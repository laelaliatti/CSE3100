#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

// Search TODO to find the locations where code needs to be completed

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

static void * thread_main(void * p_arg)
{
    // TODO
    thread_arg_t *arg = (thread_arg_t*) p_arg; //type cast to that data type.
    TMatrix*m = arg->m; //storing m in m
    TMatrix*n = arg->n;
    TMatrix*t = arg->t;
    unsigned id = arg->id;
    // figure out which rows this thread should handle
    unsigned int rows_per_thread = m->nrows / NUM_THREADS;
    unsigned int start = id * rows_per_thread;
    unsigned int end;

    if (id == NUM_THREADS - 1)
        end = m->nrows;   // last thread handles remainder
    else
        end = start + rows_per_thread;
    
    for (unsigned int i = start; i < end; i++) {
        for (unsigned int j = 0; j < n->ncols; j++) {
            TElement sum = 0;
            for (unsigned int k = 0; k < m->ncols; k++) {
                sum += m->data[i][k] * n->data[k][j];
            }
            t->data[i][j] = sum;
        }
    }


    return NULL;
}

/* Return the sum of two matrices.
 *
 * If any pthread function fails, report error and exit. 
 * Return NULL if anything else is wrong.
 *
 * Similar to mulMatrix, but with multi-threading.
 */
TMatrix * mulMatrix_thread(TMatrix *m, TMatrix *n)
//Think about how you’d split the work if you had 2 people doing matrix multiplication by hand.
{
    if (    m == NULL || n == NULL
         || m->ncols != n->nrows )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, n->ncols);
    if (t == NULL)
        return t;

    // TODO
    pthread_t threads[NUM_THREADS];
    thread_arg_t args[NUM_THREADS];
      // create threads
    for (unsigned int i = 0; i < NUM_THREADS; i++) {
        args[i].id = i;
        args[i].m = m;
        args[i].n = n;
        args[i].t = t;

        if (pthread_create(&threads[i], NULL, thread_main, &args[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }
    // join threads //waits for them to compile.
    for (unsigned int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    return t;
}
