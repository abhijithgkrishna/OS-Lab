#include <stdio.h>
#define MAX 10

struct Process
{
    int pid; // process id
    int at;  // arrival time
    int bt;  // burst time
    int p;   // priority
    int rt;  // remaining time
    int wt;  // waiting time
    int tat; // turnaround time
} temp, processes[MAX], *ready_queue[MAX], *cp, *p;

int front = 0, rear = 0; // ready queue
int n, q, ct = 0, et;    // no of process, quantum time, current time, execution time, current process

void sort()
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].at > processes[j + 1].at)
            {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void enqueue(struct Process *p)
{
    ready_queue[rear] = p;
    rear = (rear + 1) % MAX;
}

struct Process *dequeue()
{
    p = ready_queue[front];
    front = (front + 1) % MAX;
    return p;
}

void round_robin()
{
    enqueue(&processes[0]);
    printf("\nGantt Chart:\n");
    if (processes[0].at != 0)
        ct = processes[0].at;
        
    while (front != rear)
    {
        cp = dequeue();
        for (int i = 0; i < n; i++)
        {
            if (processes[i].at == cp->at && cp->pid != processes[i].pid)
                enqueue(&processes[i]);
        }
        et = cp->rt < q ? cp->rt : q;
        cp->rt -= et;
        ct += et;
        printf("%d | P%d | ", ct - et, cp->pid);
        for (int i = 0; i < n; i++)
        {
            if (processes[i].at > ct - et && processes[i].at <= ct && cp != &processes[i])
                enqueue(&processes[i]);
        }

        if (cp->rt > 0)
        {
            enqueue(cp);
            cp->tat = ct - cp->at;
            cp->wt += ct - cp->at - cp->tat;
        }
        else
        {
            cp->tat = ct - cp->at;
            cp->wt = cp->tat - cp->bt;
        }
        if (front == rear)
        {
            for (int i = 0; i < n; i++)
            {
                if (processes[i].at > ct)
                {
                    enqueue(&processes[i]);
                    printf("%d | idle | ", ct);
                    ct = processes[i].at;
                    break;
                }
            }
        }
    }
    printf("%d", ct);
}

void sjf()
{
    printf("\nGantt Chart:\n");
    int completed = 0, prev = -1,curr = -1, ct = 0;
    while (completed <= n - 1)
    {
        curr = -1;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].at > ct)
                break;
            if (processes[i].at <= ct && processes[i].rt > 0 && (curr == -1 || processes[i].rt < processes[curr].rt))
                curr = i;
        }
        if (curr != -1)
        {
            if (prev != curr)
                printf("%d | P%d | ", ct, processes[curr].pid);
            processes[curr].rt--;
            ct++;
            if (processes[curr].rt == 0)
            {
                completed++;
                processes[curr].tat = ct - processes[curr].at;
                processes[curr].wt = processes[curr].tat - processes[curr].bt;
            }
            prev = curr;
        }
        else
        {
            if (curr != prev)
                printf("%d | IDLE | ", ct);
            prev = -1;
            ct++;
        }
    }
    printf("%d", ct);
}

void fcfs()
{
    printf("\nGantt Chart:\n");
    ct = processes[0].at;
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            processes[i].wt = 0;
            processes[i].tat = processes[i].bt;
            printf("%d | p%d |", ct, processes[i].pid); 
            ct += processes[i].bt;
        }
        else
        {
            if (ct < processes[i].at)
            {
                printf("%d | IDLE |", ct); 
                ct = processes[i].at;
            }
            printf(" %d | p%d |", ct, processes[i].pid); 
            processes[i].wt = ct - processes[i].at;
            processes[i].tat = processes[i].wt + processes[i].bt;
            ct += processes[i].bt;
        }
    }
    printf("%d", ct);
}

void priority()
{
    printf("\nGantt Chart:\n");
    int completed = 0,ct=processes[0].at, curr = -1, prev = -1;
    while (completed <= n-1)
    {
        curr = -1;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].at > ct)
                break;
            if (processes[i].at <= ct && processes[i].rt > 0 &&(curr == -1 || processes[i].p < processes[curr].p))
                curr = i;
        }
        if (curr != -1)
        {
            if (prev != curr)
                printf("%d | P%d | ", ct, processes[curr].pid);
            processes[curr].rt--;
            ct++;
            if (processes[curr].rt == 0)
            {
                completed++;
                processes[curr].tat = ct - processes[curr].at;
                processes[curr].wt = processes[curr].tat - processes[curr].bt;
                prev=-1;
            }
            else
                prev = curr;
        }
        else
        {
            printf("%d | IDLE | ", ct);
            ct++;
        }
    }
    printf("%d", ct);
}

void display()
{
    printf("\n\nProcess Table:\n");
    printf("+-----+---------------+-------------+---------------+-----------------+\n");
    printf("| PID | Arrival Time  | Burst Time  | Waiting Time  | Turnaround Time |\n");
    printf("+-----+---------------+-------------+---------------+-----------------+\n");
    for (int i = 0; i < n; i++)
        printf("| %3d | %13d | %11d | %13d | %15d |\n", processes[i].pid, processes[i].at, processes[i].bt, processes[i].wt, processes[i].tat);
    printf("+-----+---------------+-------------+---------------+-----------------+\n");
    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++)
    {
        avg_wt += processes[i].wt;
        avg_tat += processes[i].tat;
    }
    avg_wt /= n;
    avg_tat /= n;
    printf("Average waiting time: %.2f\n", avg_wt);
    printf("Average turnaround time: %.2f\n", avg_tat);
}

void input(int c)
{
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    if (c != 4)
        for (int i = 0; i < n; i++)
        {
            printf("Enter arrival time and burst time for process %d: ", i + 1);
            scanf("%d %d",&processes[i].at,&processes[i].bt);
            processes[i].pid = i + 1;
            processes[i].rt = processes[i].bt;
        }
    else
        for (int i = 0; i < n; i++)
        {
            printf("Enter arrival time, burst time and priority for process %d: ", i + 1);
            scanf("%d %d %d",&processes[i].at,&processes[i].bt,&processes[i].p);
            processes[i].pid = i + 1;
            processes[i].rt = processes[i].bt;
        }
    if (c == 1)
    {
        printf("Enter time quantum: ");
        scanf("%d", &q);
    }
}

int main()
{
    int choice;
    printf("1. Round Robin\n2. SJF\n3. FCFS\n4. Priority\nEnter your choice:");
    scanf("%d", &choice);
    while (choice < 1 || choice > 4)
    {
        printf("Invalid choice. Enter again: ");
        scanf("%d", &choice);
    }
    input(choice);
    sort();
    switch (choice)
    {
    case 1:
        round_robin();
        break;
    case 2:
        sjf();
        break;
    case 3:
        fcfs();
        break;
    case 4:
        priority();
        break;
    }
    display();
    return 0;
}