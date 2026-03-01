#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){

    int alloc[20][20],avail[20],max[20][20],need[20][20],work[20];

    int no_of_process;
    printf(" enter no of processes: ");
    scanf("%d",&no_of_process);
    int no_of_res_type;
    printf(" enter no of resource type: ");
    scanf("%d",&no_of_res_type);
    printf("\n");
    printf("\n enter allocation matrix: \n");
    for(int i = 0;i <no_of_process;i++){
        for(int j = 0;j < no_of_res_type;j++){
            scanf("%d",&alloc[i][j]);

        }

    }
    printf("\n enter max matrix: ");
    for (int i = 0; i < no_of_process; i++)
    {
        for(int j =0;j<no_of_res_type;j++){
            scanf("%d",&max[i][j]);

        }

    }

    printf("\n enter available resources: ");
    for(int i = 0;i < no_of_res_type;i++){
        scanf("%d",&avail[i]);
    }
    
    printf("\n allocation matrix: \n");
    for(int i = 0;i <no_of_process;i++){
        for(int j = 0;j < no_of_res_type;j++){
            printf("%4d",alloc[i][j]);

        }
        printf("\n");

    }
    printf("\n max matrix: \n ");
    for (int i = 0; i < no_of_process; i++)
    {
        for(int j =0;j<no_of_res_type;j++){
            printf("%4d",max[i][j]);

        }
        printf("\n");
        
    }
    printf("\n available resources: \n");
    for(int i = 0;i < no_of_res_type;i++){
        printf("%4d",avail[i]);
    }
    for(int i = 0;i < no_of_process;i++){
        for(int j = 0;j < no_of_res_type;j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    printf("\n need matrix : \n ");
    for(int i = 0;i < no_of_process;i++){
        for(int j = 0;j < no_of_res_type;j++){
            printf("%4d",need[i][j]);
        }
        printf("\n");
    }

    int finished[no_of_process];
    int safeseq[no_of_process];

    for(int i = 0;i < no_of_res_type;i++){
            work[i] = avail[i];
        }
    for(int i = 0;i < no_of_process;i++){
        finished[i] = 0;
    }
    int changed = 0;
    int found = 0;
    while(changed < no_of_process){

        for(int i = 0;i < no_of_process;i++){

            int flag = 0;
            if(finished[i] == 0){
                for(int j =0;j < no_of_res_type;j++){
                    if(need[i][j] > work[j]){
                        flag = 1;
                        break;
                    }

                }
                if(flag == 0){

                    safeseq[changed++] = i;
                    finished[i] = 1;
                    found = 1;
                    for(int k = 0;k < no_of_res_type;k++){
                        work[k]+=alloc[i][k];
                    }
                }
            }
            
            
        }
        if(found == 0){
        printf("system is not safe...\n");
        return 0;
        }
        
    } 
    printf("\n system is safe..");
    printf("\n safe sequence: ");
    printf("\n |");
    for(int i = 0;i < no_of_process;i++){
        printf("P%d |",safeseq[i]);
    }   

    return 0;
}