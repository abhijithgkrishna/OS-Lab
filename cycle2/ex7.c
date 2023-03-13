#include <stdio.h>
#define MAX 5

struct process * RQ[MAX];
int fron = -1;
int rear = -1;

void enqueue(struct process * item)
{
	if (rear == MAX-1)
	{
		printf("Queue full, cannot add item \n");
	}
	else if(fron == -1 && rear == -1)
	{
		fron = 0;
		rear = 0;
		RQ[rear] = item;
	}
	else
	{
		rear++;
		RQ[rear] = item;
	}
}
struct process *  dequeue()
{
	struct process * pr;
	if (fron == -1)
	{
		printf("Queue Empty\n");
		return NULL;
	}
	else
	{
		pr = RQ[fron++];
		if (fron == rear+1)
		{
			fron = -1;
			rear = -1; 
		}
	}
	return pr;
}

struct process
{
	char pid[3];
	int burst;
	int arrival;

} p[10] ;



void main()
{
	int np, tot_burst = 0, q,time = 0;
	printf("Enter number of processes : \n");
	scanf("%d",&np);
	for (int i = 0; i < np; ++i)
	{
		printf("Enter pid, arrival, burst for process %d : ",i+1);
		scanf(" %s %d %d",p[i].pid, &p[i].arrival, &p[i].burst);
	}
	printf("Enter time quantum : ");
	scanf("%d",&q);

	// printf("pid \t arrival \t burst \n");
	// for (int i = 0; i < np; ++i)
	// {
	// 	printf("%s \t %d \t %d\n",p[i].pid, p[i].arrival, p[i].burst);
	// }

	for (int i = 0; i < np; ++i)
		tot_burst += p[i].burst;
	

	while(time < tot_burst)
	{
		
		time =+ q;
	}
}