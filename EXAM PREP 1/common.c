// Do not modify starter code
/* identify all the characters that are common across a collection of lowercase strings. 

Rely on the idea of progressively narrowing down a set of candidate characters as it examines each string in the array.
assume that every lowercase letter, from a to z, could potentially be common to all strings.
    This assumption is gradually refined as we process the input.

For each string, create a temporary record to note which characters actually appear in that string. 
As the string is scanned character by character, the corresponding entry for each letter is marked. 
    For instance, if the string is apple, then the entries for a, p, l, and e are set to true, while all others remain false.

Once the string has been examined, the program compares this temporary record with the running global record of common characters.
Any letter that is absent from the current string is immediately disqualified from being considered common 
and is removed from the global record. 
In effect, the global record is continually updated as the intersection of character sets across all strings.
    After all strings have been processed, the global record contains only those characters that were present in every string. 
    These characters are then reported as the output. 
    If no such characters remain, the program explicitly indicates this by printing None


Test: 
$./common applet ballet cattle
Common characters: a e l t
$./common app bow cut
Common characters: None

*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 100


void commonChars(char arr[][MAX_LEN], int n) {

    int common[26];                    //make commmon array, 26 characters 1 for each letter
    for (int i = 0; i < 26; i++) {
        common[i] = true;             //set all of them to true
    }

    int temp_record[26];             //make a record array
    for (int i = 0; i < 26; i++) {
        temp_record[i] = false;     //set all to false, as if we were given an empty string
    }

    for (int word = 0; word < n; word++){ //run through all the words that we were given in our word array from parameters
        int letter = 0;                   //for each word, start at the first letter
        char current = arr[word][letter]; //this gets the value of the first index of the word were at

        while(current != '\0'){          //while were not at the end of the word
            int value = current - 'a';   //the value of the character in ascii 
            temp_record[value] = true;   //use the ascii value as an index
            letter++;                    //move to the next letter
            current = arr[word][letter]; //update the current letter so the while loop will terminate eventually
          }

        for (int index = 0; index < 26; index++){ //run through the whole record
            if(!temp_record[index]){              // if the index is false, the letter isnt in the string
                common[index] = false;            // make the letter false in common
            }
          }

        for (int i = 0; i < 26; i++) {            //reset the record for the next word
            temp_record[i] = false;
          }
    }

  printf("Common characters: ");

  // fill code here
  bool found = false; 
  char hold[26];                 //hold the characters themselves for printing later
  for (int i = 0; i < 26; i++) { //run through the whole array
    hold[i] = '*';               //place holder that we can compare with
  }

  for (int i = 0; i < 26; i++){    //run through the full common array
    if(common[i] == true){            // if we find a index thats true
      found = true;                // make found true, we have a match!
      hold[i] = (char)(i + 'a');   //update the char in hold to be the char that matches. Pay attention to the fact that were adding the index
                                   // this is because the common arr only holds 1 and 0 so we cant use that to add with, we need the index which corresponds to 0-25
    }
  }

  if (!found) {
    printf("None");
  }else{
    for (int i = 0; i < 26; i++){
    if(hold[i] != '*'){           //if theres a character thats not a filler then print it!
      printf("%c ", hold[i]);
    }
  }
  printf("\n");
}
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

