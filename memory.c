#include "libraries.h"
#include "semaphore.h"
#include "memory.h"
#include "file.h"


int get_memory_id(int flags) {
  int shm_id = shmget(SHM_KEY, sizeof(int), flags);
  if (shm_id == -1) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(1);
  }
  
  return shm_id;
}

void memory_write(int value) {
  int *data = shmat(get_memory_id(0), 0, 0);
  *data = value;
  shmdt(data);
}

void memory_create() {
  int shmid = get_memory_id(IPC_CREAT | 0644);
  memory_write(0);
   
  printf("Sucessfully created shared memory with initial value of %d. ID: %d\n", memory_read(), shmid);
}

int memory_read() {
  int *data = shmat(get_memory_id(0), 0, 0);
  int value = *data;
  shmdt(data);
  return value;
}

void memory_remove() {
  int shm_id = get_memory_id(0);

  if (shmctl(shm_id, 0, IPC_RMID) == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
  }
  
  printf("Successfully removed shared memory.\n");
}

