#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine() {
    for (int i = 0; i < 10000000; i++) {
       
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex); //because there's a mutex around mails++
        //only one thread will be running that line of code at a time. 
        // read mails
        // increment
        // write mails
    }
}

int main(int argc, char* argv[]) {
    pthread_t th[4]; //make an array of threads
    pthread_mutex_init(&mutex, NULL); //initualizes the mutex in the main function. 
    for(int i = 0; i<4; i++){ //DONT put join and create in same loop, they'll execute sequencially instead of concurantly.
        if(pthread_create(&th[i],NULL,&routine,NULL)!=0){ //also creates the threads in the check.
            perror("Failed to create thread\n");
            return 1; //if it fails
        }
        printf("Thread %d has started\n", i);
    }
    for(int i = 0; i<4; i++){
        //we can also simplify join in the same way.
        if(pthread_join(th[i],NULL)!=0){ //also joins/waits for the threads in the check.
            return 2; //if it fails
        }
        printf("Thread %d has finished execution\n", i);
    }
    pthread_mutex_destroy(&mutex); //we have to destroy mutex after finished.
    printf("Number of mails: %d\n", mails);
    return 0;
}