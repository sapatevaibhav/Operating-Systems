// Implement the C program in which the main program accepts an array. The main program uses the FORK system call to create a new process called a child process. The parent process sorts an array and passes the sorted array to the child process through the command line arguments of the EXECVE system call. The child process uses an EXECVE system call to load a new program that displays the array in reverse order.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void bubble_sort(int a[], int n, int order)
{
    int i, j, temp;
    if (order == 1)
    {
        for (i = n - 1; i > 0; i--)
        {
            for (j = 0; j < i; j++)
            {
                if (a[j] > a[j + 1])
                {
                    temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                }
            }
        }
    }
    else
    {
        for (i = n - 1; i > 0; i--)
        {
            for (j = 0; j < i; j++)
            {
                if (a[j] < a[j + 1])
                {
                    temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                }
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int size;

    printf("Enter the number of elements to be sorted: ");
    scanf("%d", &size);

    int *arr = (int *)malloc(size * sizeof(int));

    printf("Enter %d elements: ", size);
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        printf("\nChild's PID: %d", getpid());
        printf("\nSorted Array in child:\n");
        bubble_sort(arr, size, 4);
        execve(argv[1], argv + 2, NULL);
        exit(1);
    }
    else
    {
        int status;
        wait(&status);
        printf("\nParent's PID: %d", getpid());
        printf("\nSorted Array in parent:\n");
        bubble_sort(arr, size, 1);
    }
    free(arr);
    return 0;
}