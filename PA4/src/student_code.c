/**
 * Aryeh Freud
 * CST 334 PA4
 * March 26, 2024
 */
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

#include "student_code.h"


bool is_entry_valid(PageTableEntry pte) {
  // todo
  // shift right by VALID_BIT - 1.
  // if VALID_BIT is the most significant bit, we need to shift it all the way
  // to the least significant bit to easily check if it's set
  return (pte >> (VALID_BIT - 1)) & 1;
}

bool is_read_enabled(PageTableEntry pte) {
  // todo
  // Question: Implement this function.  Hint: it can take as little as 1 line.
  // shift pte right to bring READ_BIT to the least significant bit, then mask all other bits off
  // return will yield 1 if READ_BIT is set (indicating read permission is enabled)
  return (pte >> (READ_BIT - 1)) & 1;
}

bool is_write_enabled(PageTableEntry pte) {
  // todo
  // shift pte right to bring WRITE_BIT to the least significant bit, then mask all other bits off
  // if WRITE_BIT is set, operation returns true, indicating write permission is enabled
  return (pte >> (WRITE_BIT - 1)) & 1;
}

bool is_execute_enabled(PageTableEntry pte) {
  // todo
  // shift pte right to bring EXEC_BIT to the least significant bit, then mask all other bits off
  // if EXEC_BIT is set, operation returns true, indicating execute permission is enabled
  return (pte >> (EXEC_BIT - 1)) & 1;
}

PFN find_free_page(MMU m) {
  // todo
  // iterate through page_used array to find the first free page frame
    for (PFN i = 0; i < NUM_FRAMES; i++) {
        if (!m.page_used[i]) {
        return i;
        }
    }
    // return invalid PFN if no free page frame was found
    return (PFN)-1;
}

PFN convert_PageTableEntry_to_PFN(PageTableEntry pte) {
  // todo
  // create a mask to isolate PFN bits. the mask has NUM_PFN_BITS bits set to 1 at the least significant end
  PFN mask = (1ULL << NUM_PFN_BITS) - 1;
  // apply mask to pte to isolate and retrieve PFN bits
  return pte & mask;
}


/*
 * Page Table Functions
 */
PageTableEntry get_pagetableentry__MMU_pagetable(MMU m, VPN vpn) {
  // todo
  // return the page table entry at the given vpn
    return m.page_pointer[vpn];
}

PFN map_page__MMU_pagetable(MMU* m, VPN vpn, bool can_read, bool can_write, bool can_exec) {
    // todo
    // first find a free page frame
    PFN free_pfn = find_free_page(*m);
    if (free_pfn == (PFN)-1) { // check if no free page was found
        return (PFN)-1; // indicate failure to map a new page (no free frame available)
    }

    // construct the page table entry
    PageTableEntry pte = 0;
    pte |= ((PageTableEntry)free_pfn); // set the PFN bits

    // set permissions bits
    if (can_read) pte |= single_bit_mask(READ_BIT);
    if (can_write) pte |= single_bit_mask(WRITE_BIT);
    if (can_exec) pte |= single_bit_mask(EXEC_BIT);
    pte |= single_bit_mask(VALID_BIT); // set the valid bit

    // update MMU page table
    m->page_pointer[vpn] = pte; // direct mapping of vpn to index

    // mark the page frame as used
    m->page_used[free_pfn] = true;

    return free_pfn;
}


/*
 * Page Directory Functions
 */

Page* get_page(MMU m, VirtualAddress va, bool for_read, bool for_write, bool for_execute) {
  // todo
  // extract vpn from va
  VPN vpn = va >> NUM_OFFSET_BITS;

  // retrieve corresponding page table entry
  PageTableEntry pte = get_pagetableentry__MMU_pagetable(m, vpn);

  // check permissions
  if ((for_read && !is_read_enabled(pte)) ||
      (for_write && !is_write_enabled(pte)) ||
      (for_execute && !is_execute_enabled(pte))) {
    return NULL;
  }

  // convert PageTableEntry to PFN
    PFN pfn = convert_PageTableEntry_to_PFN(pte);

  // return pointer to corresponding page in physical memory
  return (Page*)(m.physical_memory + (pfn * PAGE_SIZE));
}

char read_byte(MMU m, VirtualAddress va) {
  // todo

  // extract VPN from virtual address
  VPN vpn = va >> NUM_OFFSET_BITS;

  // extract offset within the page
  OFFSET offset = va & ((1ULL << NUM_OFFSET_BITS) - 1);

  // retrieve page table entry using VPN
  PageTableEntry pte = get_pagetableentry__MMU_pagetable(m, vpn);

  // check if page table is valid and readable
  if (!is_entry_valid(pte) || !is_read_enabled(pte)) {
    printf("Invalid page table entry or read permission not enabled\n");
    return -1;
  }

  // convert pte to PFN
  PFN pfn = convert_PageTableEntry_to_PFN(pte);

  // calculate physical address
  PhysicalAddress pa = (pfn << NUM_OFFSET_BITS) | offset;

  // read and return the byte at the calculated physical address
  return m.physical_memory[pa];
}

void write_byte(MMU m, VirtualAddress va, char val) {
  // todo

  // extract VPN from virtual address
  VPN vpn = va >> NUM_OFFSET_BITS;

  // extract offset within the page
  OFFSET offset = va & ((1ULL << NUM_OFFSET_BITS) - 1);

  // retrieve page table entry using VPN
  PageTableEntry pte = get_pagetableentry__MMU_pagetable(m, vpn);

  // ensure page table entry is valid and writable
  if (!is_entry_valid(pte) || !is_write_enabled(pte)) {
      return;
  }

  // convert page table entry to a physical frame number
  PFN pfn = convert_PageTableEntry_to_PFN(pte);

  // calculate the physical address
  PhysicalAddress pa = (pfn << NUM_OFFSET_BITS) | offset;

  // write the byte to the calculated physical address
  m.physical_memory[pa] = val;
}
