#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int i;
char const *mandato1[3];
FILE *p_h1, *p_h2;
char buf[1024];
char buf2[1024];
int hijos[2];
int fd[2];
int pipe_h2_h3[2], pipe_h1_h2[2];
int main(int argc, char const *argv[]) {

  int pid1, pid2, pid3;

  pipe(pipe_h2_h3);
  pipe(pipe_h1_h2);
  pid1 = fork();
  if(pid1 == 0){//Hijo 1
    close(pipe_h2_h3[0]);
    close(pipe_h2_h3[1]);
    close(pipe_h1_h2[0]);
    close(STDOUT_FILENO);
    dup(pipe_h1_h2[1]);
    execlp("ls", "ls", "-la", NULL);

    printf("Cosas\n");
    close(pipe_h1_h2[1]);
    exit(0);
  }else{//Padre
    pid2 = fork();
    if(pid2 == 0){//Hijo 2

      close(pipe_h1_h2[1]);
      close(STDIN_FILENO);
      dup(pipe_h1_h2[0]);
      close(pipe_h2_h3[0]);
      close(STDOUT_FILENO);
      dup(pipe_h2_h3[1]);
      printf("Buenas, aqui el hijo 2.\n");
      execlp("tr", "tr", "\"d\"", "\"D\"", NULL);
      exit(0);

    }else{//Padre
        pid3 = fork();
        if(pid3 == 0){
          close(pipe_h1_h2[0]);
          close(pipe_h1_h2[1]);
          close(pipe_h2_h3[1]);
          close(STDIN_FILENO);
          dup(pipe_h2_h3[0]);
          execlp("tr", "tr", "l", "X", NULL);
          close(pipe_h2_h3[0]);
        }else{
          wait(NULL);
        }

    }
  }



  return 0;
}
