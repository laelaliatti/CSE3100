//pass values to threads.
//pass an argument.
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
//problem: Create 10 threads, each taking a unique prime from primes array and print it on the screen. 
int primes[10] = {2,3,5,7,11,13,17,19,23,29};
void* routine(void* arg){// we're going to pass void*arg into routine
    int index = *(int*)arg; //have to dereference and type cast
    printf("%d\n ", primes[index]);
    free(arg);// frees int *a below. 

}

int main(int argc, char* argv[]){
    pthread_t th[10];
    int i; //this mitigates conflict with the loops.
    for(i=0; i<10; i++){
        int * a = malloc(sizeof(int));// to mitigate conflict so we can get unique answers.
        *a = i;
        if(pthread_create(&th[i], NULL, &routine, a)){ //the 4th para if we give it something it's transfered to void * arg
            //and then routine can use that address
            //so as we move through the loop it moves thru the array. 
            return 1;
        }
    }
    for(i=0; i<10; i++){
        if(pthread_join(th[i], NULL)){
            return 2;
        }
    }
}