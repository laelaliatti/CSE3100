//my own shot at this
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
//goes through 10 numbers and produces and consumes them. 
// make sure to watch the buffers 
int buffer;
int full = 0; // 0 = empty, 1 = full
pthread_mutex_t mutex;
pthread_cond_t cond_producer;
pthread_cond_t cond_consumer;

void*producer(void*arg){
    int item = buffer;
    for(int i=1; i<=10; i++){
        pthread_mutex_lock(&mutex);
        while(full == 1){
            pthread_cond_wait(&cond_producer, &mutex);
        }
        // this is post waiting
        item = i;//updates as we move through the loop
        buffer = item; //so consumer can take it
        full = 1; //set to one so we know producer is full.
        printf("Produced %d\n", item);
        pthread_cond_signal(&cond_consumer); //then alert consumer
        pthread_mutex_unlock(&mutex);
        
    }
    pthread_exit(NULL); //at the end of each thread function.
}
void*consumer(void*arg){
    int item;

    for(int i=0; i<10; i++){
    pthread_mutex_lock(&mutex);
    while(full == 0){//waits till there's an item in the buffer
        pthread_cond_wait(&cond_consumer, &mutex);
    }
    item = buffer;
    full = 0; //set full back to zero.
    printf("Consumed %d\n", item);
    pthread_cond_signal(&cond_producer); //signals back to the producer that buffer is empty again!
    pthread_mutex_unlock(&mutex);
    
    }
    pthread_exit(NULL); //at the end of each thread function.
}
int main()
{
    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_consumer, NULL);
    pthread_cond_init(&cond_producer, NULL);


    pthread_t prothread; //producer thread 
    pthread_t conthread; //consumer thread
    pthread_create(&prothread, NULL, &producer, NULL);
    pthread_create(&conthread, NULL, &consumer, NULL);
    pthread_join(prothread, NULL);
    pthread_join(conthread, NULL);


    // Clean up mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_consumer);
    pthread_cond_destroy(&cond_producer);
    return 0;
}