#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>
#include <sys/wait.h>


//goal is to cat doc.txt | tr a-z A-Z


//here cat writes to the function tr and tr only reads from cat. 
int main(){

    int p[2];
    //pipe can return a value so we can set a safety need by putting it to an error. 
    //if (p ==-1){
        //perror("pipe failed\n");

   // }  this doens't work because I have to type cast it into an integer

   int ret = pipe(p); //for return
    if (ret ==-1){
        perror("pipe failed\n");
    }
    int pid1 = fork();
    if(pid1 == 0)
{ //BTW cat tells you what's in a file.
    close(p[0]);
    dup2(p[1],1); //closes stdout and points it to p[1] which is our write. 
    execlp("cat","cat", "doc.txt",NULL); //NULL to tell it it's over and this is the func we executing

    exit(1);
}

    int pid2 = fork();
    if(pid2 == 0){
        close(p[1]);
        dup2(p[0], 0); // instead of reading from stdin it reads from the pipe. 
        close(p[0]); //this is because we don't need it anymore
        execlp("tr","tr","a-z","A-Z", NULL);
        exit(0);
    }
    close(p[0]);
    close(p[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid1, NULL, 0);
    return 0;
}