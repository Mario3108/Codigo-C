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
int pipe_p_h1[2], pipe_h1_h2[2];
int main(int argc, char const *argv[]) {

  int pid1, pid2;

  pipe(pipe_p_h1);
  pipe(pipe_h1_h2);
  pipe(fd);

  pid1 = fork();
  if(pid1 == 0){//Hijo 1
    //close(pipe_h1_h2[0]);
    //p_h2 = fdopen(pipe_h1_h2[1], "w");

    close(fd[0]);
    close(STDOUT_FILENO);
    dup(fd[1]);
    //close(fd[1]);
    execlp("ls", "ls", "-la", NULL);
    //fputs(fd[1], p_h2);
    //fflush(p_h2);
    printf("Cosas\n");
    close(fd[1]);
    exit(0);
  }else{//Padre
    pid2 = fork();
    if(pid2 == 0){//Hijo 2
      //close(pipe_h1_h2[1]);
      //p_h2 = fdopen(pipe_h1_h2[0], "r");
      close(fd[1]);
      close(STDIN_FILENO);
      dup(fd[0]);
      //close(fd[0]);
      printf("Buenas, aqui el hijo 2.\n");
      execlp("tr", "tr", "\"d\"", "\"D\"", NULL);
      //printf("%s\n", buf);
      close(fd[0]);
      exit(0);

    }else{//Padre
        wait(NULL);
    }
  }



  return 0;
}
