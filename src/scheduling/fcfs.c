#include<stdio.h>
#include<stdlib.h>
struct fcfs{
   int pid; 
   int At;
   int Bt;
   int Ct;
   int Tat;
   int Wt;
}p[10],temp[10];
int main(){ 
    int no_of_process;
    float avgwt,avgtat = 0;
    float totalwt,totaltat = 0;
    printf("enter number of processes: ");
    scanf("%d",&no_of_process);
    
    for (int i = 0; i < no_of_process; i++)
    {
       p[i].pid=i+1; 
       printf("enter arrival time burst time of process: ",i+1);
       scanf("%d%d",&p[i].At,&p[i].Bt);
    }
    for (int i = 0; i < no_of_process; i++)
    {
        for (int j = 0; j < no_of_process-i-1; j++)
        {
            if(p[j].At > p[j+1].At){
            temp[j] = p[j];
            p[j] = p[j+1];
            p[j+1] = temp[j]; 
        }
        }
        
        
    }
    p[0].Ct = p[0].At + p[0].Bt;
    for (int i = 1; i < no_of_process; i++)
    {
        p[i].Ct = p[i-1].Ct + p[i].Bt;

    }
    for (int i = 0; i < no_of_process; i++)
    {
        p[i].Tat = p[i].Ct - p[i].At;
        totaltat+=p[i].Tat;
        
    }
    for (int i = 0; i < no_of_process; i++)
    {
        p[i].Wt = p[i].Tat - p[i].Bt;
        totalwt+=p[i].Wt;
    }
    avgtat = totaltat/no_of_process;
    avgwt = totalwt/no_of_process;


    printf("FCFS SCHEDULING :\n");
    printf("PID\t AT\t BT\t CT\t TAT\t WT\n");
    for (int i = 0; i < no_of_process; i++)
    {
        printf("%d\t %d\t %d\t %d\t %d\t %d\t",p[i].pid,p[i].At,p[i].Bt,p[i].Ct,p[i].Tat,p[i].Wt);
        printf("\n");
    }
    printf("average turn around time is: %.2f\n",avgtat);
    printf("average waiting time is: %.2f\n",avgwt);


    printf("------gantt chart :------\n");
    int time = p[0].At;

    for (int i = 0; i < no_of_process; i++)
    {
        if(time < p[i].At){
            printf(" idle|");
            time = p[i].At;
        }
        printf("P%d|",p[i].pid);
        time+=p[i].Bt;
    }
    printf("\n0");
    time = p[0].At;
    for (int i = 0; i < no_of_process; i++)
    {
        if(time < p[i].At){
            printf("    %d",p[i].At);
            time = p[i].At;
        }
        printf(" %d   ",p[i].Ct);
        time+=p[i].Bt;
    }
}