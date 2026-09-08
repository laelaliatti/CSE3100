//to get bidirectional communication you need 2 pipes. 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>
#include <sys/wait.h>


//gonna attempt a multidirectional pipe, I'll have 1 child and the parent process
//the child is going to receive (read) a number from parent and it's going to multiply by 3 in the child. 
//the child will write the result to the parent, and the parent is going to read it and print it out
int main(int argc, char *argv[])
{
    
    int pc[2];  //parent to child
    int cp[2]; //child to parent 
    pipe(pc);
    pipe(cp);
    pid_t pid = fork(); //creates the child process

    if(pid == 0)
    {
        close(pc[1]); //the child will never write with pc
        int val;
        read(pc[0], &val , sizeof(int));
        printf("Number read: %d\n",val);
        int rez = val * 3;
        close(pc[0]);
        close(cp[0]);
        write(cp[1],&rez,sizeof(int));
        close(cp[1]);
        exit(EXIT_SUCCESS);
    }
    close(pc[0]); //we will never read with pc in parent
    close(cp[1]); //we will never write with cp in parent
    int val = 5;
    write(pc[1],&val, sizeof(int));
    close(pc[1]);
    int rez;
    read(cp[0],&rez, sizeof(int)); //then it'll read back the result.
    close(cp[0]);

    printf("Result: %d\n",rez);


    return 0;


}