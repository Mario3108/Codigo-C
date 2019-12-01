#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define FILOSOFOS 5


int estado_filosofo[FILOSOFOS];
int palillo[FILOSOFOS];
pthread_mutex_t mutex;
pthread_cond_t espera [FILOSOFOS];

char comiendo[] = "comiendo";
char esperando[] = "esperando";
char pensando[] = "pensando";

char *estado(int i){
    if(i == 0){
        return pensando;
    }
    if (i == 1){
        return esperando;
    }
    if(i == 2){
        return comiendo;
    }
    return NULL;
}

void print_estado(){
    printf("Estado: 0 => %s\t1 => %s\t2 => %s\t3 => %s\t4 => %s\n", estado(estado_filosofo[0]), estado(estado_filosofo[1]), estado(estado_filosofo[2]), estado(estado_filosofo[3]),
            estado(estado_filosofo[4]));
}

void *filosofo(void *num){
    int fil_id = *(int *) num;
    while(1){
        estado_filosofo[fil_id] = 0;
        printf("Filosofo %d pensando\n", fil_id);
        print_estado();
        sleep((rand()%2)+1);

        estado_filosofo[fil_id] = 1;
        printf("Filosofo %d quiere comer\n", fil_id);
        print_estado();

        pthread_mutex_lock(&mutex);
        while(palillo[fil_id] || palillo[(fil_id+1) % FILOSOFOS]){
            pthread_cond_wait(&espera[fil_id], &mutex);
        }

        palillo[fil_id] = 1;
        palillo[(fil_id+1)%FILOSOFOS] = 1;

        pthread_mutex_unlock(&mutex);

        estado_filosofo[fil_id] = 2;
        printf("Filosofo %d comiendo\n", fil_id);
        print_estado();
        sleep((rand() % 2) + 1);

        pthread_mutex_lock(&mutex);
        palillo[fil_id] = 0;
        palillo[(fil_id+1)%FILOSOFOS] = 0;
        pthread_cond_signal(&espera[fil_id]);
        pthread_cond_signal(&espera[(fil_id + 1)%FILOSOFOS]);
        pthread_mutex_unlock(&mutex);
    }
}

int main(){
    pthread_t th;
    int i;
    int fil_id[FILOSOFOS];

    pthread_mutex_init(&mutex, NULL);

    for(i = 0; i<FILOSOFOS; i++){
        palillo[i] = 0;
        pthread_cond_init(&espera[i], NULL);
        fil_id[i] = i;
        pthread_create(&th, NULL, filosofo, (void *)&fil_id[i]);
    }
    while(1);
}
