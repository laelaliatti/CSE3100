#include<stdio.h>
//how do we pass an array through a function
void print_array(int arr[], int n){
    for(int i = 0; i<n; i++){
        printf("arr[%d] = %d\n", i, arr[i]);
    }
}

int main(){
    int n;
    printf("Enter the size of array:");
    scanf("%d", &n);  //needs & for n because it needs the address to store the input properly
    int arr[n];
     for(int i = 0; i<n; i++){
     printf("Enter arr[%d]", i);
     scanf("%d", &arr[i]);
    }

    //how to call it
    print_array(arr,n);

}
//You cannot return a whole array at once in C, you return 1 element but not the whole thing