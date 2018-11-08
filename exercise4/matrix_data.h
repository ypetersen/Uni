

#ifndef MATRIX_DATA_H
#define MATRIX_DATA_H

#define  dimM      5
#define  dimN      5
#define     k     10

#define numMultiplications 10

#define lb -1.0
#define ub 1.0

extern int columnOfBReady[dimM];
extern int rowOfCReady[dimM];

extern double A[dimM][dimN];
extern double B[dimN][dimM];
extern double C[dimM][dimM];


#endif
