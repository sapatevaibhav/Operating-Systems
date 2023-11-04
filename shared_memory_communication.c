#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int shmid;
    void *shared_memory;
    char buff[100];

    shmid = shmget((key_t)2345, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }

    shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (void *)-1)
    {
        perror("shmat");
        return 1;
    }

    printf("Parent Process: Process attached at %p\n", shared_memory);
    printf("Parent Process: Enter some data to write to shared memory\n");
    read(0, buff, 100);
    strcpy((char*)shared_memory, buff);
    printf("Parent Process: You wrote : %s\n", (char *)shared_memory);

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child Process: Process attached at %p\n", shared_memory);
        printf("Child Process: Data read from shared memory is : %s\n", (char *)shared_memory);
    }
    else
    {
        wait(NULL); 
    }

    return 0;
}
