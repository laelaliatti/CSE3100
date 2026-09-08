#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
/*

A mutex is like a lock around a certain section of code
For example we could have a variable called lock and we can set it to 1 whenever we are doing something 
and set it to 0 when we are done doing something. 

*/
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
    pthread_t p1, p2, p3, p4;
    pthread_mutex_init(&mutex, NULL); //initualizes the mutex in the main function. 
    if (pthread_create(&p1, NULL, &routine, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&p2, NULL, &routine, NULL) != 0) {
        return 2;
    }
    if (pthread_create(&p3, NULL, &routine, NULL) != 0) {
        return 3;
    }
    if (pthread_create(&p4, NULL, &routine, NULL) != 0) {
        return 4;
    }
    if (pthread_join(p1, NULL) != 0) {
        return 5;
    }
    if (pthread_join(p2, NULL) != 0) {
        return 6;
    }
    if (pthread_join(p3, NULL) != 0) {
        return 7;
    }
    if (pthread_join(p4, NULL) != 0) {
        return 8;
    }
    pthread_mutex_destroy(&mutex); //we have to destroy mutex after finished.
    printf("Number of mails: %d\n", mails);
    return 0;
}