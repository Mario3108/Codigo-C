#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
int pid;
int pipe_p[2];
void sig_hnd(int sig){
  int num;
  if(sig == SIGUSR1){
    num = 1+(int)(10.0*rand()/(RAND_MAX+1.0));
    write(pipe_p[1], &num, sizeof(int));

  }else if(sig == SIGUSR2){

      printf("(Fin de archivo)\n");
      exit(0);
  }

}


int main(int argc, char const *argv[]) {
  char buf[1024];
  int num;

  signal(SIGUSR1, sig_hnd);
  signal(SIGUSR2, sig_hnd);
  if (argc > 1) {
    fprintf(stderr, "Error. No se introducen parametros\n", strerror(errno));
    exit(1);
  }
  
  pipe(pipe_p);
  srand(time(NULL));
  pid = fork();


  if(pid < 0){
    fprintf(stderr, "Ha habido un fallo en el proceso\n", strerror(errno));
  }else if (pid == 0){

    close(pipe_p[0]);

    while(1);

  }else{
    close(pipe_p[1]);
    while(fgets(buf, 1024, stdin) != NULL){
      kill(pid, SIGUSR1);
      read(pipe_p[0], &num, sizeof(int));
      printf("%d\n",num );

    }
    kill(pid, SIGUSR2);
    wait(NULL);


  }



  return 0;
}
