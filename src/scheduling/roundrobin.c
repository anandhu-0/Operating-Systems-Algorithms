#include<stdio.h>

struct rr
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    

}p[10],temp[10];
int main(){
    int time_quantum;
    int no_of_process;
    float totaltat = 0,totalwt = 0;
    float avgtat = 0,avgwt = 0;
    printf("enter no of processes: ");
    scanf("%d",&no_of_process);
    for (int i = 0; i < no_of_process; i++)
    {
        printf("enter process P%d's arrival time and burst time " ,i+1);
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i].pid=i+1;
        p[i].rt = p[i].bt;

    }
    printf("enter time quantum: ");
    scanf("%d",&time_quantum);

    int completed = 0;
    int time = 0;
    int k = 0;
    int qpid[10] ;
    int qct[10] ;
    while (completed < no_of_process){

        int executed = 0;
        for (int i = 0; i < no_of_process; i++)
        {
            if(p[i].at <= time && p[i].rt > 0){
                executed = 1;
                int exectime = p[i].rt > time_quantum ? time_quantum : p[i].rt;

                time+=exectime;
                p[i].rt-=exectime;
                qpid[k] = p[i].pid;
                qct[k] =time;
                k++;


                if(p[i].rt == 0){
                    p[i].ct = time;
                    completed++;
                }

            }
        }
        
         if(!executed) time++;
    }
    
         for (int i = 0; i < no_of_process; i++)
         {
            p[i].tat = p[i].ct - p[i].at;
            totaltat+=p[i].tat;
            p[i].wt = p[i].tat - p[i].bt;
            totalwt+=p[i].wt;
         }
         avgtat = totaltat / no_of_process;
         avgwt = totalwt / no_of_process;

         printf("-----round robin---------\n");
         printf("PID\t AT\t BT\t CT\t TAT\t WT\n");
         for (int i = 0; i < no_of_process; i++)
         {
           printf("%d\t %d\t %d\t %d\t %d\t %d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
         }
         printf("\n\n");
         printf("average tt : %.2f\n",avgtat);
         printf("average wt : %.2f\n",avgwt);

         
         
         printf("\n       GANNT CHART    \n");
         printf("|");
         for (int i = 0; i < k; i++)
         {
            printf("P%d  |",qpid[i]);
         }
         printf("\n0");
         for (int i = 0; i < k; i++)
         {
            printf("   %d",qct[i]);
         }
         
        
   

    return 0;
    
}
