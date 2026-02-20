#include<stdio.h>

struct sjf
{
    int PID;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int iscompleted;
}p[10],temp[10],q[10];

int main(){
    int completed = 0;
    int no_of_processes;
    printf("enter no of processes: ");
    scanf("%d",&no_of_processes);
    for (int i = 0; i < no_of_processes; i++)
    {
        p[i].PID=i+1;
        printf("enter  process %d arrival time and burst time: ",i+1);
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i].iscompleted = 0;
    }
    int time = 0;
    int j = 0;
    while(completed < no_of_processes){
        int minBT = 9999;
        int indx = -1;
        
        for (int i = 0; i < no_of_processes; i++)
        {
            if(p[i].at <= time && p[i].iscompleted ==0){
                if(p[i].bt < minBT){
                    minBT = p[i].bt;
                    indx = i;
                }

            }
        }
        if(indx == -1){
            time++;
            continue;
        }
        
        time+=p[indx].bt;
        q[j].PID = p[indx].PID;
        p[indx].ct = time;
        p[indx].iscompleted = 1;
        completed++;
        j++;

    }
    float totaltat =0,totalwt =0;
    float avgtat =0,avgwt = 0;
    for (int i = 0; i < no_of_processes; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        totaltat+=p[i].tat;
        
    }
    for (int i = 0; i < no_of_processes; i++)
    {
        p[i].wt = p[i].tat - p[i].bt;
        totalwt+=p[i].wt;
    }
    avgtat = totaltat/no_of_processes;
    avgwt = totalwt/no_of_processes;

    for (int i = 0; i < no_of_processes; i++)
    {
        for (int j = 0; j < no_of_processes; j++)
        {
            if(p[i].wt < p[j].wt){
                temp[i] = p[i];
                p[i] = p[j];
                p[j] = temp[i];
            }
        }
        
    }
    
    printf("SJF scheduling : \n");
    printf("PID\t AT\t BT\t CT\t TAT\t WT\n");
    for (int i = 0; i < no_of_processes; i++)
    {
        
        printf("%d\t %d\t %d\t %d\t %d\t %d\n",p[i].PID,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    printf("average turnaround time: %.2f\n",avgtat);
    printf("average waiting time: %.2f\n",avgwt);

    printf("|");
    for (int i = 0; i < no_of_processes; i++)
    {
        for (int k = 0; k < no_of_processes; k++)
        {
            if(q[i].PID == p[k].PID){
                printf("P%d |",p[i].PID);
            }
        }
        
    }
    printf("\n0");
    for (int i = 0; i < no_of_processes; i++)
    {
        for (int k = 0; k < no_of_processes; k++)
        {
            if(q[i].PID == p[k].PID){
                printf("  %d",p[i].ct);
            }
        }
        
    }
    return 0;
}