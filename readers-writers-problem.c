#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "asm/unistd.h"
#include <semaphore.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define ITERATION 3
#define MAX_WRITERS 2
#define MAX_READERS 5

static int *data;
static int *reader_count;
sem_t *sem_writer, *sem_reader;

int main (int argv, char **argc) {
    if((sem_writer = sem_open("/sem_writer", O_CREAT, 0644, 1)) == (sem_t*)-1){
        printf(" %i  %s \n", errno, strerror(errno));
        printf("Error in sem_writer\n");
    }

    if((sem_reader = sem_open("/sem_reader", O_CREAT, 0644, 1)) == (sem_t*)-1){
        printf(" %i  %s \n", errno, strerror(errno));
        printf("Error in sem_reader\n");
    }

    data = mmap(NULL, sizeof *data, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *data = 1;

    reader_count = mmap(NULL, sizeof *reader_count, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *reader_count = 0;

    int reader_counter = 0;
    while (reader_counter++ < MAX_READERS) {
            if (fork() == 0) { 
                    for(int i = 0; i < ITERATION; i++){
                                sem_wait(sem_reader);
                                sleep(1);

                                *reader_count = *reader_count + 1;
                                if (*reader_count == 1) sem_wait(sem_writer);
                                sem_post(sem_reader);

                                printf("Reader %d - reads %d\n", reader_counter, *data);

                                sem_wait(sem_reader);
                                *reader_count = *reader_count - 1;
                                if(*reader_count == 0) sem_post(sem_writer);

                                sem_post(sem_reader);
                    }
                    return;
            }
    } 

    int writer_counter = 0;
    while (writer_counter++ < MAX_WRITERS) {
            if (fork() == 0) {
                    for (int j = 0; j < ITERATION; j++){
                        sem_wait(sem_writer);

                        *data = *data + 1;
                        printf("Writer %d - writes %d\n", writer_counter, *data);
                        sleep(1);
                        
                        sem_post(sem_writer);
                        sleep(1);
                    }
                    return;  
            }
    }

    sem_close(sem_writer);
    sem_close(sem_reader);
    sem_unlink("/sem_writer");
    sem_unlink("/sem_reader");
    return 0;
}