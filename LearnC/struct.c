#include<stdio.h>
#include<stdlib.h>

//Structures are like classes in a way.
//allows us to make new data types
//STRUCTURES ARE DEFINED OUTSIDE MAIN FUNCTION
struct exam1{
    int id;
    int points;
};

typedef struct exam1 Exam1;
//now we can say Exam1 student1, instead of struct exam1 student1

int main(){

    struct exam1 student1; // the type of student 1 is struct exam1 so struct makes new types ie int, float, char
    student1.id = 1;
    student1.points = 87;

    printf("student1 id = %d\n", student1.id);
    printf("student1 points = %d\n", student1.points);
    struct exam1 students[10]; //we've made an array with our data type
    students[0].id = 123;    //pretty much at every index you can set the id and the points
    students[0].points = 56;

    printf("students[0] id = %d\n", students[0].id);   //accessing the first students id.
    printf("students[0] points = %d\n", students[0].points);


    //when normal variable you need to student1.id
    //when it's a pointer you need arrow operator
    Exam1* student2 = malloc(sizeof(Exam1)); //dynamically created 
    student2 ->id = 2;
    student2 ->points = 90;
    printf("student2 id = %d\n", student2 ->id);
    printf("student2 points = %d\n", student2->points);
    free(student2); //and ofc free.

    return 0;
}