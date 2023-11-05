#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int sorted_array[argc - 1];
    for (int i = 0; i < argc - 1; i++)
    {
        sorted_array[i] = atoi(argv[i + 1]);
    }

    printf("\nThe sorted array by child is: ");
    for (int i = argc - 2; i >= 0; i--)
    {
        printf("%d ", sorted_array[i]);
    }
    printf("\n");

    return 0;
}
