#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include "parser.h"
#include <sys/types.h>
#include <sys/wait.h>
char buf[1024];
tline * line;
int i,j;
int pid;
int pipe_des1[2];
int pipe_des2[2];
int fd[2];
FILE *p_p;
FILE *p_h;
int cont;
int pid2;
int *hijos;
int **pipes;

//TODO:
// -mandato cd
// -redireccionamiento entrada/salida con mas de un mandato
// -Cambiar el execvp a una señal (si se puede, si no pues fuck it)
// -estructura de procesos para el jobs

int main(void) {
	printf("1msh> ");
	while (fgets(buf, 1024, stdin)) {
    line = tokenize(buf);


    if (line==NULL) {
      continue;
    }

      if(line->ncommands == 1){//Caso de que solo haya un mandato
        pipe(fd);
        pid = fork();

        if (line->redirect_input != NULL) {
          if(pid == 0){
            printf("redirección de entrada: %s\n", line->redirect_input);
            close(fd[1]);
            close(STDIN_FILENO);
            p_p = fopen(line->redirect_input, "r");
            dup2(p_p, fd[0]);
            close(fd[0]);
          }
        }

      	if (line->redirect_output != NULL) {
              if(pid == 0){
                  printf("redireccion de salida: %s\n", line->redirect_output);
                  close(fd[0]);
                  close(STDOUT_FILENO);
                  p_p = fopen(line->redirect_output, "w");
                  dup2(p_p, fd[1]);
                  close(fd[1]);
              }
          }

          if (line->redirect_error != NULL) {
              if(pid == 0){
                  printf("redireccion de error: %s\n", line->redirect_error);
                  close(fd[0]);
                  close(STDERR_FILENO);
                  p_p = fopen(line->redirect_error, "w");
                  dup2(p_p, fd[1]);

                  close(fd[1]);
              }
          }

  		    if (line->background) {
  			       printf("comando a ejecutarse en background\n");
  		    }

          if(pid == 0){
            if(execvp(line->commands[0].argv[0], line->commands[0].argv)< 0){
                      char buff[1024];
                      char *salida = "No se ha encontrado el mandato\n";
                      strcpy(buff, salida);
                      fputs(buff, stderr);
            }
          }else{
            waitpid(pid, NULL, 0);
          }

      }
      if(line->ncommands >= 2){//Caso de que haya mas de un mandato

        hijos = malloc(line->ncommands * sizeof(int));
			  pipes = (int **) malloc((line->ncommands-1) * sizeof(int *));
        for (i=0; i<line->ncommands-1; i++){
            pipes[i] = (int *) malloc (2*sizeof(int));
            pipe(pipes[i]);
        }


        for (i=0; i<line->ncommands; i++) {
          pid = fork();
          if(pid < 0){
            fprintf(stderr, "Error al crear el hijo\n");
          }else if (pid == 0){
            if(i == 0){
              printf("Primer mandato\n");
              for(int c = 1; c < line->ncommands-1; c++){
                close(pipes[c][0]);
                close(pipes[c][1]);
              }
              close(pipes[0][0]);
              close(STDOUT_FILENO);
              dup(pipes[0][1]);


            }
            if (i > 0 && i < line->ncommands-1){
              sleep(0.5);
              printf("En el medio\n");
              for(int c = 0; c < line->ncommands-1; c++){
                if(c != i && c != i-1){
                  close(pipes[c][0]);
                  close(pipes[c][1]);
                }


                close(pipes[i-1][1]);
                close(STDIN_FILENO);
                dup(pipes[i-1][0]);

                close(pipes[i][0]);
                close(STDOUT_FILENO);
                dup(pipes[i][1]);
              }

            }
            if(i == line->ncommands-1){
              sleep(0.5);
              printf("Ultimo mandato\n");
              for(int c = 0; c<line->ncommands-2; c++){
                close(pipes[c][0]);
                close(pipes[c][1]);
              }

              close(pipes[i-1][1]);
              close(STDIN_FILENO);
              dup(pipes[i-1][0]);

            }


            execv(line->commands[i].filename, line->commands[i].argv);

          }else{
            hijos[i] = pid;

          }


        }

        for(int a = 0; a<line->ncommands-1; a++){
          close(pipes[a][1]);
          close(pipes[a][0]);
        }

        for(int k = 0; k<line->ncommands; k++){
          waitpid(hijos[k], NULL, 0);
        }
        free(pipes);
        free(hijos);

      }

      printf("2msh> ");

	}

	return 0;
}
