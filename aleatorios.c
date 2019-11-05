#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>

void sig_hnd(int sig){
  (void) sig;
  printf("(Fin de archivo)");
}
int pid;

int main(int argc, char const *argv[]) {
  int status, pipe_p[2], pipe_h[2];
  char buf[1024];
  int buf2[10], buf3[10];

  FILE *p_p, *p_h;
  int n;
  signal(STDIN, sig_hnd);
  if (argc > 1) {
    fprintf(stderr, "Error. No se introducen parametros\n", strerror(errno));
    exit(1);
  }

  pipe(pipe_p);
  pipe(pipe_h);

  pid = fork();

  if(pid < 0){
    fprintf(stderr, "Ha habido un fallo en el proceso\n", strerror(errno));
  }else if (pid == 0){
    close(pipe_h[0]);
    close(pipe_p[1]);
    p_h = fdopen(pipe_h[1], "w");
    p_p = fdopen(pipe_p[0], "r");
    n = 5;
    while(fgets(buf, 1024, p_p) != NULL){
      //sprintf (buf, "%i", n);
      fputs(buf, p_h);
      fflush(p_h);
    }
    kill(pid, STDIN);
    wait(status);
    printf("El hijo terminó\n");

  }else{
    close(pipe_p[0]);
    close(pipe_h[1]);
    p_p = fdopen(pipe_p[1], "w");
    p_h = fdopen(pipe_h[0], "r");

    while(fgets(buf, 1024, stdin) != NULL){
      fputs(buf, p_p);
      fflush(p_p);
      fgets(buf, 1024, p_h);
      fputs(buf, stdout);
    }



  }



  return 0;
}
