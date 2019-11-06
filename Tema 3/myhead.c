#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char const *argv[]) {
  char buf[1024];
  int cuenta = 0;
  int lineas;
  if(argc == 1){
    lineas = 10;
  }else if(argc == 2){
    lineas = atoi(argv[1]);
  }else{
    fprintf(stderr, "error\n" );
    return 1;
  }


  while((cuenta < lineas)&&(fgets(buf, 1024, stdin)!=NULL)){
        printf("%s\n", buf);
        cuenta++;
  }
  /* code */
  return 0;
}
