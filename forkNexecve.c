// Implement the C program in which the main program accepts an array. The main program uses the FORK system call to create a new process called a child process. The parent process sorts an array and passes the sorted array to the child process through the command line arguments of the EXECVE system call. The child process uses an EXECVE system call to load a new program that displays the array in reverse order.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void sort(int *array, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main()
{
    char *argv[4];

    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int array[size];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &array[i]);
    }

    int pid = fork();

    if (pid < 0)
    {
        printf("Error creating child process\n");
        exit(1);
    }

    if (pid > 0)
    {
        sort(array, size);

        char *args[size + 2];
        args[0] = "./display_reverse";
        for (int i = 1; i <= size; i++)
        {
            args[i] = malloc(sizeof(char) * 10);
            sprintf(args[i], "%d", array[i - 1]);
        }
        args[size + 1] = NULL;

        execve("./display_reverse", args, NULL);
    }

    else
    {

        int sorted_array[size];
        for (int i = 1; i <= size; i++)
        {
            sorted_array[i - 1] = atoi(argv[i]);
        }

        printf("The sorted array in reverse order is: ");
        for (int i = size - 1; i >= 0; i--)
        {
            printf("%d ", sorted_array[i]);
        }
        printf("\n");
    }
    return 0;
}