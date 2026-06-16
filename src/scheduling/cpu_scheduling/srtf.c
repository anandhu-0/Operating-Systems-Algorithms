#include<stdio.h>
#include<stdlib.h>

struct srtf{
    int pid;
    int at;
    int bt;
    int rbt;
    int ct;
    int tat;
    int wt;
    int iscompleted;
}p[10];

int main(){

    int no_of_processes;
    int current_time = 0;
    int completed = 0;
    //int k = 0;
    printf("enter no of processes: ");
    scanf("%d",&no_of_processes);
    for (int i = 0; i < no_of_processes; i++)
    {
        p[i].pid = i + 1;
        printf("enter arrival time and burst time of process P%d : ",i+1);
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i].rbt = p[i].bt;
        p[i].iscompleted = 0;

    }
    int gantt_pid[100];
    int gantt_time[100];
    int  g_loop = 0;
    while(completed < no_of_processes){

        int minrt =9999;
        int index = -1;

        for (int i = 0; i < no_of_processes; i++){
            if(p[i].at <= current_time && p[i].rbt > 0){
                if(p[i].rbt < minrt){
                    minrt = p[i].rbt;
                    index = i;
                }

            }
        }
        if(index == -1){
            current_time++;
            continue;
            
        }
        else{
            //if( g_loop == 0 || gantt_pid[ g_loop-1] != p[index].pid){
            gantt_time[ g_loop] = current_time;
            gantt_pid[ g_loop] = p[index].pid;
            g_loop++;

            //}
        }
        p[index].rbt--;
        current_time++;
        if(p[index].rbt == 0){
            p[index].iscompleted = 1;
            p[index].ct = current_time;
            completed++;
            
        }
    }
    gantt_time[g_loop] = current_time;

    float totalwt = 0, totaltat = 0, avgwt = 0, avgtat = 0;
    for(int i = 0; i < no_of_processes;i++){
        p[i].tat = p[i].ct - p[i].at;
        totaltat += p[i].tat;
        p[i].wt = p[i].tat - p[i].bt;
        totalwt += p[i].wt;
    }
    printf("\n------ SHORTED REMAINING TIME FIRST------\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < no_of_processes; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid, p[i].at, p[i].bt,
            p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Turnaround Time = %.2f", totaltat / no_of_processes);
    printf("\nAverage Waiting Time = %.2f", totalwt / no_of_processes);

    printf("\n-----gantt chart-------\n");
    printf("|");
    for(int i = 0;i <  g_loop;i++){

        printf(" P%d |",gantt_pid[i]);
    }
    printf("\n%d",gantt_time[0]);
    for(int i = 1;i <= g_loop;i++){
        
            printf("%5d",gantt_time[i]);
        
    }
    return 0;
    
}