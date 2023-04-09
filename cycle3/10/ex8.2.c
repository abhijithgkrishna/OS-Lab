#include <stdio.h>
int ref_string[20];
int no_of_frames;
int stack[100], top = -1, size = 0;
void push(int item)
{
    top++;
    stack[top] = item;
    size++;
}
void pop_from_bottom()
{
    for (int i = 0; i < top; i++)
    {
        stack[i] = stack[i + 1];
    }
    top--;
    size--;
}
int search(int item)
{
    for (int i = 0; i <= top; i++)
    {
        if (stack[i] == item)
        {
            return i;
        }
    }
    return -1;
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
        int index = search(page_no);
        if (index == -1)
        {
            page_fault++;
            if (size < no_of_frames)
            {
                push(page_no);
            }
            else
            {
                pop_from_bottom();
                push(page_no);
            }
        }
        else
        {
            int temp = stack[index];
            for (int i = index; i < top; i++)
            {
                stack[i] = stack[i + 1];
            }
            stack[top] = temp;
        }
        printf("\npages in memory:");
        for (int i = 0; i <= top; i++)
        {
            printf("%d ", stack[i]);
        }
    }
    printf("\n\nOUTPUT-");
    printf("\nno. of page faults:%d\n", page_fault);
}
