//conditional vars.
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
//◝(ᵔᗜᵔ)◜
//Conditional Variables -- Variable on conditon.  // kinda just like a wait.
//one care is getting fuel another car is waiting to get fuel. 

int fuel = 0; //global variable for both threads so we'll need a mutex.
pthread_mutex_t mutexFuel;
pthread_cond_t condFuel; // making the conditional var.
void*fuel_filling(void*arg){
    for(int i=0; i<5; i++){    
        pthread_mutex_lock(&mutexFuel); //cuz we're accessing a shared var.
        fuel +=15;
        printf("Filled Fuel... %d\n",fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_signal(&condFuel); //signals and then activates the car thread 
        //says to all the threads that are waiting on the condition to keep running
        //signal starts the wait. in car function.
        sleep(1);
    }
}
void*car(void*arg){
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40){ //our condition
        printf("No fuel. Waiting ... \n");
        // sleep(1);
        pthread_cond_wait(&condFuel, &mutexFuel); //will wait for the signal
        //also unlocks the mutex and waits
        //Instead of sleeping we call this
        //it's going to wait for a signal from another thread. 
        //after it waits it locks again. 
    }
    fuel -=40;
    printf("Now left: %d\n",fuel);
    pthread_mutex_unlock(&mutexFuel);

}

int main(){
    pthread_mutex_init(&mutexFuel,NULL);
    pthread_cond_init(&condFuel, NULL);
    pthread_t th[2]; //instead of creating 2 different threads he does this, interesting.
    for(int i=0; i<2; i++){
        if (i==1){
            if(pthread_create(&th[i], NULL, &fuel_filling, NULL)!=0){
                perror("Failed to create thread");
            }
        } else {
        if (pthread_create(&th[i], NULL, &car, NULL)!= 0){
                perror("Failed to create thread");
            }
        }
    }
    for(int i=0; i<2; i++){
        if(pthread_join(th[i], NULL)!=0){
            perror("Failed to join thread");
        }
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_condattr_destroy(&condFuel);
    return 0;    
}