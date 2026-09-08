#include <stdio.h>
#include<stdlib.h>
//this is a singly linked list with a value and a next pointer node, if the node points to null then it is the last node

typedef struct node{
        int value;
        struct node* next; //self referential pointer

    }Node; //we can use Node as the data type here

//write a function that takes an input and returns a node

Node  *createNode(int v){
    Node*n = malloc(sizeof(Node));
    n ->value = v;
    n ->next = NULL;
    return n;
}

Node *prepend(Node *head, int v){  //Node *head just just input a node type
    Node *new = createNode(v);
    new->next= head; // puts it in front of head
    head = new; //sets it to be the new head.
    return head;
}

Node *find_last(Node *head){ //whatever node has it's next value as NULL is the last node
    if(head != NULL){
        while(head->next !=NULL){ 
            head = head->next;  // this while loop lets head travel throughout the linked list. 
        }
    }
    return head;
}
Node *append(Node*head, int v){
    if(head ==NULL){
        return createNode(v);
    }
    Node *last = find_last(head);
    last ->next = createNode(v);
    return head;
}

Node *print_list(Node *head){
    if(head == NULL){
        printf("Empty List\n");
    }
    while(head !=NULL){
        printf("%d->",head->value); //we print the value at the node
        head=head->next; //we move on to the next node till while satisfy.
    }
printf("NULL\n");
}

void free_list(Node *head){
    Node*temp = head;
    while(temp!=NULL){
        head = head ->next;
        free(temp);
        temp = head;
    }
}
int main(){

    //10,20,30,40
    Node *list = NULL;  // an empty list
    
    list = prepend(list,10);   // 10 -> NULL
    list = prepend(list,20);  // 20 -> 10 -> NULL
     //the number on the inside is the value, it doesn't create 10 nodes btw. 
    print_list(list);
     //what if we wanted to prepend to the start of the list.

    free_list(list);

    return 0;
}