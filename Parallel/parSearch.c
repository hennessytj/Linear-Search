#include <pthread.h>
#include <stdio.h>

#define FALSE 0
#define TRUE  1
#define V 1
#define N 10
#define NUM_THREADS 10

int A[] = {1, 7, 9, -33, 1, 4, 11, 0, 891, 3};
int FOUND = FALSE;
int COUNT = 0;

pthread_mutex_t lock;

void *partition(void *p)
{
    int i;
    long tid = (long) p;
    int numCells = N / NUM_THREADS;
    int remainingCells = N % NUM_THREADS;
    int startCell = numCells * tid;
    int endCell;
    
    // Last thread is one less than NUM_THREADS [0..NUM_THREADS)
    // Last thread is assigned remaining number of rows, in the
    //   case is N - 1
    if (tid == NUM_THREADS - 1)
        endCell = numCells * tid + numCells + remainingCells;
    else
        endCell = numCells * tid + numCells;

    for (i = startCell; i < endCell; i++)
        printf("Tid %d does cell %d\n", tid, i);
    
    for (i = startCell; i < endCell; i++)
        if (A[i] == V) 
        { 
            FOUND = TRUE;
            pthread_mutex_lock(&lock);
            COUNT++;
            pthread_mutex_unlock(&lock);
        }
    
    pthread_exit(NULL);
}

// pthread entry point function

int main(void)
{
    int i;
    long t;
    void *status;
    pthread_t tid[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);

    for (t = 0; t < NUM_THREADS; t++)
        pthread_create(&tid[t], NULL, partition, (void *) t);
    
    for (t = 0; t < NUM_THREADS; t++)
        pthread_join(tid[t], &status);

    printf("%d found = %d times\n", V, COUNT);
    
    pthread_mutex_destroy(&lock);

    return 0;
}
