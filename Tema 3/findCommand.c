#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


char * cmd2path(char * cmd);

int main(int argc, char const *argv[]) {
  char *dir;
  if (argc != 2) {
    fprintf(stderr, "Error:%s+un mandato\n", argv[0]);
    return 1;
  }else{
    dir = cmd2path(argv[1]);
    if(dir == NULL){
      fprintf(stderr, "No se encuentran las mierdas\n");
    }else{
      fprintf(stdout, "%s esta en %s\n", argv[1], dir);
    }
  }

  return 0;
}
char * cmd2path(char * cmd){
  char buf[1024];
  char * str;
  char * tokens;

  if(strchr(cmd, '/')){
    if(!access(cmd, X_OK)){
      return strdup(cmd);
    }else{
      return NULL;
    }
  }

  str = getenv("PATH");
  if(!str){
    str = "/bin:/usr/bin";
  }

  tokens = strtok(str, ":");
  while (tokens) {
    //printf("%s %s\n",tokens, str);
    tokens = strtok(NULL, ":");
    if(tokens != NULL){
      strcpy(buf, tokens);
      strcat(buf, "/");
      strcat(buf, cmd);

      if(!access(buf, X_OK)){
        return strdup(buf);
      }
    }
  }
  return NULL;
}
