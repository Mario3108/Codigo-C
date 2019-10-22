#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int status, pipe_des1[2], pipe_des2[2];
  pid_t pid;
  FILE *p_p, *p_h;
  char buf[1024];
  if (argc > 1) {
    fprintf(stderr, "No son necesarios argumentos para ejecutar este comando\n", );
    return 1;
  }
  pipe(pipe_des);
  pid = fork();
  if(pid < 0){
    fprintf(stderr, " Ha habido un error en el fork \n %s\n", strerror(errno));
    exit(1);
  }else if (pid == 0){
    close(pipe_des1[1]);
    close(pipe_des2[0]);
    p_p = fdopen(pipe_des1[0], "r");
    p_h = fdopen(pipe_des2[1], "w");

    while( fgets(buf, 1024, p_p) != NILL){

    }

  }else{
    close(pipe_des1[0]);
    close(pipe_des2[1]);
    p_p = fdopen(pipe_des1[1], "w");
    p_h = fdopen(pipe_des2[0], "r");
    while(fgets(buf, 1024, stdin) != NULL){
      fputs(buf, p_p);
      fflush(p_p);
      fgets(buf, 1024, p_h);
      fputs(buf, stdout);
    }


  }

  return 0;
}
