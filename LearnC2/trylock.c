//to trylock or to lock hmmm. (˶◜ᵕ◝˶)
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutex;

void* routine(void*arg){
    //pthread_mutex_lock(&mutex); //only one can lock at a time.
    if(pthread_mutex_trylock(&mutex) == 0){ //always put trylock under a if.
        //trylock tries to lock.
    printf("Got lock\n");
    sleep(1);//simulating something time consuming
    pthread_mutex_unlock(&mutex);
    } else{
        EBUSY; //needs #include <errno.h>
        perror("Didn't get lock\n");
        /*
        The Winner: One thread grabs the lock, prints "Got lock," and goes to sleep for a second.
        The Losers: The other 3 threads immediately hit the else block because trylock doesn't wait. 
        They print their error message and exit the routine.
        */
    }
}

int main(int argc, char* agrv[]){
    pthread_mutex_init(&mutex, NULL);
    pthread_t th[4]; // 4 THREADS (｡o_o｡)""
    for(int i = 0; i<4; i++){ 
        if(pthread_create(&th[i],NULL,&routine,NULL)!=0){
            perror("Failed to create thread\n");
            return 1; //if it fails
        }
    }
    for(int i = 0; i<4; i++){
        if(pthread_join(th[i],NULL)!=0){ 
            return 2; //if it fails
        }
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}



