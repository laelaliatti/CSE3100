#include<stdio.h>
// this is me testing stuff and learning C
int main(){
    //arrays store elements of the same datatype
    //we want to store 10,20,30,40,50
    int arr[5]; // we just made an int array of size 5
    arr[0] = 10; //this sets the first index which is 0 to 10
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;

    int y[5] = {10,20,30,40,50}; //another way to create arrays but we're telling it to be size 5
    int z[] = {10,20,30,40,50}; // we don't need to tell it the size

    // how to access something at an index
    printf("arr[1] = %d\n",arr[1]);
    printf("y[3] = %d\n", y[3]);

    // a string is a collection of chars we can show this with arrays
    char s[6] = {'H','e','l','l','O','\0'}; // the \0 or null operator tells us that the string is over, but there other ways to do this
    char t[5] = "Hello"; //C adds the \0 at the end automatically
    char a[] = "Hello"; // thank the stars you don't need to specify the size and also whatever you put \0 is added at the end
    //for the just write it out assignment you need to use double quotes
    //you can't assign arrays to each other
    int temp [5];
    for(int i =0; i<5; i++){
        temp[i] = arr[i]; //this loop through arr and adds it's elements to temp


    //what if we don't know what size the array is going to be?
    int n;
    printf("Enter the size of array");
    scanf("%d", &n); // they input this n which gives us the size
    int arr[n]; // we then create an array of size n
    for(int i=0; i<n;i++){  // iterates from 0 to n and increases
        printf("Enter arr[%d]", i); //it asks if for the input at each index that %d takes the index and shows it
        scanf("%d", &arr[i]); //and here you enter
    }

//strings are just a different type of array

    }
    
    //to print strings we use %s, to print decimals we use %d
    printf("%s\n", t);


    

    return 0;
}