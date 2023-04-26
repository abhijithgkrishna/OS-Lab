#include <stdio.h>
int process_size[10];
int block_size[10];
int block_allocated[10];
int process_alloc[10];
void main()
{
    int m;
    printf("input the no. of blocks:");
    scanf("%d", &m);
    int n;
    printf("\ninput the no. of processes:");
    scanf("%d", &n);
    printf("\ninput block sizes:");
    for (int i = 0; i < m; i++)
    {
        printf("\nblock %d:", i);
        scanf("%d", &block_size[i]);
    }
    printf("\ninput process sizes:");
    for (int i = 0; i < n; i++)
    {
        printf("\nprocess %d:", i);
        scanf("%d", &process_size[i]);
    }
    for (int i = 0; i < m; i++)
        block_allocated[i] = 0;
    for (int i = 0; i < n; i++)
        process_alloc[i] = -1;
    for (int i = 0; i < n; i++)
    {
        int large;
        for (int j = 0; j < m; j++)
        {
            if (block_allocated[j] == 0)
            {
                if (block_size[j] >= process_size[i])
                {
                    large = j;
                    break;
                }
            }
        }
        for (int j = 0; j < m; j++)
        {
            if (block_allocated[j] == 0)
            {
                if (((block_size[j] - process_size[i]) >= 0) && (block_size[j] >
                                                                 block_size[large]))
                {
                    large = j;
                }
            }
        }
        process_alloc[i] = large;
        block_allocated[large] = 1;
    }
    printf("\nprocesss no.|process size|allocated block|allocated block size|internal fragmentation\n");
    for (int i = 0; i < n; i++)
    {
        int j = process_alloc[i];
        int s = process_size[i];
        int frag = block_size[j] - process_size[i];
        if (process_alloc[i] != -1)
            printf(" %d\t\t%d\t\t%d\t\t%d\t\t %d\n", i, s, j, block_size[j], frag);
        else
            printf(" %d\t\t%d\t\t--\t\t--\t\t --\n", i, s);
    }
}