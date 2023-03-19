#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct process
{
    int pid, arrival, burst, wait, turn;
    int temp, priority;
} process;
int k = 0;
int *pid;
int *time;

void sort(process *p, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (p[min].arrival > p[j].arrival)
                min = j;
        }
        if (i != min)
        {
            process temp = p[i];
            p[i] = p[min];
            p[min] = temp;
        }
    }
}
void fcfs(process *p, int n)
{
    p[0].wait = 0;
    p[0].turn = p[0].burst;
    int sum = p[0].arrival;
    for (int i = 1; i < n; i++)
    {
        sum += p[i - 1].burst;
        p[i].wait = sum - p[i].arrival;
        if (p[i].wait < 0)
            p[i].wait = 0;
        p[i].turn = p[i].burst + p[i].wait;
    }
}
void gantt_chart(process *p, int n)
{
    printf("\n\n");
    for (int i = 0; i < p[n - 1].turn - 1; i++)
    {
        printf(" ");
    }
    printf("GANTT CHART\n\n ");
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");
        printf("P%d", i + 1);
        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("--");
        printf(" ");
    }
    printf("\n%d", p[0].arrival);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("  ");
        if (p[i].turn + p[i].arrival > 9)
            printf("\b");
        printf("%d", p[i].turn + p[i].arrival);
    }
    printf("\n");
}
void average(process *p, int n)
{
    float sumw = 0, sumt = 0;
    for (int i = 0; i < n; i++)
    {
        sumw += p[i].wait;
        sumt += p[i].turn;
    }
    printf("\n\nAverage Waiting Time = %0.3f", sumw / n);
    printf("\nAverage Turnaround Time = %0.3f\n", sumt / n);
}
void fcfsmain()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process p[10];
    printf("Enter the arrival times of Processes:");
    for (int i = 0; i < n; i++)
        scanf("%d", &p[i].arrival);
    printf("Enter the burst times of Processes:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].burst);
        p[i].pid = i + 1;
    }
    sort(p, n);
    fcfs(p, n);
    printf("\n\n First Come First Served(FCFS) scheduling");
    printf("\n-----------------------------------------------------------------------------\n");
    printf("Processes Arrival time\tBurst time\tWaiting time\tTurnaround time\n");
    printf("-----------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf(" P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].wait, p[i].turn);
    }

    printf("-----------------------------------------------------------------------------\n");
    gantt_chart(p, n);
    average(p, n);
}
void sort_arrival_time(process *p, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (p[min].arrival > p[j].arrival)
                min = j;
        }
        if (i != min)
        {
            process temp = p[i];
            p[i] = p[min];
            p[min] = temp;
        }
    }
}
void round_robin(process *p, int n, int quantum)
{

    int rem[10];
    for (int i = 0; i < n; i++)
        rem[i] = p[i].burst;
    int previous = p[0].arrival;
    while (1)
    {
        int flag = 0;
        int i;
        int min = 0;
        for (i = 0; i < n; i++)
        {

            if (rem[i] > 0)
            {
                if (p[i].temp <= p[min].temp)
                    min = i;
            }
        }
        if (rem[min] > 0)
        {
            flag = 1;
            if (rem[min] > quantum)
            {
                previous += quantum;
                rem[min] -= quantum;
            }
            else
            {
                previous += rem[min];
                p[min].wait = previous - p[min].burst - p[min].arrival;
                rem[min] = 0;
                p[min].turn = p[min].burst + p[min].wait;
            }
            p[min].temp = previous;
            pid[k] = p[min].pid;
            time[k++] = p[min].temp;
        }
        if (!flag)
            break;
    }
}
void gantt(process *p, int n, int size)
{
    printf("\n\n");
    for (int i = 0; i < (time[size - 1] * 2 + size - 11) / 2; i++)
        printf(" ");
    printf("GANTT CHART\n\n ");
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < time[i] - time[i - 1]; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < time[i] - time[i - 1] - 1; j++)
            printf(" ");
        printf("P%d", pid[i]);
        for (j = 0; j < time[i] - time[i - 1] - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < time[i] - time[i - 1]; j++)
            printf("--");
        printf(" ");
    }
    printf("\n%d", p[0].arrival);
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < time[i] - time[i - 1]; j++)
            printf("  ");
        if (time[i] > 9)
            printf("\b");
        printf("%d", time[i]);
    }
    printf("\n");
}

