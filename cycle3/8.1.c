//Page replacement algorithms
//FIFO
#include<stdio.h>

int isIn(int item, int arr[], int n){
	// function returns -1 if item is not in arr[] of size n
	for (int i = 0; i < n; ++i)
	{
		if (arr[i] == item)
		{
			return i;
		}
	}
	return -1;
}


void main()
{
	int fr_size, no_of_pages, page_fault=0;
	int pages[100];
	int fr_count = 0;
	printf("Enter frame size : ");
	scanf("%d",&fr_size);
	//initializing frames array
	int frames[fr_size];
	for (int i = 0; i < fr_size; ++i)
		frames[i] = -1;

	//initializing pages
	printf("Enter number of pages : ");
	scanf("%d",&no_of_pages);
	printf("Enter page referencing string : ");
	for (int i = 0; i < no_of_pages; ++i)
		scanf("%d",&pages[i]);


	//printing table header
	printf("Incoming ");
	for (int j = 0; j < fr_size; ++j)
	{
		printf("\t Frame %d",j+1 );
	}
	printf("\n");

	for (int i = 0; i < no_of_pages; ++i)
	{
		//if next number is not in frames array, update array using fifo
		if (isIn(pages[i],frames,fr_size) == -1)
		{
			page_fault++;
			frames[fr_count] = pages[i];
			fr_count = (fr_count + 1)%fr_size; 
		}
		printf("%d ", pages[i]);
		for (int i = 0; i < fr_size; ++i)
		{
			printf("\t\t %d",frames[i]);
		}
		printf("\n");
	}
	printf("No of page page faultS = %d \n", page_fault);
}