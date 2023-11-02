// Implement the C program for Page Replacement Algorithms: FCFS, LRU, and Optimal for frame size as minimum of three.

#include <stdio.h>
#include <stdlib.h>

    int seektime = 0;

void fcfs(int sequence[], int head, int n);
void lru(int sequence[], int head, int n);
void optimal(int sequence[], int head, int n);

int main()
{
    int n, t, i, head, choice;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    printf("Enter the total number of tracks: ");
    scanf("%d", &t);

    int sequence[n];

    printf("Enter the disk request sequence for a disk with %d tracks: ", t);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &sequence[i]);
    }

    printf("Enter the initial position of the R/W head: ");
    scanf("%d", &head);

    do
    {
        printf("\n----------------------------------\n");
        printf("1. FCFS\n2. LRU\n3. Optimal\n4. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fcfs(sequence, head, n);
            break;
        case 2:
            lru(sequence, head, n);
            break;
        case 3:
            optimal(sequence, head, n);
            break;
        case 4:
            exit(0);
            break;
        }
    } while (1);

    return 0;
}

void fcfs(int sequence[], int head, int n)
{
    int i, temp = head;
    seektime = 0;

    printf("The Disk sequence is:\n");

    for (i = 0; i < n; i++)
    {
        printf(" > %d", sequence[i]);
        seektime += abs(sequence[i] - temp);
        temp = sequence[i];
    }

    printf("\nSeek Time of FCFS = %d\n", seektime);
}

void lru(int sequence[], int head, int n)
{
    int i, j, k, fault = 0, flag, pos;
    int frame_size;

    printf("Enter the frame size: ");
    scanf("%d", &frame_size);

    int frame[frame_size];
    int page[n];

    for (i = 0; i < frame_size; i++)
    {
        frame[i] = -1;
    }

    printf("The Disk sequence is:\n");

    for (i = 0; i < n; i++)
    {
        page[i] = -1;

        for (j = 0; j < frame_size; j++)
        {
            if (frame[j] == sequence[i])
            {
                page[i] = j;
                break;
            }
        }

        if (page[i] == -1)
        {
            fault++;

            if (i < frame_size)
            {
                frame[i] = sequence[i];
                page[i] = i;
            }
            else
            {
                int max = -1;
                for (j = 0; j < frame_size; j++)
                {
                    if (page[j] == -1)
                    {
                        pos = j;
                        break;
                    }

                    if (max < page[j])
                    {
                        max = page[j];
                        pos = j;
                    }
                }

                frame[pos] = sequence[i];
                page[i] = pos;
            }
        }

        printf(" > %d", sequence[i]);
    }

    seektime = fault;
    printf("\nSeek Time of LRU = %d\n", seektime);
}

void optimal(int sequence[], int head, int n)
{
    int i, j, k, flag, pos, max, index;
    int temp[n];
    int visited[n];

    for (i = 0; i < n; i++)
    {
        temp[i] = sequence[i];
        visited[i] = 0;
    }

    printf("The Disk sequence is:\n");
    for (i = 0; i < n; i++)
    {
        max = -1;
        for (j = 0; j < n; j++)
        {
            if (!visited[j])
            {
                if (max == -1 || abs(temp[j] - head) > max)
                {
                    max = abs(temp[j] - head);
                    index = j;
                }
            }
        }
        visited[index] = 1;
        seektime += max;
        head = temp[index];
        printf(" > %d", head);
    }

    printf("\nSeek Time of Optimal = %d\n", seektime);
}