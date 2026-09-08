//get a value from a thread!
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h> //to generate random num.

void * roll_dice(){ // will roll dice and return it
    int value = (rand() % 6)+1; //will roll 0-5 and then we add 1 which will make it 1-6.
    // printf("%d\n", value); just to make sure it works. 
    int *result = malloc(sizeof(int)); //we have to allocate space for a pointer
    *result = value; //this is so we don't get a seg fault.
    // return(void*) &value; 
    return (void*)result;//join reads from this and writes it to res where we can use it.
    //res = result 
    //DON'T FORGET TO RETURN VOID.

}

int main(){ //main function will print out what is returned
    int*res;
    srand(time(NULL)); //ignore this, it just makes the numbers more random ig
    pthread_t th; //create thread
    if(pthread_create(&th, NULL, &roll_dice, NULL) !=0){
        return 1; //failure
    }
    if(pthread_join(th, (void **)&res)!=0){ //you don't have to cast, but it avoids warnings
        //the second param here is the var it writes too
        return 2;
    }
    printf("Result: %d\n", *res); //pointer to res.
    free(res); //of course we have to free res.
    //if you need to debug print our res and results addresses and see if they match. %p for pointers
    return 0;
}