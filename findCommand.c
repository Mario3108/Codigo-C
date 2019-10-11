#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc, char const *argv[]) {

  if (argc != 2) {
    printf("Error: intruce un comando .\n", );
  }else{
    char comando[] = argv[1];
  }

  char dir[] = getenv("PATH");


  return 0;
}
