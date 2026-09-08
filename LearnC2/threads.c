//fork and exec:
//multiple processes can work on different things at the same 
//they are entirely seperate so if one of them (processes) crash 
//the others keep running just fine.
//threads:
//you get concurrency, but no isolation, so this happens all in the same process
//if one of your threads crashes, the whole thing crashes. 
//a thread can write into the memory of another thread
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

void* myturn(void* arg)  //a thread function has to return a void pointer and take one as an arg
{
    int *iptr = (int *)arg; //iprt = integer pointer
    for(int i=0; i<8; i++){
        sleep(1); //every one second 
        printf("my turn %d %d\n", i, *iptr); //prints out my turn //i prints out the line we're on.
        (*iptr)++; //incriment the value
    }
    return NULL;  //also return NULL
}

void yourturn()  //only one of them needs to be like that
{
    for(int i=0; i<3; i++){
        sleep(2); //every two seconds 
        printf("your turn %d\n", i); //prints out your turn
    }

}


int main()
{

   // myturn();       //if we call them after another the first function only executes and never goes to second func.
    // yourturn();
    pthread_t newthread; //we have just made a thread with the data type pthread_t
    int v = 5;
    // pthread_create(&newthread, NULL, myturn, NULL); //this is for if we're not passing anything
     //the third parameter takes a thread func
    // myturn();  we don't need it anymore
    pthread_create(&newthread, NULL, myturn, &v); //we're passing v
    yourturn();
    pthread_join(newthread,NULL); //it'll wait until a specific thread finishes running and then continue
    //it takes just the newthreads not the address, but check warnings
    //other wise the other function wouldn't finish because when main is done the program exits.
    printf("The thread finished %d\n", v); //prints out v after thread finishes
}