// Implement the C program for Deadlock Avoidance Algorithm: Bankers Algorithm.

#include <stdio.h>

int main()
{
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int available[m], max[n][m], allocated[n][m], need[n][m], completed[n];

    for (int i = 0; i < n; i++)
        completed[i] = 0;

    printf("Enter available resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    printf("Enter maximum resources for each process:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter allocated resources for each process:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocated[i][j]);
            need[i][j] = max[i][j] - allocated[i][j];
        }

    printf("Safe Sequence is: ");
    int safeSequence[n];
    int count = 0;

    while (count < n)
    {
        int k = -1;

        for (int i = 0; i < n; i++)
        {
            if (!completed[i])
            {
                int safe = 1;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        safe = 0;
                        break;
                    }
                }
                if (safe)
                {
                    k = i;
                    break;
                }
            }
        }

        if (k == -1)
        {
            break;
        }

        completed[k] = 1;
        for (int j = 0; j < m; j++)
        {
            available[j] += allocated[k][j];
        }

        safeSequence[count] = k;
        count++;
    }

    if (count == n)
    {

        for (int i = 0; i < n; i++)
        {
            printf("P%d", safeSequence[i]);
            if (i < n - 1)
            {
                printf(" -> ");
            }
        }
        printf("\n");

        printf("All processes can be allocated resources safely.\n");
    }
    else
    {
        printf("Unsafe state detected!\n");
        for (int i = 0; i < n; i++)
        {
            if (!completed[i])
            {
                printf("Process P%d cannot be allocated resources.\n", i);
            }
        }
    }
}