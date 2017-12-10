#include "libraries.h"
#include "semaphore.h"
#include "memory.h"
#include "file.h"

// The man page for semctl says we have to declare this ourselves.
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};

int get_semaphore_id(int flags) {
    int semid = semget(SEM_KEY, 1, flags);
    if (semid == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    return semid;
}

void semaphore_create(int value) {
    int semid = get_semaphore_id(IPC_CREAT | IPC_EXCL | 0644);

    union semun semopts;
    semopts.val = value;
    if (semctl(semid, 0, SETVAL, semopts) == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }
    
    printf("Sucessfully created semaphore with initial value of %d. ID: %d\n", value, semid);
}

void semaphore_view_value() {
    // TODO: Does the mode need to be passed as a flag here?
    int semid = get_semaphore_id(0);

    printf("Semaphore value: %d\n", semctl(semid, 0, GETVAL));
}

void semaphore_remove() {
    // TODO: Does the mode need to be passed as a flag here?
    int semid = get_semaphore_id(0);

    if (semctl(semid, 0, IPC_RMID) == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    printf("Sucessfully removed semaphore.\n");
}
