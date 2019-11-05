#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char const *argv[]) {
  for(int i = argc-1; i>=1; i--){
    for(int j = strlen(argv[i])-1; j>=0 ; j--){
      printf("%c", argv[i][j]);
    }
    printf(" ");
  }
  printf("\n");
  return 0;
}
