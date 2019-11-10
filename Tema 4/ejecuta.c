#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  pid_t pid;
  int status;
  char * mandato;
  char argumentos[1024];

  if(argc < 2){
    fprintf(stderr, "Error: introducir mandato\n" );
  }else{
    mandato = argv[1];

  }

  pid = fork();
  if(pid < 0){
    fprintf(stderr, "Ha habido un error con la creacion del proceso hijo\n", strerror(errno));
    exit(1);
  }else if(pid == 0){
    execvp(mandato, argv + 1);
    printf("Error al ejecutar el comando: %s\n", strerror(errno));
  }else{
    wait(&status);
    if(WIFEXITED(status) != 0){
      if(WEXITSTATUS(status) != 0){
        fprintf(stderr, "El comando no se ejecuto correctamente: %s\n", strerror(errno));
      }

      exit(1);
    }
  }

  return 0;
}
