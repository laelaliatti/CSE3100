#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

/* the main function of threads */
static void * thread_main(void * p_arg)
{
    // TODO

     thread_arg_t *arg = (thread_arg_t *)p_arg;
    TMatrix *m = arg->m;
    TMatrix *n = arg->n;
    TMatrix *t = arg->t;

    // Split rows between threads
    unsigned int start_row = arg->id * (m->nrows / NUM_THREADS);
    unsigned int end_row = (arg->id == NUM_THREADS - 1) ? m->nrows : (arg->id + 1) * (m->nrows / NUM_THREADS);

    for (unsigned int i = start_row; i < end_row; i++) {
        for (unsigned int j = 0; j < m->ncols; j++) {
            t->data[i][j] = m->data[i][j] + n->data[i][j];
        }
    }
    return NULL;
}

/* Return the sum of two matrices. The result is in a newly creaed matrix. 
 *
 * If a pthread function fails, report error and exit. 
 * Return NULL if something else is wrong.
 *
 * Similar to addMatrix, but this function uses 2 threads.
 */
TMatrix * addMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->nrows != n->nrows || m->ncols != n->ncols )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, m->ncols);
    if (t == NULL)
        return t;

    // TODO
    pthread_t threads[2];
    thread_arg_t args[2];
    for(int i = 0; i<2; i++)
    {
        args[i].id = i;
        args[i].t = t;
        args[i].m = m;
        args[i].n = n; 
        
    if (pthread_create(&threads[i], NULL, thread_main, &args[i]) != 0) {
        perror("pthread_create failed");
        exit(1);

    }
}
    for (int i = 0; i < NUM_THREADS; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
        perror("pthread_join failed");
        exit(1);
    }
}
    

    return t;
}
