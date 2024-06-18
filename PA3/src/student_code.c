/**
 * Aryeh Freud
 * CST 334 PA3
 * March 19, 2024
 */
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#include "student_code.h"

int statusno, _initialized;

node_t *_chunklist;
void *_arena_start, *_arena_end;


void print_header(node_t *header){
  //Note: These printf statements may produce a segmentation fault if the buff
  //pointer is incorrect, e.g., if buff points to the start of the arena.
  printf("Header->size: %lu\n", header->size);
  printf("Header->fwd: %p\n", header->fwd);
  printf("Header->bwd: %p\n", header->bwd);
  printf("Header->is_free: %d\n", header->is_free);
}


int init(size_t size) {
  if(size > (size_t) MAX_ARENA_SIZE) {
    return ERR_BAD_ARGUMENTS;
  }


  // Find pagesize and increase allocation to match some multiple a page size
  // Question: Why is it good to match our allocation to the size of the page?
  // More efficient to allocate memory in multiples of the page size
  // The OS allocates memory in pages, so if we allocate it in multiples of page size,
  // we avoid wasting memory and reduce systems calls.
  int pagesize = getpagesize();

  if (pagesize <= 0)
    return ERR_CALL_FAILED;

  //Align to page size
  if( size % pagesize != 0 ) {
    // Calculate how much we need to increase to match the size of a page
    size -= size % pagesize;
    size += pagesize;
  }

  // Open up /dev/zero to zero-init our memory.
  int fd=open("/dev/zero",O_RDWR);
  if (fd == -1) {
    return ERR_SYSCALL_FAILED;
  }
  // Map memory from /dev/zero using mmap()
  _arena_start = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

  if (_arena_start == MAP_FAILED) {
    return ERR_SYSCALL_FAILED;
  }

  _arena_end = _arena_start + size;
  _initialized = 1;

  _chunklist = _arena_start;
  _chunklist -> size = size - sizeof(node_t);

  //  mmap sets the initial memory value
  // to zero so the fwd pointer of the is already null, but
  // it doesn't hurt to make that clear
  _chunklist -> fwd = NULL;
  _chunklist -> bwd = NULL;
  _chunklist -> is_free = true;

   return size;
}

int destroy() {

  if (_initialized == 0) {
    return ERR_UNINITIALIZED; 
  }

  // Remove arena with munmap()
  if(munmap(_arena_start, _arena_end - _arena_start) == -1) {
    return ERR_SYSCALL_FAILED;
  }

  // Question: Are there memory leaks here?
  // No. We're using munmap to unmap the memory so the memory is deallocated.

  // Clean up variables
  _arena_start = NULL;
  _arena_end = NULL;
  _chunklist = NULL;
  _initialized = 0;

  return 0;
}


node_t * find_first_free_chunk(size_t size, node_t* starting_node) {
  // todo

  // Find the first available free chunk that is big enough to support the requested size allocation
  for (node_t* node = starting_node; node != NULL; node = node->fwd) {
    if (node->is_free && node->size >= size) {
      return node;
    }
  }

return NULL;

}

void split_node(node_t* node, size_t size) {

  node_t* next = node->fwd; // Save the next node

  if (node->size == size){
    // Then the node is exactly the right size
    // todo
    // If true, then done
  } else if(node->size - size < sizeof(node_t)){
    // Then the node is bigger than requested, but too small to split
    // todo
    // if true, then done
  }
  else {
    // If the requested memory does not take up the entire free chunk, we need to
    // to split that chunk and add a new node to the free list.

    // todo - done
    // Split node, create new node_t, adjust size of original node, and insert new node into list

    size_t remaining_size = node->size - size - sizeof(node_t); // Split the node

    node_t* new_node = (node_t*)((char*)node + sizeof(node_t) + size); // Create new node

    // Initialize new node
    new_node->size = remaining_size;
    new_node->is_free = true;
    new_node->fwd = next;
    new_node->bwd = node;

    // Update original node
    node->size = size;
    node->fwd = new_node;
    if (next) {
      next->bwd = new_node;
    }
  }
  // todo
  node->is_free = false; // Update original node to not free


}

node_t* get_header(void* ptr) {
  // todo

  // Find the node_t header associated with memory block
    return (node_t*)((char*)ptr - sizeof(node_t));
}

void coalesce_nodes(node_t* front, node_t* back) {

    statusno = 0; // Reset statusno

    if (front > back) {
    // todo
      node_t* temp = front;
      front = back;
      back = temp;
      statusno = ERR_BAD_ARGUMENTS;
      return;
    }
    if (front == back) {
      // Check to make sure they aren't the same node
      // todo
        statusno = ERR_BAD_ARGUMENTS;
        return;
    }
    if (front == NULL || back == NULL) {
      // Then one of them is already the end of the list
      // todo
        statusno = ERR_BAD_ARGUMENTS;
        return;
    }
    if ( ! (front->is_free && back->is_free)) {
      // Then one of them isn't free
      // todo
        statusno = ERR_CALL_FAILED;
        return;
    }

    // We want to do two things: skip over the second node and update size.
    // todo

    front->size += sizeof(node_t) + back->size;
    front->fwd = back->fwd;
    if (back->fwd != NULL) {
        back->fwd->bwd = front;
    }
}


void* mem_alloc(size_t size){

    // Check if memory system is initialized
    if (_initialized == 0) {
        statusno = ERR_UNINITIALIZED;
        return NULL;
    }

    // Include the size of the node_t struct in the total size needed for allocation
    size_t totalSizeNeeded = size + sizeof(node_t);

    // Check if there's enough memory in the arena to accommodate totalSizeNeeded
    // Considering the very first chunk that was initialized during `init`
    if (totalSizeNeeded > _chunklist->size + sizeof(node_t)) {
        statusno = ERR_OUT_OF_MEMORY;
        return NULL;
    }

    // Find the first free chunk that is big enough to support the requested size allocation
    node_t* node = find_first_free_chunk(size, _chunklist);
    if (node == NULL) {
        statusno = ERR_OUT_OF_MEMORY;
        return NULL;
    }

    // Attempt to split the node if it's significantly larger than the requested size
    split_node(node, size);

    node->is_free = false; // Mark the node as allocated

    // Return a pointer to the memory space just after the header
    return (char*)node + sizeof(node_t);
}

void mem_free(void *ptr){

    // Check if memory system is initialized
  if (ptr == NULL){
    return;
  }

  if (ptr < _arena_start || ptr > _arena_end){
    // Then the pointer is outside of the arena
    // todo
    statusno = ERR_BAD_ARGUMENTS;
    return;
  }

  // Step backward from the pointer to look at the node header
  // todo
  node_t* node = (node_t*)((char*)ptr - sizeof(node_t));

  // Free the memory
  // todo
  node->is_free = true;

  // Coalesce together the chunks
  // todo

  // coalesce with the previous node
  if (node->bwd != NULL && node->bwd->is_free) {
      coalesce_nodes(node->bwd, node);
      node = node->bwd;
  }
// coalesce with the next node
  if (node->fwd != NULL && node->fwd->is_free) {
      coalesce_nodes(node, node->fwd);
  }
}
