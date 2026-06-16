#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define num_r 3
#define num_w 5

sem_t resource;
sem_t wmutex;
sem_t rmutex;
sem_t readtry;

int readcount = 0;
int writecount = 0;

int shared_data = 0;

void *writer(void *args){

    int id = *(int *)args;

    sem_wait(&wmutex);  // protects write count
    writecount++;

    if(writecount == 1){

        sem_wait(&readtry);   //waits readers
    }

    sem_post(&wmutex);    

    sem_wait(&resource);    // locks resource
    shared_data+=10;
    printf(" \nwriter %d is writing shared data : %d",id,shared_data);
    sleep(2);
    sem_post(&resource);  // release resource

    printf("\nwriter %d has finished writing",id);
    sem_wait(&wmutex);
    writecount--;

    if(writecount == 0){
        sem_post(&readtry);
    }
    
    sem_post(&wmutex);

    return NULL;
}

void *reader(void *args){

    int id = *(int *)args;

    sem_wait(&readtry);  // check if any writers are holding
    sem_wait(&rmutex);   // if not protected readcount incrementer
    readcount++;

    if(readcount == 1){

        sem_wait(&resource);  // lock resource
    }
    sem_post(&readtry);
    sem_post(&rmutex);
    
    printf("\nreader %d is reading shared data:%d",id,shared_data);
    sleep(2);

    sem_wait(&rmutex);  // exit section
    readcount--;

    

    if(readcount == 0){

        sem_post(&resource);
    }
    printf("\nreader %d has finished reading",id);

    sem_post(&rmutex);

    return NULL;

}

int main(){

    pthread_t writer_threads[num_w];
    pthread_t reader_threads[num_r];

    sem_init(&wmutex, 0 , 1);
    sem_init(&rmutex, 0 , 1);
    sem_init(&readtry, 0 , 1);
    sem_init(&resource, 0 , 1);

    int w_id[num_w];
    int r_id[num_r];

    for(int i = 0;i < num_w;i++){
        w_id[i] = i + 1;
        pthread_create(&writer_threads[i],NULL,writer,&w_id[i]);
    }

    for(int i = 0;i < num_r;i++){
        r_id [i] = i +1;
        pthread_create(&reader_threads[i],NULL,reader,&r_id[i]);
    }
    for(int i = 0;i < num_w;i++){

        pthread_join(writer_threads[i],NULL);
    }
    for(int i = 0;i < num_r;i++){

        pthread_join(reader_threads[i],NULL);
    }

    sem_destroy(&wmutex);
    sem_destroy(&rmutex);
    sem_destroy(&resource);
    sem_destroy(&readtry);
    return 0;
}