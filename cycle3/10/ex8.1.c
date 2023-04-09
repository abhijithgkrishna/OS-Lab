#include <stdio.h>
int ref_string[20];
int no_of_frames;
int q[100], f = -1, r = -1, q_size = 0;
void push(int item)
{
    if (f == -1)
    {
        f = 0;
        r = 0;
        q[r] = item;
    }
    else
    {
        r++;
        q[r] = item;
    }
    q_size++;
}
void pop()
{
    f++;
    q_size--;
}
int search(int item)
{
    for (int i = f; i <= r; i++)
    {
        if (q[i] == item)
        {
            return 1;
        }
    }
    return 0;
}
void main()
{
    printf("input no. of frames:");
    scanf("%d", &no_of_frames);
    int n;
    printf("\ninput reference string size:");
    scanf("%d", &n);
    printf("\ninput reference string:");
    for (int i = 0; i < n; i++)
        scanf("%d", &ref_string[i]);
    int page_fault = 0;
    for (int i = 0; i < n; i++)
    {
        int page_no = ref_string[i];
        if (search(page_no) == 0)
        {
            page_fault++;
            if (q_size < no_of_frames)
            {
                push(page_no);
            }
            else
            {
                pop();
                push(page_no);
            }
        }
    }
    printf("\nOUTPUT-");
    printf("\nno. of page faults:%d\n", page_fault);
}