#include "libraries.h"
#include "semaphore.h"
#include "memory.h"
#include "file.h"


char *get_prev_line() {
  int size = memory_read();
  if (size == 0) return "(no previous line found)";
  char *line = (char *) calloc(sizeof(char), size + 1);
  int fd = file_open(O_RDWR | O_APPEND);
  lseek(fd, -1 * size, SEEK_END);
  read(fd, line, size);
  close(fd);
  return line;
}

void write_next_line(char *line) {
  int fd = file_open(O_RDWR | O_APPEND);
  lseek(fd, 0, SEEK_END);
  write(fd, line, strlen(line));
}

int main() {
  if (semget(SEM_KEY, 1, 0) == -1 ) {
    printf("\nNo story available for access:\nRun $ ./control -c N to create a new story\n\n");
    exit(1);
  }
  
  int sem_id = get_semaphore_id(0); //this line may trigger wait
  
  printf("Waiting for access to file.\n");
  struct sembuf sem_cmd = {0, -1, SEM_UNDO};
  semop(sem_id, &sem_cmd, 1);
  printf("File access recieved.\n");
  
  
  printf("Last line entered:\n%s\nPlease enter next line:\n", get_prev_line());
  char input[64];
  fgets(input, sizeof(input), stdin);
  write_next_line(input);

  memory_write(strlen(input));
  
  sem_cmd.sem_op *= -1;
  semop(sem_id, &sem_cmd, 1);

  return 0;
}
  
  
  
  
