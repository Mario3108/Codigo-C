#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
void *funcionThread(void *parametro);

#define TAMANO_BUFFER 10000
int buffer[TAMANO_BUFFER];

#ifdef MUTEX
pthread_mutex_t mutexBuffer;
#endif


int main(void){
    pthread_t idHilo;

    int error;

    int contador = 0;

    int i;

#ifdef MUTEX
    pthread_mutex_init(&mutexBuffer, NULL);
#endif

    error = pthread_create(&idHilo, NULL, funcionThread, NULL);
    if(error != 0){
        perror("No puedo crear thread");
        return 1;

    }
    
    while(1){
#ifdef MUTEX
        pthread_mutex_lock(&mutexBuffer);
#endif
        for(int i = 0; i<TAMANO_BUFFER; i++){
            buffer[i] = contador;
        }

#ifdef MUTEX
        pthread_mutex_unlock(&mutexBuffer);
#endif
        contador++;
    }
}

void *funcionThread(void *parametro){
    int i;
    int elementoDistinto = 0;

    while(1){
#ifdef MUTEX
        pthread_mutex_lock(&mutexBuffer);
#endif
        for(i = 1; i<TAMANO_BUFFER; i++){
            if(buffer[0] != buffer[i]){
                elementoDistinto = 1;
                break;
            }
        }

        if(!elementoDistinto){
            printf("Hijo: Error. Elementos de buffer distintos\n");
        }else{
            printf("Hijo: Correcto\n");
        }

        elementoDistinto = 0;

#ifdef MUTEX
        pthread_mutex_unlock(&mutexBuffer);
#endif
    }
}















