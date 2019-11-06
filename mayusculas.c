#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char const *argv[]) {
  int status, pipe_des1[2], pipe_des2[2];
  pid_t pid;
  FILE *p_p, *p_h;
  char buf[1024];
  char buf2[1024];
  if (argc > 1) {
    fprintf(stderr, "No son necesarios argumentos para ejecutar este comando\n", strerror(errno));
    return 1;
  }
  pipe(pipe_des1);
  pipe(pipe_des2);
  pid = fork();
  if(pid < 0){
    fprintf(stderr, "Algo ha ido mal con el fork\n");
  }else if(pid == 0){
    close(pipe_des1[1]);
    close(pipe_des2[0]);
    p_p = fdopen(pipe_des1[0], "r");
    p_h = fdopen(pipe_des2[1], "w");
    while(fgets(buf, 1024, p_p) != NULL){
      for(int i = 0; i<sizeof(buf); i++){
        buf[i]=toupper(buf[i]);
      }

      fputs(buf, p_h);
      fflush(p_h);
    }

  }else{
    close(pipe_des1[0]);
    close(pipe_des2[1]);
    p_p = fdopen(pipe_des1[1],"w");
    p_h = fdopen(pipe_des2[0], "r");

    while (fgets(buf, 1024, stdin) != NULL) {
      fputs(buf, p_p);
      fflush(p_p);
      fgets(buf, 1024, p_h);
      printf("%s\n", buf);
    }
  }

  return 0;
}
