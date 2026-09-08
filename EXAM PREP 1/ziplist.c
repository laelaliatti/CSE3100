//Do not modify starter code
//You may add helper functions if needed
#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
  int data;
  struct Node *next;
} Node;

// Create a new node
Node *createNode(int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

// Insert at end
void insertEnd(Node **head, int data) {
  Node *newNode = createNode(data);
  if (!*head) {
    *head = newNode;
    return;
  }
  Node *temp = *head;
  while (temp->next)
    temp = temp->next;
  temp->next = newNode;
}

// Print list
void printList(Node *head) {
  while (head) {
    printf("%d ", head->data);
    head = head->next;
  }
  printf("\n");
}

Node *find_prev(Node *head, int v){
  while (head != NULL && head -> next != NULL){ //while we have things in our list and we have another node
    if (head -> data == v){  //v and data are the same thing
      return head; 
    }
    if (head -> next -> data == v){ //if the current node value of next is equal to the one im trying to find 
      return head; // return it
    }
    head = head -> next; //otherwise move to the next one

  }
  return head; //return the node we're on if theres no previous
}

int amount(Node *head){
  int count = 0;
  while(head->next != NULL){
    count += 1;
    head = head->next;  // this is what moves it around

  }
  return count;
}


void zipList(Node **headRef) {

  // fill code here
  Node *head = *headRef; //head is the pointer
  int len = amount(*headRef);
  
for(int i = 0; i < len/2; i++){
  Node* current_next = head->next; //traversing the list
  Node* temp = head;  // this is accessing the value
  while(temp->next!= NULL){
    temp = temp->next;
  }
  Node *prev = find_prev(*headRef, temp->data);
  prev -> next = NULL;
  head -> next = temp;
  temp -> next = current_next;
  head = current_next;
  }
}

void free_list(Node *head) {
  Node *temp = head;
  while (temp != NULL) {
    head = head->next;
    free(temp);
    temp = head;
  }
}


int main(int argc, char *argv[]) {
  Node *head = NULL;

  if (argc < 2) {
    printf("Usage: %s <list of integers>\n", argv[0]);
    return 1;
  }

  for (int i = 1; i < argc; i++) {
    int val = atoi(argv[i]);
    insertEnd(&head, val);
  }

  printf("Original list:\n");
  printList(head);

  zipList(&head);

  printf("Zipped list:\n");
  printList(head);
 
	// fill code here
  free_list(head);

  return 0;
}
