#include <stdio.h>
//we're gonna make a power function and it'll use recursion!!!


int power(int base, int n){
    // we want to calculate base^n
    int result = 1; //because you can't start multiplication with 0 it'll all go to zero
    while(n>0){
        result = result * base;
        n--;
    }
return result;
}

int main(){
    printf("2^3 = %d\n", power(2,3));  // this prints the 2 to the power of 3 and you can see it calling it
}