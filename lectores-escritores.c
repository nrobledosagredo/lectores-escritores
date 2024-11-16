#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "asm/unistd.h"
#include <semaphore.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>


#define ITERACION 3
#define MAX_ESCRITORES 2
#define MAX_LECTORES 5

static int *dato;
static int *n_lectores;
sem_t *sem_esc, *sem_lec;

int main (int argv, char **argc) {
    if((sem_esc = sem_open("/sem_esc", O_CREAT, 0644, 1)) == (sem_t*)-1){
        printf(" %i  %s \n", errno, strerror(errno));
        printf("Error en sem_esc\n");
    }

    if((sem_lec = sem_open("/sem_lec", O_CREAT, 0644, 1)) == (sem_t*)-1){
        printf(" %i  %s \n", errno, strerror(errno));
        printf("Error en sem_lec\n");
    }

    dato = mmap(NULL, sizeof *dato, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *dato = 1;

    n_lectores = mmap(NULL, sizeof *n_lectores, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *n_lectores = 0;


    int conteo_lec = 0;
    while (conteo_lec++ < MAX_LECTORES) {
            if (fork() == 0) { 
                    for(int i = 0; i < ITERACION; i++){
                                sem_wait(sem_lec);
                                sleep(1);

                                *n_lectores = *n_lectores + 1;
                                if (*n_lectores == 1) sem_wait(sem_esc);
                                sem_post(sem_lec);

                                printf("Lector %d - lee %d\n", conteo_lec, *dato);

                                sem_wait(sem_lec);
                                *n_lectores = *n_lectores - 1;
                                if(*n_lectores == 0) sem_post(sem_esc);

                                sem_post(sem_lec);

                    }
                    return;
            }
    } 

    int conteo_esc = 0;
    while (conteo_esc++ < MAX_ESCRITORES) {
            if (fork() == 0) {
                    for (int j = 0; j < ITERACION; j++){
                        sem_wait(sem_esc);

                        *dato = *dato + 1;
                        printf("Escritor %d - escribe %d\n", conteo_esc, *dato);
                        sleep(1);
                        
                        sem_post(sem_esc);
                        sleep(1);
                    }
                    return;  
            }
    }

    sem_close(sem_esc);
    sem_close(sem_lec);
    sem_unlink("/sem_esc");
    sem_unlink("/sem_lec");
    return 0;
}
