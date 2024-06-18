Your task

You'll be doing two things.

You will be writing a set of functions to implement read and write locks to make a database object threadsafe. These functions should use both locks and condition variables.
You will be converting a webserver from being single-thread to multi-threaded
Functions you'll be writing

In this assignment you'll be writing 5 functions. Note that these funtions are used through the rest of the code in student_code.c, and only these 5 should be changed.

void pass_to_client_handler(void* arg) {
  // todo: Convert this to run multi-threaded
  client_handler(arg);
}


void read_lock(PlayerDatabase* db) {
  // todo
}

void read_unlock(PlayerDatabase* db) {
  // todo
}

void write_lock(PlayerDatabase* db) {
  // todo
}

void write_unlock(PlayerDatabase* db) {
  // todo
}
