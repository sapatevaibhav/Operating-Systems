#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
    int sorted_array[argc - 1];
    for (int i = 1; i <= argc - 1; i++)
    {
        sorted_array[i - 1] = atoi(argv[i]);
    }

    printf("The sorted array by child is: ");
    for (int i = argc - 2; i >= 0; i--)
    {
        printf("%d ", sorted_array[i]);
    }
    printf("\n");

}
