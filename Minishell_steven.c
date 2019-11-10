#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "parser.h"
#include <signal.h>

char buf[1024];
char buf2[1024];
char buf3[1024];
tline * line , *line2;
int i,j;
pid_t pid1;
int pipe_hijo[2];
int pipe_padre[2];
FILE * p_lectura, * p_escri,* fich_lectura_padre;

void manejador_hijo(int sig){
    if (sig == SIGUSR1){
        close(pipe_hijo[0]);
        dup2(pipe_hijo[1],1);//cambio la salida estandar al pipe[1]. 0 entrada estandar 1 salida estandar
        if ( execvp(line->commands[0].argv[0],line->commands[0].argv) < 0 ){
            printf("mandato: No se encuentra el mandato\n");
        }

    }else if(sig ==SIGUSR2){
        close(pipe_hijo[0]);
        dup2(pipe_hijo[1],1);
        if(execvp(line->commands[0].argv[0],line2->commands[0].argv) < 0 ){
            printf("mandato: No se encuentra el mandato\n");
        }
    }

}



int main (void){
    printf("msh> ");
    signal (SIGUSR2,manejador_hijo);
    signal (SIGUSR1,manejador_hijo);

    while(fgets(buf, 1024, stdin)){
             line = tokenize(buf);
         if(line == NULL){
              continue;
         }
         pipe(pipe_hijo);
         pipe(pipe_padre);
         pid1 = fork();//pid1 tiene el pid del hijo P.ejem 1234
         if(line->redirect_output != NULL){//si se redirecciona la salida
            p_escri= fopen(line->redirect_output,"w+");
            kill(pid1,SIGUSR1);//Tiene el pid del hijo
            close(pipe_hijo[1]);
            read(pipe_hijo[0],buf2,1024);//leo la ejecucion del execvp del hijo.
            fputs(buf2,p_escri);
            fclose(p_escri);
         }
         if(line-> redirect_input!= NULL){
            p_lectura = fopen(line->redirect_input, "r+");
            close(pipe_hijo[1]);//el hijo no recibe
            fgets(buf3,1024,p_lectura);
            line2 = tokenize(buf3);
            printf("%s",line2->commands[0].argv[0]);
            p_escri= fopen(line->redirect_output,"w+");
            kill(pid1,SIGUSR2);
            read(pipe_hijo[0],buf2,1024);//leo la ejecucion del execvp del hijo.
            fputs(buf2,p_escri);
            fclose(p_escri);
         }
         printf("msh> ");
    }
}
