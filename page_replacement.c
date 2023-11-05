// Implement the C program for Page Replacement Algorithms: FCFS, LRU, and Optimal for frame size as minimum of three.
#include <stdio.h>
#include <stdlib.h>

int findOptimal(int page[], int n, int indexes[], int m)
{
    int res = -1, farthest = indexes[0];
    for (int i = 0; i < m; i++)
    {
        int j;
        for (j = 0; j < n; j++)
        {
            if (page[j] == indexes[i])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

int main()
{
    int choice, capacity;
    int n;

    printf("Enter the number of pages: ");
    scanf("%d", &n);
    int page[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &page[i]);
    }
    printf("Enter frame size: ");
    scanf("%d", &capacity);

    if (capacity < 3)
    {
        printf("Frame size cannot be less than 3.\n");
        exit(0);
    }
    int frame[capacity];
    int faults = 0;

    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int j;
        for (j = 0; j < capacity; j++)
        {
            if (frame[j] == page[i])
                break;
            else if (frame[j] == -1)
            {
                frame[j] = page[i];
                faults++;
                break;
            }
        }
        if (j == capacity)
        {
            frame[0] = page[i];
            faults++;
        }
    }

    printf("First Come First Serve (FCFS) - Total Page Faults: %d\n", faults);

    faults = 0;
    int usedTime[capacity];

    for (int i = 0; i < capacity; i++)
    {
        frame[i] = -1;
        usedTime[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int j;
        for (j = 0; j < capacity; j++)
        {
            if (frame[j] == page[i])
            {
                usedTime[j] = i + 1;
                break;
            }
            else if (frame[j] == -1)
            {
                frame[j] = page[i];
                usedTime[j] = i + 1;
                faults++;
                break;
            }
        }
        if (j == capacity)
        {
            int lru = 0;
            for (int k = 1; k < capacity; k++)
            {
                if (usedTime[k] < usedTime[lru])
                    lru = k;
            }
            frame[lru] = page[i];
            usedTime[lru] = i + 1;
            faults++;
        }
    }

    printf("Least Recently Used (LRU) - Total Page Faults: %d\n", faults);

    faults = 0;

    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int j;
        for (j = 0; j < capacity; j++)
        {
            if (frame[j] == page[i])
                break;
            else if (frame[j] == -1)
            {
                frame[j] = page[i];
                faults++;
                break;
            }
        }
        if (j == capacity)
        {
            int index = findOptimal(page, n, frame, capacity);
            frame[index] = page[i];
            faults++;
        }
    }

    printf("Optimal Page Replacement - Total Page Faults are: %d\n", faults);

    return 0;
}