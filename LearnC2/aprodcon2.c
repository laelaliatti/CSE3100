#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int head  = 0;  // consumer reads from here
int tail  = 0;  // producer writes here
int count = 0;  // number of items currently in buffer

pthread_mutex_t mutex;
pthread_cond_t cond_producer;
pthread_cond_t cond_consumer;

void *producer(void *arg) {
    for (int i = 1; i <= NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) {         // buffer full — wait
            pthread_cond_wait(&cond_producer, &mutex);
        }

        buffer[tail] = i;
        tail = (tail + 1) % BUFFER_SIZE;      // wrap around
        count++;
        printf("Produced %d  (count=%d)\n", i, count);

        pthread_cond_signal(&cond_consumer);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {                   // buffer empty — wait
            pthread_cond_wait(&cond_consumer, &mutex);
        }

        int item = buffer[head];
        head = (head + 1) % BUFFER_SIZE;      // wrap around
        count--;
        printf("Consumed %d  (count=%d)\n", item, count);

        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_producer, NULL);
    pthread_cond_init(&cond_consumer, NULL);

    pthread_t prothread, conthread;
    pthread_create(&prothread, NULL, &producer, NULL);
    pthread_create(&conthread, NULL, &consumer, NULL);

    pthread_join(prothread, NULL);
    pthread_join(conthread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);
    return 0;
}