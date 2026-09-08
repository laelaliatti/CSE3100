/*
Base case is where it’ll stop
And everything else is a recursive case
*/
#include<stdio.h>


int power(int base, int n){
    // we want to calculate base^n
    int result = 1; //because you can't start multiplication with 0 it'll all go to zero
    while(n>0){
        result = result * base;
        n--;
    }
return result;
}
int power_rec(int base, int n){
    if (n ==0){
        return 1;  //if exponent to the power of 0 you get 1, also it's a base case.
    }
    else{
        return base *power_rec(base, n-1); // the recursive case
    }
}
// lets say we're trying to get 2^3
// so 2*power(2,2)
//then 2*2*power(2,1)
// 2*2*2*power(2,0) 

int main(){
    printf("2^3 = %d\n", power(2,3));
    printf("2^3 = %d\n", power_rec(2,3)); // this prints the 2 to the power of 3 and you can see it calling it
}