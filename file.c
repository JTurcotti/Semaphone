#include "libraries.h"
#include "semaphore.h"
#include "memory.h"
#include "file.h"

//these are totally pointless but it doesn't work without them
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
void file_create() {
  close(open(FILE_NAME, O_CREAT | O_TRUNC, 0644));
  
  printf("Successfully created file with name %s.\n", FILE_NAME);
}

int file_open(int flags) {
  int fd = open(FILE_NAME, flags, 0644);

  if (fd == -1) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(1);
  }

  return fd;
}
