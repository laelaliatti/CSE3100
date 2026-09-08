//trying to roll like 8 dice at once on my own with no help.

//get a value from a thread!
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h> //to generate random num.


pthread_mutex_t mutex; //make a mutex with name mutex.
void * roll_dice(){ // will roll dice and return it

    pthread_mutex_lock(&mutex);
    int value = (rand() % 6)+1; //will roll 0-5 and then we add 1 which will make it 1-6.
    // printf("%d\n", value); just to make sure it works. 
    int *result = malloc(sizeof(int)); //we have to allocate space for a pointer
    *result = value; //this is so we don't get a seg fault.
    // return(void*) &value; 
    pthread_mutex_unlock(&mutex);
    return (void*)result;//join reads from this and writes it to res where we can use it.
    //res = result 
    //DON'T FORGET TO RETURN VOID.

}

int main(){ //main function will print out what is returned
    int*res;
    pthread_mutex_init(&mutex, NULL);
    srand(time(NULL)); //ignore this, it just makes the numbers more random ig
    pthread_t th[8]; //when looping threads need to be arrays. HAVE to give size right away.
    for(int i=0; i<8; i++){
    if(pthread_create(&th[i], NULL, &roll_dice, NULL) !=0){
        //we're iterating thru eat thread
        return 1; //failure
    }
}
    for(int i=0; i<8; i++){
    if(pthread_join(th[i], (void **)&res)!=0){ //you don't have to cast, but it avoids warnings
        //the second param here is the var it writes too
        return 2;
    }
    printf("Try %d Result: %d\n",i, *res); //pointer to res.

    free(res); //of course we have to free res.
}
    pthread_mutex_destroy(&mutex);
    //if you need to debug print our res and results addresses and see if they match. %p for pointers
    return 0;
}