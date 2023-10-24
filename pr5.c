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
    int count, k;
    while (count < n)
    {
        count = k;
        for (int i = 0; i < n; i++)
        {
            int safe = 1;
            for (int j = 0; j < m; j++)
            {
                if (completed[i] || need[i][j] > available[j])
                {
                    safe = 0;
                    break;
                }
            }
            if (safe)
            {
                completed[i] = 1;
                for (int j = 0; j < m; j++)
                    available[j] += allocated[i][j];
                printf("P%d ", i);
                count++;
            }
        }
        if (count == k)
            break;
    }

    if (count < n)
    {
        printf("\nUnsafe state detected!\n");
        for (int i = 0; i < n; i++)
        {
            if (!completed[i])
            {
                printf("Process P%d cannot be allocated resources.\n", i);
            }
        }
    }
    else
    {
        printf("\nAll processes can be allocated resources safely.\n");
    }

    return 0;
}
