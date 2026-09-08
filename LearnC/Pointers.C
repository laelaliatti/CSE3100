#include<stdio.h>
// this is me testing stuff and learning C
int main(){
//everytime you change code recompile it
    int a = 10;
    printf("a= %d\n", a);
    printf("address of a = %p\n", &a);  // Prints the Address
    

    // we should be able to store the address somewhere
    // pointers are special vars that store addresses
    int *pa = &a;       //the address of a is bieng stored in pointer pa here.
    printf("pa = %p\n", pa); // printing the address of a
    printf("*pa= %d\n", *pa); //prints the value that is stored in the address ---- this is called dereferencing.

    *pa = 12;  // this updates the value 
    printf("*pa = %d\n", *pa); //prints the ho
    printf("a = %d\n", a);   // by changing the pointer value we also changed a

/* Multi 
Line
COmments 
*/


    return 0;
}