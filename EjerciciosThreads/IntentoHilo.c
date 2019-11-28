#include <stdio.h>
#include <pthread.h>

int sum = 0;
void *suma(void *num){
    int limite = *(int *) num;

    for(int i = 0; i <= limite; i++){
        sum += i;
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]){
    pthread_t tid;
    int N = 10;

    pthread_create(&tid, NULL, suma, (void *) &N);
    pthread_join(tid, NULL);
    printf("SUMA = %d\n", sum);
    return 0;
}
