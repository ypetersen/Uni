#define _GNU_SOURCE
#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <stdio.h>
#include "matrix_data.h"

double A[dimM][dimN];
double B[dimN][dimM];
double C[dimM][dimM];

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
            B[i][j] = fRand(lb,ub);
        }
    }
}

void multiplyAB() {
    
    int row, col;
    for ( row = 0; row < dimM; row++ ) {
        for ( col = 0; col < dimM; col++ ) {
            int i;
            double aux = 0;
            for ( i=0; i < dimN; i++ ) {
                aux += A[row][i]*B[i][col];
            }
            C[row][col] = aux;
        }
    }
}




int main(int argc, char *argv[]) {
    
    int i;
    
    createA();
    
    for ( i = 0; i < numMultiplications; i++ ) {
        printf("%d ",i); fflush(0);
        createB();
        multiplyAB();
    }
    
    exit(0);
    
}
