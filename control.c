#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "semaphore.h"

void print_usage_and_exit() {
  fprintf(stderr,
	  "Usage: control [-c N | -v | -r ]\n"
	  "-c N : Creates a semaphore and sets its value to N\n"
	  "-v   : View the current value of the semaphore\n"
	  "-r   : Removes the semaphore\n");
  exit(1);
}

int main(int argc, char** argv) {
  if (argc == 1) {
    print_usage_and_exit();
  }

  char* opt = argv[1];
  if (strncmp(opt, "-c", 2) == 0) {
    if (argc == 2) {
      print_usage_and_exit();
    }
    char* value_text = argv[2];
    int value;
    if (sscanf(value_text, "%d", &value) != 1) {
      print_usage_and_exit();
    }
    semaphore_create(value);
  } else if (strncmp(opt, "-v", 2) == 0) {
    semaphore_view_value();
  } else if (strncmp(opt, "-r", 2) == 0) {
    semaphore_remove();
  } else {
    print_usage_and_exit();
  }
  
  return 0;
}
