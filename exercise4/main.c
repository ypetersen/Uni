#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <stdio.h>
#include "matrix_data.h"

double A[dimM][dimN];
double B[dimN][dimM];
double B2[dimN][dimM];
double C[dimM][dimM];

double* currentB;
double* nextB = *B;

int done = k;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int calculate[k-1];
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

void permitCalc() {
    for(int i = 0; i < k; i++) {
	    calculate[i] = 1;
    }
}

void initCalc() {
    for(int i = 0; i < k; i++) {
	    calculate[i] = 0;
    }
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void createA() {
    int i;
    int j;
    for ( i = 0; i < dimM; i++ ) {
        for ( j = 0; j < dimN; j++ ) {
            A[i][j] = fRand(lb,ub);
        }
    }
}

void createB() {
    int i;
    int j;
    for ( j = 0; j < dimM; j++ ) {
        for ( i = 0; i < dimN; i++ ) {
            *(nextB + i * dimN + j) = fRand(lb,ub);
        }
    }
}

void multiplyAB(int id) {
    int row = id;
    int ci = 0;
    while(row < dimM) {
//        printf("thread %d calculating row %d\n",id, row);
        for(int col = 0; col < dimM; col++) {
            double aux = 0;
            for(int i = 0; i < dimN; i++) {
                aux += A[row][i] * *(currentB + i * dimN + col);
            }
            C[row][col] = aux;
        }
        ci++;
        row = id + ci * k;
    }
}

void printC() {
    for(int i = 0; i < dimM; i++) {
        for(int j = 0; j < dimM; j++) {
            printf("%e", C[i][j]);
        }
    }
}

void swap() {
//    printf("swap-buffer\n");
    if(currentB == *B) {
        currentB = *B2;
        nextB = *B;
    } else {
        currentB = *B;
        nextB = *B2;
    }
}

void* leadworker(void* args) {
    /**
    *   1. create B for nextB
    *   2. swap() nextB > currentB
    *   3. signal workerthreads to start
    */
    createA();
    for(int i = 0; i < numMultiplications; i++) {
        createB();
        printf("%d", i);fflush(0);
        //wait for every worker to finish before swapping B
        pthread_mutex_lock(&mutex);
        while(done < k) {
            pthread_cond_wait(&cond, &mutex);
        }
        done = 0;
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex2);
        swap();
        permitCalc();
        //signal workers to resume working
        pthread_cond_broadcast(&cond2);
        pthread_mutex_unlock(&mutex2);
    }
    printf("leadworker finished\n");
    pthread_exit(NULL);
}

void* worker(void* args) {
    int id= *(int*)args;
    for(int i = 0; i < numMultiplications; i++) {
        pthread_mutex_lock(&mutex2);

        if(calculate[id] == 0){
            pthread_cond_wait(&cond2, &mutex2);
	    }
	    calculate[id] = 0;
        pthread_mutex_unlock(&mutex2);

        multiplyAB(id);

        pthread_mutex_lock(&mutex);
        done++;

	    if(done >= k){
        	pthread_cond_signal(&cond);
	    }
        pthread_mutex_unlock(&mutex);
    }
    printf("%d finished\n", id);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    initCalc();
    //workload =
    pthread_t threads[k+1];
    int ids[k+1];
    for(int i = 0; i < k+1; i++) {
        ids[i] = i;
        if(i == k) {
            pthread_create(&threads[i], NULL, leadworker, NULL);
        } else {
            pthread_create(&threads[i], NULL, worker, &ids[i]);
        }
    }

    for(int i = 0; i < k+1; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
