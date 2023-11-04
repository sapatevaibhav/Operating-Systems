// Implement the C program for Page Replacement Algorithms: FCFS, LRU, and Optimal for frame size as minimum of three.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int seektime = 0;

void pageReplacement(char in[], int n, int nf);

int main()
{
    int nf;
    printf("Enter the length of string: ");
    scanf("%d", &nf);

    char in[nf];
    int choice;

    printf("Enter the string: ");
    for (int i = 0; i < nf; i++)
    {
        scanf(" %c", &in[i]);
    }

    int n = nf;

    pageReplacement(in, n, nf);

    return 0;
}

void pageReplacement(char in[], int n, int nf)
{
    int i, j, k;
    char frame[nf];
    int framePointer = 0;

    printf("The Page reference sequence is:\n");

    for (i = 0; i < n; i++)
    {
        printf(" > %c", in[i]);
    }

    // FCFS Algorithm
    int page_faults_fcfs = 0;
    char frame_fcfs[nf];
    int framePointer_fcfs = 0;

    for (i = 0; i < n; i++)
    {
        bool pageFault = true;

        for (j = 0; j < nf; j++)
        {
            if (frame_fcfs[j] == in[i])
            {
                pageFault = false;
                break;
            }
        }

        if (pageFault)
        {
            page_faults_fcfs++;
            frame_fcfs[framePointer_fcfs] = in[i];
            framePointer_fcfs = (framePointer_fcfs + 1) % nf;
        }
    }

    printf("\nPage Faults in FCFS = %d\n", page_faults_fcfs);

    // LRU Algorithm
    int page_faults_lru = 0;
    char frame_lru[nf];
    int framePointer_lru = 0;
    int leastRecentlyUsed[nf];

    for (i = 0; i < nf; i++)
    {
        frame_lru[i] = ' ';
    }

    for (i = 0; i < n; i++)
    {
        bool pageFault = true;

        for (j = 0; j < nf; j++)
        {
            if (frame_lru[j] == in[i])
            {
                pageFault = false;
                leastRecentlyUsed[j] = i;
                break;
            }
        }

        if (pageFault)
        {
            page_faults_lru++;
            int min = leastRecentlyUsed[0];
            int replacePage = 0;

            for (j = 0; j < nf; j++)
            {
                if (leastRecentlyUsed[j] < min)
                {
                    min = leastRecentlyUsed[j];
                    replacePage = j;
                }
            }

            frame_lru[replacePage] = in[i];
            leastRecentlyUsed[replacePage] = i;
        }
    }

    printf("Page Faults in LRU = %d\n", page_faults_lru);

    // Optimal Algorithm
    int page_faults_optimal = 0;
    char frame_optimal[nf];
    int framePointer_optimal = 0;

    for (i = 0; i < nf; i++)
    {
        frame_optimal[i] = ' ';
    }

    for (i = 0; i < n; i++)
    {
        bool pageFault = true;

        for (j = 0; j < nf; j++)
        {
            if (frame_optimal[j] == in[i])
            {
                pageFault = false;
                break;
            }
        }

        if (pageFault)
        {
            page_faults_optimal++;
            int leastFrequent = 0;
            int replacePage = 0;

            for (j = 0; j < nf; j++)
            {
                int count = 0;
                for (k = i + 1; k < n; k++)
                {
                    if (frame_optimal[j] == in[k])
                    {
                        count++;
                        break;
                    }
                }

                if (count < leastFrequent)
                {
                    leastFrequent = count;
                    replacePage = j;
                }
            }

            frame_optimal[replacePage] = in[i];
        }
    }

    printf("Page Faults in Optimal = %d\n", page_faults_optimal);
}
