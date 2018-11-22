

#ifndef MATRIX_DATA_H
#define MATRIX_DATA_H

#define  dimM   1000
#define  dimN   2000
#define     k      8

#define numMultiplications 10

#define lb -1.0
#define ub 1.0

extern int columnOfBReady[dimM];
extern int rowOfCReady[dimM];

extern double A[dimM][dimN];
extern double B[dimN][dimM];
extern double C[dimM][dimM];


#endif
