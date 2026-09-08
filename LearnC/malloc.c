#include<stdio.h> //allows us to print
#include<stdlib.h> // allows us to work on malloc


void print_array(int *arr, int n){
    for(int i=0;i<n;i++){
        printf("%d\n", arr[i]);
    }
}
int main(){
   /* //size_t in malloc is number of bytes
    int* p = malloc(100); //this takes 100 bytes
    char *c = malloc(200); // this takes 200 bytes
    //an integer is 4 bytes so p can store 100/4 = 25 integers
    //a char is 1 byte so c can store 200/1 = 200 chars
    //*p and *c are storing the addresses of where the memory is allocated
    //address points to the first byte

    int *a = malloc(25*sizeof(int)); // here we want to be able to store 25 integers so 25 times the size of how many bytes an integer is gives us.
    int *t = calloc(1,sizeof(int)); //allocates space and initializes at zero.

    //when you grab memory from malloc you need to always go and free that memory, but only free after you are done using, always free tho.

    free(p);
    free(c);
    free(a);
    free(t);
    // Valgrind tells you if the memory is leaked or not.
    //unless I had freed all them valgrind would've spoke of my memory leaks. 
    // void* malloc(size_t);  void* means that you can give it whatever type you want, it has no type it;s just raw memory
    */

    //1d array using Malloc
    int*arr = malloc(4*sizeof(int)); //arr is now storing the address of the first byte and since here it's integer it looks at the first 4 which gives index
    //reads the whole 4 bytes which is just first index
    //4 integers cuz we gave it enough space for 4 and you just apply it the same way.
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    // printf("%d\n",*arr);
    
    print_array(arr,4);
    free(arr);   //free it without the star
    //printf always mallocs and frees on it's own.

}
