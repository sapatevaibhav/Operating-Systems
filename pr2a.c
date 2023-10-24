#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int arr[], int size, int ascending)
{
    for (int step = 0; step < size - 1; step++)
    {
        for (int i = 0; i < size - step - 1; i++)
        {
            int condition = ascending ? (arr[i] > arr[i + 1]) : (arr[i] < arr[i + 1]);
            if (condition)
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
        printf("Child's PID: %d\n", getpid());
        printf("Parent's PID: %d\n", getppid());
        bubble_sort(arr, size, 1);

        printf("\nSorted in ascending order by Child:\n");
        for (int i = 0; i < size; i++)
        {
            printf("%d ", arr[i]);
        }
    }
    else if (pid > 0)
    {
        int status;
        wait(&status);
        printf("\n\nTerminated Child's PID: %d\n", pid);
        printf("Parent's PID: %d\n", getpid());
        printf("Parent's parent PID: %d\n", getppid());
    }
    free(arr);
    return 0;
}
