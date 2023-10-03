#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void bubble_sort(int a[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    printf("\nSorted Array is:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", a[i]);
    }
}

int main(int argc, char *argv[])
{
    int n = argc - 2;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = atoi(argv[i + 2]);
    }
    bubble_sort(a, n);

    pid_t pid = fork();

    if (pid == 0)
    {
        printf("\nI am Child Process, my pid is %d\n", getpid());
        printf("I am Parent Process, my pid is %d\n", getppid());
        execve(argv[1], argv + 1, NULL);
    }
    else
    {
        int k;
        wait(&k);
        printf("\nI am Parent Process, my pid is %d\n", getpid());
        printf("I am Parent's Parent Process, my pid is %d\n\n", getppid());
    }

    return 0;
}
