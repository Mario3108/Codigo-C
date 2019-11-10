#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>


int hijos[4] = {0, 0, 0, 0};
int i;
int j = 3;
void manejador(int sig);
int main(int argc, char const *argv[]) {
  int pid;
  signal(SIGUSR2, manejador);



    for( i = 0; i< 4; i++){
      pid = fork();
      if(pid == 0){
        pause();
      }else{
        hijos[i] = pid;
      }
    }
    printf("Todos los hijos creado\n");
    printf("Doy la salida\n");
    kill(hijos[3], SIGUSR2);
    for(i = 0; i<4; i++){
      wait(NULL);
    }
    printf("Todos terminaron.\n");
  return 0;
}

void manejador(int sig){
  printf("Soy el hijo %d con pid %d, corriendo...\n", i,getpid());
  sleep(1);
  if(i!=0){
    printf("Terminé. Paso el testigo al hijo %d con pid %d\n", i-1, hijos[i-1]);
    kill(hijos[i-1], SIGUSR2);

  }else{
    printf("Terminé!\n");

  }
  exit(0);
}
