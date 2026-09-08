// Do not modify starter code
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

void commonChars(char arr[][MAX_LEN], int n) { //function looks for common chars and returns void
  int common[26]; // The 26 letters in the alphabet
  for (int i = 0; i < 26; i++) {
    common[i] = true; //initializes all letters are true.
  }

  for (int i = 0; i < n; i++) {  //n is the number of strings there are
    int temp[26];
    for(int i = 0; i <26; i++){
      temp[i] = false;

    }
    // fill code here
    char a = 'a';
    char b = 'a';
    char c = 'a';
    char d = 'a';
    char e = 'a';
    char f = 'a';
    char g = 'a';
    char h = 'a';
    char ch_i = 'a';
    char j = 'j';
    char k = 'k';
    char l = 'l';
    char ch_m = 'm';
    char ch_n = 'n';
    char o = 'o';
    char p = 'p';
    char q = 'q';
    char r = 'r';
    char s = 's';
    char t = 't';
    char u = 'u';
    char v = 'v';
    char w = 'w';
    char x = 'x';
    char y = 'y';
    char z = 'z';
    int check = (arr[i] >= 'a' && arr[i] <= 'z'); //checks if this is fine
    for(int word=0; word<n;word++){
      int letter = 0;
      char cur = arr[word][letter];
      
      while(cur != '\0'){  //It's the array here because letter and word are just indexes they don't hold the value
        int value = cur -'a'; // calling it an int turns the letter into it's ASCII value and subtracting it by a makes a 0 the starting index
        temp[value] = true;
        letter++; // this moves us to the next letter
        cur = arr[word][letter]; //update the current letter so the while loop will terminate eventually so we reach \0
      }
      for(int index = 0; index< 26; index++){ //run through the whole record.
        if(!temp[index]){              // if the index is false, the letter isnt in the string
                common[index] = false;            // make the letter false in common at the same index as temp.
            }

      }
    }
    for (int i = 0; i < 26; i++) {            //reset the record for the next word
            temp[i] = false;
          }


  }

  printf("Common characters: ");

  // fill code here
  bool found = false;
  for(int i=0; i<26;i++){
    if(common[i]){
      printf("%c ", i + 'a');
        found = true;
    }
  }
  if (!found) {
    printf("None");
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s string1 string2 ...\n", argv[0]);
    return 1;
  }

  int n = argc - 1;
  char arr[n][MAX_LEN];

  for (int i = 0; i < n; i++) {
    strcpy(arr[i], argv[i + 1]);
  }

  commonChars(arr, n);

  return 0;
}
