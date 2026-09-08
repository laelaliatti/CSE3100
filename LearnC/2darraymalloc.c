#include<stdio.h>
#include<stdlib.h>

int main(){

    int **rows = malloc(3*sizeof(int*));  //rows the double pointer will store 3 pointers that are size int* because they are size int. 
      // all the rows are stored inside of a double pointer.
     /* rows[0] = malloc(5*sizeof(int));
      rows[1] = malloc(5*sizeof(int));
      rows[2] = malloc(5*sizeof(int));
    */
//another way to do this 
        for(int i=0;i<3;i++){
            rows[i] = malloc(5*sizeof(int));

        }
        // this is all technically a 2d array
    for(int i=0;i<3;i++){
        free(rows[i]);
    free(rows);
    return 0;
}