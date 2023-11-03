// Implement the C program in which the main program accepts an array. The main program uses the FORK system call to create a new process called a child process. The parent process sorts an array and passes the sorted array to the child process through the command line arguments of the EXECVE system call. The child process uses an EXECVE system call to load a new program that displays the array in reverse order.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void bubble_sort(int a[], int n)
{
    int i, j, temp;
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
    printf("\nSorted Array is:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int binarySearch(int arr[], int size, int key)
{
    int left = 0;
    int right = size - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key)
        {
            printf("Element found");
            return 0;
        }
        if (arr[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    printf("Element not found");
    return -1;
}

int main(int argc, char *argv[])
{
    int size, key;

    printf("Enter the number of elements to be sorted: ");
    scanf("%d", &size);

    int *arr = (int *)malloc(size * sizeof(int));

    printf("Enter %d elements: ", size);
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("Enter the key to be searched: ");
    scanf("%d", &key);

    bubble_sort(arr, size);
    pid_t pid = fork();
    if (pid == 0)
    {
        execve(argv[1], argv + 2, NULL);

        binarySearch(arr, size, key);
        exit(1);
    }
    else
    {
        int status;
        wait(&status);
    }
    free(arr);
    return 0;
}