#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include "parser.h"
char buf[1024];
char buf2[1024];
tline * line;
int i,j;
int pid1;
int pipe_des1[2];
int pipe_des2[2];
int fd[2];
FILE *p_p;
FILE *p_h;
FILE *lectura;
FILE *lectura2;
int cont;


int hijos[5];
void manejador_hijo(int sig);

int main(void) {

    signal(SIGUSR1, manejador_hijo);
    signal(SIGUSR2, manejador_hijo);
	printf("msh> ");
	while (fgets(buf, 1024, stdin)) {
        line = tokenize(buf);

        if (line==NULL) {
    		continue;
      }
      if (line->redirect_input != NULL) {
              printf("redirección de entrada: %s\n", line->redirect_input);
              close(fd[1]);
              close(STDIN_FILENO);
              p_p = fopen(line->redirect_input, "r");
              dup2(p_p, fd[0]);
      }
      if (line->redirect_output != NULL) {
              printf("redireccion de salida: %s\n", line->redirect_output);
              close(fd[0]);
              close(STDOUT_FILENO);
              p_p = fopen(line->redirect_output, "w");
              dup2(p_p, fd[1]);
              kill(pid1 , SIGUSR2);
              close(fd[1]);

        }

        if (line->redirect_error != NULL) {
              printf("redireccion de error: %s\n", line->redirect_error);
              close(fd[0]);
              close(STDERR_FILENO);
              p_p = fopen(line->redirect_error, "w");
              dup2(p_p, fd[1]);
              close(fd[1]);

        }

		if (line->background) {
			printf("comando a ejecutarse en background\n");
		}

            int pipes[line->ncommands-1][2];
            for(i = 0; i<line->ncommands-1; i++){
              pipe(pipes[i]);
            }
            pipe(fd);
            for (i=0; i<line->ncommands; i++) {
                printf("orden %d (%s):\n", i, line->commands[i].filename);
                for (j=0; j<line->commands[i].argc; j++) {
                  printf("  argumento %d: %s\n", j, line->commands[i].argv[j]);
                }

                int pid2 = fork();
                if(pid2 == 0){
                  printf("hola soy el hijo numero %d con comando %s\n",i, line->commands[i].argv[0]);
                  if(line->ncommands > 1){
                    if(i == 0){
                      for(int k = 0; k<line->ncommands-1; k++){
                        if(k != i){
                          close(pipes[k][0]);
                          close(pipes[k][1]);
                        }
                      }
                      close(pipes[i][0]);
                      close(STDOUT_FILENO);
                      dup(pipes[i][1]);
                    }if(i > 0 && i<line->ncommands-1){
                      for(int k = 0; k<line->ncommands-1; k++){
                        if(k != i && k != i-1){
                          close(pipes[k][0]);
                          close(pipes[k][1]);
                        }
                      }
                      close(pipes[i-1][1]);
                      close(pipes[i][0]);
                      close(STDIN_FILENO);
                      dup(pipes[i-1][0]);
                      close(STDOUT_FILENO);
                      dup(pipes[i][1]);

                    }else{
                      for(int k = 0; k<line->ncommands-1; k++){
                        if(k != i-1){
                          close(pipes[k][0]);
                          close(pipes[k][1]);
                        }
                      }
                      close(pipes[i-1][1]);
                      close(STDIN_FILENO);
                      dup(pipes[i-1][0]);
                    }
                    while(1);
                  }else{
                    while(1);
                  }



                }else{
                  hijos[i] = pid2;
                  sleep(2);
                  kill(hijos[i], SIGUSR1);
                  wait(hijos[i]);
                  wait(hijos[line->ncommands-1]);
                }

        }

        printf("msh> ");

	}

	return 0;
}

void manejador_hijo(int sig){
    if(execvp(line->commands[i].argv[0], line->commands[i].argv)<0){
        printf("No se encuentra el comando\n");
    }
    exit(0);
}
