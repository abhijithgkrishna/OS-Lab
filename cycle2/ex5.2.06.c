#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
int main()
{
    key_t key = ftok("shmfile", 43);
    int shmid = shmget(key, 1024, 0666);
    printf("identifier for shared memory is: %d\n", shmid);
    void *shared_memory = shmat(shmid, NULL, 0);
    printf("Process attached at %p\n", shared_memory);
    char buff[100];
    printf("Data read from shared memory is:%s\n", (char *)shared_memory);
    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL); // destroy shared memory
}