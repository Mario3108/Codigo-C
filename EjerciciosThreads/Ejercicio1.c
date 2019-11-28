#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void *funcion1(void *arg){
    printf("Hola, soy el thread 1\n");
    sem_wait(&sem);
    printf("Y esto se tiene que imprimir después\n");
    pthread_exit(0);
}

void *funcion2(void *arg){
    printf("Hola, soy el thread 2\n");
    printf("Esto se tiene que imprimir primero\n");
    sem_post(&sem);

    pthread_exit(0);
}


int main(){
    pthread_t tid1, tid2;

    sem_init(&sem, 0, 0);

    
    pthread_create(&tid1, NULL, funcion1, NULL);
    pthread_create(&tid2, NULL, funcion2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}
