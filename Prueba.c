#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
int pid;
void manejador(int sig){
  printf("REcibida señal %d\n",sig );
}

int main(int argc, char const *argv[]) {
  char const *mandato[9];
  for(int i = 0; i<sizeof(argv); i++){
    mandato[i] = argv[i];
  }
  execvp(mandato[1], mandato+1);


  //Comentario de prueba
  return 0;
}
