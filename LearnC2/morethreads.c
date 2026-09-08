//another example of threads
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> //thread library

void * routine(){ //thread function
    printf("Test from Threads \n");

    sleep(3); //waits 3 seconds
    printf("Ending threads\n"); //this is to test concurrency and we see that at the same time
    //test from threads is executes in both threads and then ending threads is executed 3 secs later at the same time. 
}


int main(int argc, char* argv[])
{
    pthread_t t1;// a var t1 : a place where API can store some information about the thread //
    //this is the thread itself, t1 is thread 1.
    pthread_t t2; //now I have a second thread
    if (pthread_create(&t1, NULL,&routine,NULL) !=0){//3rd is the function we are passing too //4th is args passed to 3rd func.
        //we can wrap the create under an if to error check
        return 1; //this means it failed
    }
    if (pthread_create(&t2, NULL,&routine,NULL) !=0)
    {
        return 1;
    }
    //pthread_create(&t2, NULL,&routine,NULL); //executes the same function
    //you can also do this but it's not as safe.
    if(pthread_join(t1, NULL)!=0){ //waits for the thread to finish it's execution //2nd para is what the thread executes, here it's NULL
        return 2; //can also be done with join and any number above 0 can work for failure.    
    }
    if(pthread_join(t2, NULL)!=0){
        return 4;
    }//waits till t2 is done
    return 0;
}