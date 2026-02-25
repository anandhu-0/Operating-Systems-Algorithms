#include<stdio.h>

struct priority
{
    int pid;
    int at;
    int bt;
    int pr;
    int ct;
    int tat;
    int wt;
    int iscompleted;
}p[10], q[10];

int main(){
    int no_of_process;
    float totaltat = 0, totalwt = 0;
    float avgtat = 0, avgwt = 0;

    printf("enter number of processes: ");
    scanf("%d", &no_of_process);

    for(int i = 0; i < no_of_process; i++){
        p[i].pid = i + 1;
        printf("enter arrival time, burst time and priority of process P%d: ", i+1);
        scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].iscompleted = 0;
    }

    int time = 0;
    int completed = 0;
    int j = 0;

    while(completed < no_of_process){
        int indx = -1;
        int minPR = 9999;

        for(int i = 0; i < no_of_process; i++){
            if(p[i].at <= time && p[i].iscompleted == 0){
                if(p[i].pr < minPR){
                    minPR = p[i].pr;
                    indx = i;
                }
                else if(p[i].pr == minPR){
                    if(p[i].at < p[indx].at){
                        indx = i;
                    }
                }

            }
        }

        if(indx == -1){
            time++;
            continue;
        }

        time += p[indx].bt;
        p[indx].ct = time;
        p[indx].iscompleted = 1;
        q[j].pid = p[indx].pid;
        completed++;
        j++;
    }

    for(int i = 0; i < no_of_process; i++){
        p[i].tat = p[i].ct - p[i].at;
        totaltat += p[i].tat;
    }
    for(int i = 0; i < no_of_process; i++){
        p[i].wt = p[i].tat - p[i].bt;
        totalwt += p[i].wt;
    }

    avgtat = totaltat / no_of_process;
    avgwt  = totalwt  / no_of_process;

    printf("\nNON PREEMPTIVE PRIORITY SCHEDULING :\n");
    printf("PID\t AT\t BT\t PR\t CT\t TAT\t WT\n");
    for(int i = 0; i < no_of_process; i++){
        printf("%d\t %d\t %d\t %d\t %d\t %d\t %d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("average turnaround time: %.2f\n", avgtat);
    printf("average waiting time:    %.2f\n", avgwt);

    printf("\n------gantt chart:------\n|");
    for(int i = 0; i < no_of_process; i++){
        printf(" P%d |", q[i].pid);
    }
    printf("\n0");
    for(int i = 0; i < no_of_process; i++){
        for(int k = 0; k < no_of_process; k++){
            if(q[i].pid == p[k].pid){
                printf("%4d", p[k].ct);
            }
        }
    }
    printf("\n");

    return 0;
}