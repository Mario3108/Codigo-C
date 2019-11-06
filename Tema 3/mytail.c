#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int lineas;
  char buf[1024];
  int total = 0;
  char todas[1024][1024];
  if(argc == 1){
    lineas = 10;
  }else if(argc == 2){
    lineas = atoi(argv[1]);
  }else{
    fprintf(stderr, "error\n");
  }
  int j = 0;
  while(fgets(buf, 1024, stdin)){
    strcpy(todas[j], buf);
    total++;
    j++;
  }
  printf("\n" );
  int inicio = j-lineas;
  int i = 0;
  if(inicio < 0){
    i = 0;
  }else{
    i = inicio;
  }
  for(i; i<j; i++){
    printf("%s", todas[i]);
  }

  return 0;
}
