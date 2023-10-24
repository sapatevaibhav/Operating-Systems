#include <stdio.h>
#include <stdlib.h>

int seektime = 0;

void fcfs(int sequence[], int head, int n);
void sstf(int sequence[], int head, int n);
void scan(int sequence[], int head, int n);

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
        printf("1. FCFS\n2. SSTF\n3. SCAN\n4. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fcfs(sequence, head, n);
            break;
        case 2:
            sstf(sequence, head, n);
            break;
        case 3:
            scan(sequence, head, n);
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

void sstf(int sequence[], int head, int n)
{
    int arr[n], min, temp, i, j, pos;

    for (i = 0; i < n; i++)
    {
        arr[i] = 0;
    }

    while (1)
    {
        min = 999;
        for (i = 0; i < n; i++)
        {
            if (arr[i] == 0)
            {
                if (min > abs(head - sequence[i]))
                {
                    min = abs(head - sequence[i]);
                    pos = i;
                }
            }
        }

        if (min == 999)
            break;
        arr[pos] = 1;
        seektime += min;
        head = sequence[pos];
        printf(" > %d", sequence[pos]);
    }

    printf("\nSeek Time of SSTF = %d\n", seektime);
}

void scan(int sequence[], int head, int n)
{
    int temp, i, j;
    seektime = 0;

    printf("The Disk sequence is:\n");

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (sequence[i] > sequence[j])
            {
                temp = sequence[i];
                sequence[i] = sequence[j];
                sequence[j] = temp;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        if (sequence[i] > head)
        {
            printf(" > %d", sequence[i]);
            seektime += abs(temp - sequence[i]);
            temp = sequence[i];
        }
    }

    for (i = n - 1; i >= 0; i--)
    {
        if (head > sequence[i])
        {
            printf(" > %d", sequence[i]);
            seektime += abs(temp - sequence[i]);
            temp = sequence[i];
        }
    }

    printf("\nSeek Time of SCAN = %d\n", seektime);
}
