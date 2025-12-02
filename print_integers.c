#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void for_each_String_(long long* elem, long long * elems){
    static int incr = 0;
    //static long long threadConnu[3];
    *elem = elems[incr];
    if(*elem == -1){
        //L'objectif le thread choisi de se fermer : 
        //comme en mode recursive terminal
        //printf("Allo : %d\n", *elem);
        //Kill Thread
        long long * entete_fin = &elems[incr];
        //printf("Thread 1 +: %p\n", test_thread);
        printf("Thread 1 *: %p\n", entete_fin[0]); //Début
        printf("Thread 1 -: %p\n", entete_fin[1]); //Adresse du thread
        free(elems);
        //pthread_cancel(test_thread);
        pthread_cancel(entete_fin[1]);
    }else{
        //Run Thread
       // printf("Allo2 : %d\n", *elem);
       incr++;

    }
    
    //printf("Val : %d\n", elems[incr]);

}

#define for_each_string(A, B) label: for_each_String_(A, B); 


typedef struct Data {
    int capacity;
    long long * buffer;
} Data;

typedef struct  Callback {
    int (*callback)(long long);
} Callback;


int fake_main(struct Data*d, struct Callback * c){
    long long valeur = 0;
    //int entiers[d->capacity] = ;
    for_each_string(&valeur, d->buffer){
        //printf("Hello World %d \n", valeur);
        c->callback(valeur);
        goto label;
    }
    //No execution
}

int body(long long val){
    printf("Hello World %ld \n", val);
    return 0;
}



void *thread_test_run (void *v) // I must not modify this function
{
    //-1: début des entetes de fin
    Data data = {7};
    data.buffer = (long long *) malloc( data.capacity *sizeof(long long) );
    if(data.buffer == NULL){
        return NULL;
    }
    pthread_t threadId = pthread_self();
    long long temp[] = {1,2,3,4,5, -1, threadId};
    memcpy(data.buffer, temp, sizeof(temp));
    Callback method = {&body};
    
    fake_main(&data, &method);
    
    return NULL;
}


int createTask()
{
    pthread_t test_thread;
    pthread_create(&test_thread, NULL, &thread_test_run, NULL);
    //pthread_join(test_thread, NULL);
    pthread_detach(test_thread);
    return 0;
}



int main()
{
    createTask();
    createTask();
    return 0;
}




