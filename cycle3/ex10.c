#include <stdio.h>
#include <stdlib.h>
int available[10];
int allocation[10][10];
int request[10][10];
void main()
{
    int n, m;
    printf("input the no.of processes:");
    scanf("%d", &n);
    printf("input the no.of resource types:");
    scanf("%d", &m);
    printf("\navailable resources:");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }
    printf("\nallocation matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("process %d:", i);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("\nrequest matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("process %d:", i);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }
    int *work = (int *)malloc(m * sizeof(int));   // array of length m
    int *finish = (int *)malloc(n * sizeof(int)); // array of length n
    // initializing work=available
    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }
    // initializing finish
    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        for (int j = 0; j < m; j++)
        {
            if (allocation[i][j] != 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            finish[i] = 1;
        }
        else
        {
            finish[i] = 0;
        }
    }

    for (int z = 0; z < n; z++)
    {
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int f = 0;
                for (int j = 0; j < m; j++)
                {
                    if (request[i][j] > work[j])
                    {
                        f = 1;
                    }
                }
                if (f == 0)
                {
                    for (int p = 0; p < m; p++)
                        work[p] += allocation[i][p];
                    finish[i] = 1;
                }
            }
        }
    }
    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        if (finish[i] == 0)
        {
            flag = 1;
            printf("\ndeadlock detected\n");
            break;
        }
    }
    if (flag == 0)
        printf("\n no deadlock\n");
}