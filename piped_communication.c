// Inter-process communication in Linux using Pipes: FIFOS : Full duplex communication between two independent processes.The first process accepts sentences and writes on one pipe to be read by the second rocess and the second process counts the number of characters, the number of words, and the number of lines in accepted sentences, and writes this output in a text file and writes the contents of the file on the second pipe to be read by the first process and displays on standard output.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define FIFO_FILE "myfifo"
#define OUTPUT_FILE "output.txt"
#define MAX_BUF 1024

        void
        childProcess(int fifo_fd);

int main()
{
    int res;
    pid_t child_pid;
    int fifo_fd;

    res = mkfifo(FIFO_FILE, 0666);
    if (res != 0)
    {
        perror("FIFO creation failed");
        exit(EXIT_FAILURE);
    }

    child_pid = fork();
    if (child_pid < 0)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0)
    {

        childProcess(fifo_fd);
        exit(EXIT_SUCCESS);
    }
    else
    {

        char input[MAX_BUF];
        fifo_fd = open(FIFO_FILE, O_WRONLY);
        if (fifo_fd == -1)
        {
            perror("Opening FIFO failed");
            exit(EXIT_FAILURE);
        }

        while (1)
        {
            printf("Enter a sentence (or 'exit' to quit): ");
            fgets(input, MAX_BUF, stdin);

            if (strcmp(input, "exit\n") == 0)
            {
                close(fifo_fd);
                break;
            }

            write(fifo_fd, input, strlen(input) + 1);
        }

        close(fifo_fd);
        wait(NULL);

        char ch;
        FILE *outputFile = fopen(OUTPUT_FILE, "r");
        if (outputFile == NULL)
        {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }

        while ((ch = fgetc(outputFile)) != EOF)
        {
            putchar(ch);
        }

        fclose(outputFile);
    }

    return 0;
}
void childProcess(int fifo_fd)
{
    int bytesRead;
    char received[MAX_BUF];
    int charCount = 0;
    int wordCount = 0;
    int lineCount = 0;

    int outputFile = open(OUTPUT_FILE, O_WRONLY | O_CREAT, 0666);
    if (outputFile == -1)
    {
        perror("Opening output file failed");
        exit(EXIT_FAILURE);
    }

    fifo_fd = open(FIFO_FILE, O_RDONLY);
    if (fifo_fd == -1)
    {
        perror("Opening FIFO failed");
        exit(EXIT_FAILURE);
    }

    char lastChar = ' ';

    while (1)
    {
        bytesRead = read(fifo_fd, received, sizeof(received));

        if (bytesRead <= 0)
        {
            close(fifo_fd);
            break;
        }

        for (int i = 0; i < bytesRead; i++)
        {
            char currentChar = received[i];

            if (currentChar >= 32 && currentChar <= 126 || currentChar == '\n')
            {
                charCount++;

                if (currentChar == ' ' || currentChar == '\n')
                {

                    if (lastChar != ' ' && currentChar == ' ')
                    {
                        wordCount++;
                    }

                    if (currentChar == '\n')
                    {
                        lineCount++;
                    }
                }

                lastChar = currentChar;

                write(outputFile, &currentChar, 1);
            }
        }
    }

    printf("Character count: %d\n", charCount);
    printf("Word count: %d\n", wordCount);
    printf("Line count: %d\n", lineCount);

    dprintf(outputFile, "Character count: %d\n", charCount);
    dprintf(outputFile, "Word count: %d\n", wordCount);
    dprintf(outputFile, "Line count: %d\n", lineCount);

    close(outputFile);
}
