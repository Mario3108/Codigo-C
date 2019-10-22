#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  pid_t pid;
  int status;

  if (argc < 2) {
    fprintf(stderr, "Uso: %s comando y opciones\n", argv[0]);
    return 1;
  }

  pid=fork();

  if(pid < 0){
      fprintf(stderr, "Fallo en el fork)().\n %s\n", strerror(errno));
      exit(1);
  }else if (pid == 0){
    execvp(argv[1], argv + 1);

    printf("Error al ejecutar el comando: %s\n", strerror(errno));
    exit(1);
  }else{
    wait(&status);

    if (WIFESTATUS(status) != 0) {
      if(WIFEXITED(status) != 0){
        printf("El comando  no se ejecuto correctamente\n" );
      }
    }
    exit(0);

  }

  return 0;
}
