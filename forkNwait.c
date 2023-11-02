// Implement the C program in which the main program accepts the integers to be sorted. The main program uses the FORK system call to create a new process called a child process. The parent process sorts the integers using a sorting algorithm and waits for the child process using the WAIT system call to sort the integers using any sorting algorithm. Also, demonstrate zombie and orphan states.

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

void bubble_sort(int arr[], int size)
{
    for (int step = 0; step < size - 1; step++)
    {
        for (int i = 0; i < size - step - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    }
}

int main()
{
    int pid, size;

    printf("Enter the number of elements to be sorted: ");
    scanf("%d", &size);

    int *arr = (int *)malloc(size * sizeof(int));

    printf("Enter %d elements: ", size);
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    pid = fork();

    if (pid == 0)
    {
        printf("\nChild's PID: %d\n", getpid());
        printf("Parent's PID: %d\n", getppid());
        bubble_sort(arr, size);

        printf("\nSorted by Child:\n");
        for (int i = 0; i < size; i++)
        {
            printf("%d ", arr[i]);
        }
    }
    else if (pid > 0)
    {
        int status;
        wait(&status);
        bubble_sort(arr, size);

        printf("\nSorted by Parent:\n");
        for (int i = 0; i < size; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n\nTerminated the Child whose PID was: %d\n", pid);
    }
    free(arr);
    return 0;
}