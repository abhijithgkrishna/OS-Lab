#include <stdio.h>
#define MAX 10

struct Process
{
    int pid; // process id
    int at;  // arrival time
    int bt;  // burst time
    int rt;  // remaining time
    int wt;  // waiting time
    int tat; // turnaround time
} process, processes[MAX];

int front = 0, rear = 0, ready_queue[MAX];

int n, q, ct = 0, et, cp; // no of process, quantum time, current time, execution time, current process

void sort()
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].at > processes[j + 1].at) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}
void enqueue(int pid)
{
    ready_queue[rear] = pid;
    rear = (rear + 1) % MAX;
}

int dequeue()
{
    int pid = ready_queue[front];
    front = (front + 1) % MAX;
    return pid;
}

void round_robin()
{
    enqueue(processes[0].pid);
    if (processes[cp].at != 0)
        ct=processes[cp].at;
    printf("\nGantt Chart:\n");
    while (front != rear)
    {
        cp = dequeue() - 1;
        et = processes[cp].rt < q ? processes[cp].rt : q;
        processes[cp].rt -= et;
        ct += et;
        printf("%d | P%d | ", ct - et, processes[cp].pid);
        for (int i = 0; i < n; i++)
        {
            if (processes[i].at > ct - et && processes[i].at <= ct)
                enqueue(processes[i].pid);
        }
        if (processes[cp].rt > 0)
        {
            enqueue(processes[cp].pid);
            processes[cp].tat = ct - processes[cp].at;
            processes[cp].wt += ct - processes[cp].at - processes[cp].tat;
        }
        else
        {
            processes[cp].tat = ct - processes[cp].at;
            processes[cp].wt = processes[cp].tat - processes[cp].bt;
        }
        if (front == rear)
        {
            for (int i = 0; i < n; i++)
            {
                if (processes[i].at > ct)
                {
                    enqueue(processes[i].pid);
                    printf("%d | idle | ", ct);
                    ct = processes[i].at;
                    break;
                }
            }
        }
    }
    printf("%d", ct);
}

int main()
{
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
        processes[i].pid = i + 1;
        processes[i].rt = processes[i].bt;
    }
    printf("Enter time quantum: ");
    scanf("%d", &q);
    sort();
    printf("Sorted processes based on increasing order of at:\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", processes[i].pid, processes[i].at, processes[i].bt);
    }
    round_robin();
    printf("\n\nProcess Table:\n");
    printf("+-----+---------------+-------------+---------------+-----------------+\n");
    printf("| PID | Arrival Time  | Burst Time  | Waiting Time  | Turnaround Time |\n");
    printf("+-----+---------------+-------------+---------------+-----------------+\n");
    for (int i = 0; i < n; i++)
    {
        printf("| %3d | %13d | %11d | %13d | %15d |\n", processes[i].pid, processes[i].at, processes[i].bt, processes[i].wt, processes[i].tat);
    }
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
    return 0;
}