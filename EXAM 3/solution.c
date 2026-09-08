#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 2

pthread_mutex_t mutex;
pthread_cond_t profcond;
pthread_cond_t studcond;
int buffer[BUFFER_SIZE];
int seattaken = 0; // 0 = empty, 1 = full


void * professorfunction(void* arg)
{
    int p = *(int*)arg;
    int student;
    sleep(3);
    for(int i=0; i<p; i++){
    pthread_mutex_lock(&mutex);
    while(seattaken == 0){//waits till there's an item in the buffer
        pthread_cond_wait(&profcond, &mutex);
    }
    seattaken --;
    p--;
    pthread_cond_signal(&studcond);
    pthread_mutex_unlock(&mutex);
}
    printf("Prof is done talking to %d students\n", p);
    pthread_exit(NULL);

}

void * studentfunction(void* arg)
{
    sleep(rand()%3+1); //simulate students arriving at different times.
    pthread_mutex_lock(&mutex); 
    while(seattaken == BUFFER_SIZE){//waits till buffer empty //buffer here is seats
        pthread_cond_wait(&studcond, &mutex);
    }
    int p = *(int*)arg;
    if(p == 0){
        pthread_exit(NULL);
    }
    
    seattaken ++;
    pthread_cond_signal(&profcond);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) 
{
    int n = atoi(argv[1]); //number of students
    unsigned int seed = atoi(argv[2]);
    int p = atoi(argv[3]); //max number of students the professor will talk too!
    srand(seed);
    

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&profcond, NULL);
    pthread_cond_init(&studcond, NULL);

    printf("%d\n", n);
    pthread_t professor;
    pthread_t students[n];
    pthread_create(&professor, NULL, &professorfunction ,p);

    for(int i = 0; i<n; i++){
        if(pthread_create(&students[i],NULL,&studentfunction,p)!=0)
        {
            perror("Failed to create thread\n");
            return 1; //if it fails
        }

    }
    //join the threads
    pthread_join(professor, NULL);
    for(int i = 0; i<n; i++){
        if(pthread_join(students[i],NULL)!=0)
        {
            perror("Failed to join thread\n");
        }
    }


    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&profcond);
    pthread_cond_destroy(&studcond);

    return 0;
}
