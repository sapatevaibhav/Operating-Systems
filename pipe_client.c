#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define FIFO_PIPE "xyz"

int main()
{
    int fd, i, c = 0, w = 0, l = 0;
    char str[100];

    fd = open(FIFO_PIPE, O_RDONLY);
    read(fd, str, sizeof(str));
    printf("\nReceived Data : %s", str);

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ' || str[i] == '\n')
            w++;
        if (str[i] == '\n')
            l++;
        c++;
    }
    printf("\n No of characters = %d", c);
    printf("\n No of lines = %d", l + 1);
    printf("\n No of words = %d \n", w + 1);

    close(fd);
    return 0;
}