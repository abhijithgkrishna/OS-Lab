#include <stdio.h>
int ref_string[20];
int no_of_frames;
typedef struct
{
    int page_no;
    int count; // no. of references
} pages_in_memory;
pages_in_memory pages[20];
int n = -1, size = 0;
void add_page(int item)
{
    pages_in_memory page;
    page.page_no = item;
    page.count = 1;
    pages[++n] = page;
    size++;
}
void remove_page() // removes page with least reference count
{
    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < size - i; j++)
        {
            if (pages[j].count > pages[j + 1].count)
            {
                pages_in_memory temp = pages[j];
                pages[j] = pages[j + 1];
                pages[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < size - 1; i++)
    {
        pages[i] = pages[i + 1];
    }
    size--;
}

int search(int item)
{
    for (int i = 0; i < size; i++)
    {
        if (pages[i].page_no == item)
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
        int pno = ref_string[i];
        if (search(pno) == 0)
        {
            page_fault++;
            if (size < no_of_frames)
            {
                add_page(pno);
            }
            else
            {
                remove_page();
                add_page(pno);
            }
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                if (pages[i].page_no == pno)
                {
                    pages[i].count++;
                    break;
                }
            }
        }
    }
    printf("\nOUTPUT-");
    printf("\nno. of page faults:%d\n", page_fault);
}