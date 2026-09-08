#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 1024  // this defines a constant, but it doesnt have a data type

// read from a file a encrypted message and then decrypt and print the message
void read_secret_message(char key, int fd) {
  int message[MAX];
  int len = read(fd, message, MAX);   //file descriptor is fd
  for (int i = 0; i < len / sizeof(int); i++) {
    message[i] = message[i] ^ key;  // ^ is xor   if we xor back with the key we can decrypt it
    printf("%c", (char)(message[i]));
  }
  printf("\n");
}

int main() {
  int fd = open("message.txt", O_RDONLY);
  if (fd < 0) {
    printf("Cannot open the file\n");
    return -1; //return failure
  }
  read_secret_message(111, fd); //111 is the key here
  close(fd); //always close when you're done
}
