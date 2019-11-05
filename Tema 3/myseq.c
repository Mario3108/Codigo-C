#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


int main(int argc, char const *argv[]) {
  if(argc < 2){
    printf("Error\n" );
    exit(1);
  }

  int first;
  int last;
  int increment;
  if(argc == 2){
    last = atoi(argv[1]);
    increment = 1;
    first = 1;
  }else if(argc == 3){
    first = atoi(argv[1]);
    increment = 1;
    last = atoi(argv[2]);
  }else if(argc == 4){
    first = atoi(argv[1]);
    increment = atoi(argv[2]);
    last = atoi(argv[3]);
  }

  for(int i = first; i <= last; i= i+ increment){
    printf("%i\n", i);
  }
  return 0;
}
