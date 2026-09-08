#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>
#include <sys/wait.h>


//a parent process
// Child 1 and Child 2 processes
//they will communicate via pipes
//takes an integer from command line arguments and passes it through the processes as follows. 

//we will need 6 pipes in total so we need to close 30+ fds!!!
//
//naming convention, the one that writes is in front.
int main(int argc, char *argv[])
{

    int input = atoi(argv[1]);
    //printf("%d\n",input);
    int pc1[2]; // use for parent(write) child(read)  
    int cp1[2]; //use for child(write) parent(read)
    int pc2[2];
    int cp2[2];
    int c1c2[2];
    int c2c1[2];
    pipe(pc1);
    pipe(cp1);
    pipe(pc2);
    pipe(cp2);
    pipe(c1c2);
    pipe(c2c1);
    //just set up stuff
    int c1 = fork();
    int c2 = fork();

    if(c1 == 0)
    { //child 1
        close(pc1[1]); //pc1 won't write in child
        int firstinput;
        read(pc1[0],&firstinput, sizeof(int));
        int firstmult = firstinput * 2;
        close(c1c2[0]);
        int val;
        write(c1c2[1], &val, sizeof(int)); //writes to c2
        close(c1c2[1]);
        close(c2c1[1]);
        int gotfr2;
        read(c2c1[0], &gotfr2, sizeof(int));
        int bytwo = gotfr2*2;
        close(c2c1[0]);
        close(cp1[0]);
        int end;
        write(cp1[1],&end, sizeof(int));
        close(pc1[0]);
        close(cp1[1]);
        close(pc2[1]);
        close(cp2[1]);
        close(pc2[0]);
        close(cp2[0]);
        

        exit(EXIT_SUCCESS);
    }
    if(c2 == 0)
    { //child 2
        close(c1c2[1]);
        int val;
        read(c1c2[0],&val,sizeof(int));
        int secondmult = val *4;
        close(cp2[0]); //child 2 write to parent
        write(cp2[1],&secondmult, sizeof(int)); //writes to parent
        close(pc2[1]);
        int gotfrpar;
        read(pc2[0],&gotfrpar, sizeof(int));
        close(pc2[0]);
        int byfour = gotfrpar *4;
        close(c2c1[0]);
        write(c2c1[1], &byfour, sizeof(int));
        printf("%d\n", val);
        exit(EXIT_SUCCESS);
    }
    //parent
    close(pc1[0]);
    write(pc1[1],&input,sizeof(int));
    close(cp2[1]);
    int gotfr2;
    read(cp2[0],&gotfr2, sizeof(int));
    int byeight = gotfr2*8;
    close(pc2[0]);
    write(pc2[1], &byeight, sizeof(int));
    close(pc2[1]);
    close(cp1[1]);
    int rez;
    read(cp1[0],&rez, sizeof(int));
   // printf("final results: %d\n", rez);

return 0;



}