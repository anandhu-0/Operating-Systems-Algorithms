#include <stdio.h>
struct rr
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
} p[10];
int main()
{
    int n, time_quantum;
    int time = 0, completed = 0;
    float totaltat = 0, totalwt = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
        p[i].rt = p[i].bt;
    }
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);
    int queue[100], front = 0, rear = 0;
    int visited[10] = {0};
    
    int gantt_pid[100], gantt_time[100];
    int k = 0;
    while (completed < n)
    {
        // Add newly arrived processes to queue
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].rt > 0 && visited[i] == 0)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
        if (front == rear)
        {
            time++;
            continue;
        }
        int idx = queue[front++];
        int exec_time = (p[idx].rt > time_quantum) ? time_quantum : p[idx].rt;
        time += exec_time;
        p[idx].rt -= exec_time;
        gantt_pid[k] = p[idx].pid;
        gantt_time[k] = time;
        k++;
        
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].rt > 0 && visited[i] == 0)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
        if (p[idx].rt > 0)
        {
            queue[rear++] = idx;  // push back
        }
        else
        {
            p[idx].ct = time;
            completed++;
        }
    }
    // Calculate TAT and WT
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        totaltat += p[i].tat;
        totalwt += p[i].wt;
    }
    printf("\n------ ROUND ROBIN ------\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Turnaround Time = %.2f", totaltat / n);
    printf("\nAverage Waiting Time = %.2f", totalwt / n);
    
    printf("\n\n-----GANTT CHART-----\n|");
    for (int i = 0; i < k; i++)
        printf(" P%d |", gantt_pid[i]);
    printf("\n0");
    for (int i = 0; i < k; i++)
        printf("   %d", gantt_time[i]);
    printf("\n");
    return 0;
}
