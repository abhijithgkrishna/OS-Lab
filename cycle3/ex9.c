#include <stdio.h>
int available[10];
int allocation[10][10];
int max[10][10];
int need[10][10];
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
    printf("\nmax matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("process %d:", i);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    printf("\nallocation matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("process %d:", i);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    int finish[10], safe_sequence[10], z = 0;
    for (int i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int flag = 0;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    safe_sequence[z++] = i;
                    for (int y = 0; y < m; y++)
                        available[y] += allocation[i][y];
                    finish[i] = 1;
                }
            }
        }
    }
    printf("\nSAFE Sequence is:\n");
    for (int i = 0; i < n - 1; i++)
        printf(" P%d ->", safe_sequence[i]);
    printf("P%d\n", safe_sequence[n - 1]);
}