void rrmain()
{
    process *p;
    int n, quantum, size = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    p = (process *)malloc(sizeof(process) * n);
    printf("Enter the time quantum : ");
    scanf("%d", &quantum);
    printf("Enter the arrival times of Processes:");

    for (int i = 0; i < n; i++)
        scanf("%d", &p[i].arrival);
    printf("Enter the burst times of Processes:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].burst);
        p[i].pid = i + 1;
        p[i].temp = p[i].arrival;
        float f = p[i].burst / (float)quantum;
        size += ceil(f);
    }
    pid = (int *)malloc(sizeof(int) * size);
    time = (int *)malloc(sizeof(int) * size);
    sort_arrival_time(p, n);
    round_robin(p, n, quantum);
    printf("\n\n ROUND ROBIN SCHEDULING");
    printf("\n-----------------------------------------------------------------------------\n");
    printf("Processes Arrival time\tBurst time\tWaiting time\tTurnaround time\n");
    printf("-----------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf(" P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival,
               p[i].burst, p[i].wait, p[i].turn);
    }
    printf("-----------------------------------------------------------------------------\n");
    gantt(p, n, size);
    average(p, n);
}
void priority(process *p, int n)
{
    int previous = p[0].arrival;
    for (int i = 0; i < n; i++)
    {
        int min = p[i].priority;
        int min_index = i;
        int flag = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (p[j].arrival > previous)
                break;
            if (p[j].priority < min)
            {
                min = p[j].priority;
                min_index = j;
                flag = 1;
            }
        }
        if (flag == 1)
        {
            process temp = p[i];
            p[i] = p[min_index];
            p[min_index] = temp;
        }
        p[i].wait = previous - p[i].arrival;
        if (p[i].wait < 0)
            p[i].wait = 0;
        p[i].turn = p[i].burst + p[i].wait;
        previous = p[i].arrival + p[i].turn;
    }
}

void pmain()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process p[10];
    printf("Enter the arrival times of Processes:");
    for (int i = 0; i < n; i++)
        scanf("%d", &p[i].arrival);
    printf("Enter the burst times of Processes:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].burst);
        p[i].pid = i + 1;
    }
    printf("Enter the priorities of Processes:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].priority);
    }

    sort_arrival_time(p, n);
    priority(p, n);
    printf("\n\n PRIORITY SCHEDULING");
    printf("\n----------------------------------------------------------------------------------------\n");
    printf("Processes Arrival time\tBurst time\tPriority\tWaiting time\tTurnaround time\n");
    printf("----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf(" P%d\t\t%d\t\t%d\t %d\t\t%d\t\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst, p[i].priority,
               p[i].wait, p[i].turn);
    }
    printf("-----------------------------------------------------------------------------------\n");
    gantt_chart(p, n);
    average(p, n);
}

void sjfs(process *p, int n)
{
    int previous = p[0].arrival;
    for (int i = 0; i < n; i++)
    {
        int min = p[i].burst;
        int min_index = i;
        int flag = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (p[j].arrival > previous)
                break;
            if (p[j].burst < min)
            {
                min = p[j].burst;
                min_index = j;
                flag = 1;
            }
        }
        if (flag == 1)
        {
            process temp = p[i];
            p[i] = p[min_index];
            p[min_index] = temp;
        }
        p[i].wait = previous - p[i].arrival;
        if (p[i].wait < 0)
            p[i].wait = 0;
        p[i].turn = p[i].burst + p[i].wait;
        previous = p[i].arrival + p[i].turn;
    }
}

void sjfsmain()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process p[10];
    printf("Enter the arrival times of Processes:");
    for (int i = 0; i < n; i++)
        scanf("%d", &p[i].arrival);
    printf("Enter the burst times of Processes:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].burst);
        p[i].pid = i + 1;
    }
    sort_arrival_time(p, n);
    sjfs(p, n);
    printf("\n\n Shortest Job First(SJF) SCHEDULING");
    printf("\n-----------------------------------------------------------------------------\n");
    printf("Processes Arrival time\tBurst time\tWaiting time\tTurnaround time\n");
    printf("-----------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf(" P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid,
               p[i].arrival, p[i].burst, p[i].wait, p[i].turn);
    }
    printf("-----------------------------------------------------------------------------\n");
    gantt_chart(p, n);
    average(p, n);
}

void main()
{
    printf("Choose algorithm : \n");
    int choice;
    printf("1.Round Robin\n2.FCFS \n3.SJF \n4.Priority SCHEDULING\n5.exit\n");
    printf("Enter choice : ");
    scanf("%d", &choice);
    while (choice != 5)
    {
        if (choice == 1)
            rrmain();
        else if (choice == 2)
            fcfsmain();
        else if (choice == 3)
            sjfsmain();
        else if (choice == 4)
            pmain();
        printf("Enter choice: ");
        scanf("%d", &choice);
    }
}