#include <stdio.h>
#define MAX 100

int np;
int q;

struct process
{
	char pid[3];
	int burst;
	int arrival;
	int turnaround;
	int waiting;
	int remaining;
	int flag;

} p[10], item;

/*-------------------------------------------------------------------*/
struct process RQ[100];
int fron = -1;
int rear = -1;

void enqueue(struct process item)
{
	if (rear == MAX-1)
	{
		printf("Queue full, cannot add item \n");
	}
	else
	{
		rear++;
		RQ[rear] = item;
		if (fron == -1)
		{
			fron = 0;
		}
	}
}
struct process dequeue()
{
	struct process pr;
	if (fron == -1)
	{
		printf("Queue Empty\n");
		
		return pr;
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
/*-------------------------------------------------------------------*/


int tot_burst()
{
	int tot_burst = 0;
	for (int i = 0; i < np; ++i)
		tot_burst += p[i].burst;
	return tot_burst;
}

void sortarrival()
{
	struct process temp;
	for (int i = 0; i < np-1; ++i)
	{
		for (int j = 0; j < np-i-1; ++j)
		{
			if (p[j].arrival>p[j+1].arrival)
			{
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}
}

/*-------------------------------------------------------------------*/

void getInput()
{
	printf("Enter time quantum : ");
	scanf("%d",&q);

	for (int i = 0; i < np; ++i)
	{
		printf("Enter pid, arrival, burst for process %d : ",i+1);
		scanf(" %s %d %d",p[i].pid, &p[i].arrival, &p[i].burst);
		p[i].turnaround = 0;
		p[i].waiting = 0;
		p[i].remaining = p[i].burst;
		p[i].flag = 0;
	}

}

void printtable()
{
	printf("\n\nProcess Table:\n");
    printf("+-----+---------------+-------------+---------------+-----------------+\n");
    printf("| PID | Arrival Time  | Burst Time  | Waiting Time  | Turnaround Time |\n");
    printf("+-----+---------------+-------------+---------------+-----------------+\n");
    for (int i = 0; i < np; i++)
    {
        printf("| %3s | %13d | %11d | %13d | %15d |\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }
    printf("+-----+---------------+-------------+---------------+-----------------+\n");
}

void printQlong()
{	
	if (fron == rear+1)
	{
		printf("Current Queue :\n");
		printf("Empty\n");
	}
	else
	{
		printf("Current Queue : \n");
		printf("| PID | Arrival Time  | Burst Time  | Waiting Time  | Turnaround Time |\n");
		for (int k = fron; k <= rear; ++k)
		{
			printf("| %3s | %13d | %11d | %13d | %15d |\n", RQ[k].pid, RQ[k].arrival, RQ[k].burst, RQ[k].waiting, RQ[k].turnaround);
		}
	}
}

void printQshort()
{	
	if (fron == rear+1)
	{
		printf("Current Queue :\n");
		printf("Empty\n");
	}
	else
	{
		printf("Current Queue : \n");
		for (int k = fron; k <= rear; ++k)
		{
			printf("%s | ",RQ[k].pid);
		}
		printf("\n");
	}
}
/*-------------------------------------------------------------------*/

void roundRobin()
{
	struct process exec;
	int tottime = tot_burst();
	printf("%d\n",tottime);
	int t;
	sortarrival();
	//printf("0 |");
	for (int time = 0; time < tottime; time=time+q)
	{	
		int up = 0;
		for (int counter = 0; counter < np; ++counter)
		{
			if (p[counter].arrival <= time && p[counter].flag == 0)
			{
				p[counter].flag = 1;
				enqueue(p[counter]);
			}
		}
		
		exec = dequeue();
		if (exec.remaining < q)
		{
			time += exec.remaining;
			printf("%s | %d | ",exec.pid,time);
			up = 1;
		}
		else
		{
			printf("%s | %d | ",exec.pid,time);
			exec.remaining -= q;
		}
		if (exec.remaining > 0)
		{
			enqueue(exec);
		}
		if (up == 1)
		{
			time-=q;
		}
	}
}

void main()
{
	struct process temper;
	printf("Enter number of processes : \n");
	scanf("%d",&np);
	getInput(np);
	roundRobin();

}


