#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_elements(char **elems, int count) {
  for (int i = 0; i < count; i++) {
  
    printf("%s\n", elems[i]);

  }
}

int stringCompare(const void *s1, const void *s2) {
  return strcmp(*(char **)s1, *(char **)s2);
}


int main(int argc, char *argv[]) {
  if (argc < 2) {
    perror("Usage : ./place <strings>");
    exit(1);
  }
  for(int i=0; i<argc; i++){
    int count[] = {};
    int a = argv[i];
    int value = a;
    if(value >= 'a'){
      count[i] ++; // if value is greater than or eqaul to the ascii value of a then it's a lowercase.
    }
  }
 

  //char **words = (char **)malloc(sizeof(char *) * argc);
  //qsort(words, argc, sizeof(char *), stringCompare);

  print_elements(&argv[1], argc - 1);
  return 0;
}
