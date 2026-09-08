//pass values to threads.
//pass an argument.
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
int primes[10] = {2,3,5,7,11,13,17,19,23,29};
void* routine(void* arg){// we're going to pass void*arg into routine
    int index = *(int*)arg; //have to dereference and type cast
    int sum = 0;
    for(int j=0; j<5; j++){
        sum += primes[index+j]; //we move along and we add them 
        //index is the a from main and it can come through as 0 or 5 and then it appends. 
    }
    printf("Local sum: %d\n", sum);
    *(int*)arg=sum;
    return arg;

}

int main(int argc, char* argv[]){
    pthread_t th[2];
    int i; //this mitigates conflict with the loops.
    for(i=0; i<2; i++){
        int * a = malloc(sizeof(int));// to mitigate conflict so we can get unique answers.
        *a = i*5; //at index 0 it's 0*5= index 0 and when it's 1 it's 1*5 = index 5 which is the 6th element onwards. 
        //we want first index to give us first half of list and second index to give second half
        if(pthread_create(&th[i], NULL, &routine, a)){ //the 4th para if we give it something it's transfered to void * arg
            //and then routine can use that address
            
            return 1;
        }
    }
    int globalsum = 0;
    for(i=0; i<2; i++){
        int *res;
        if(pthread_join(th[i], (void**)&res)){ //2nd para takes threads returning value.
            return 2;
        }
        globalsum+=*res;
        free(res);
    }
    printf("Global Sum = %d\n", globalsum);
    return 0;
}