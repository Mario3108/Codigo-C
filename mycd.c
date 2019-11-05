#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


int main(int argc, char const *argv[]) {
  char *dir;
  char buffer[1024];
  if(argc > 2){
    fprintf(stderr, "Error:%s y un directorio\n", argv[0]);
    return 1;
  }
  if(argc == 1){
    dir = getenv("HOME");
    if(dir == NULL){
      fprintf(stderr, "Error, no existe variable $HOME\n");
    }
  }
  if(argc == 2){
    dir = argv[1];
  }

  if(chdir(dir) != 0){
    fprintf(stderr, "mensaje de error: %s\n", strerror(errno));
  }
  printf("%s\n",getcwd(buffer, -1));

}
