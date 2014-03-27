// Homework 1: ME766
// Achyut Panchal: 09D01002
// This code defines basic matrix operations

#include <iostream>
#include<stdio.h>
#include <omp.h>

float** ompMatMult(float **A, float **B, int N, int M, int P){
	/* Serial matrix multiply of N x M and M X P matrices A and B */
	int i,j,k;
	float val;
	int tid;

	// Initiate C matrix
	float **C;
	C = new float *[N];
	for (i=0;i<N;i++){
		C[i] = new float[P];
		}
	
	// Calculate matrix multiplication
	#pragma omp parallel for private(val,tid,j,k)
	
	for(i=0;i<N;i++){
		// print threa id
		tid = omp_get_thread_num();
		//printf("Thread id is %d\n",tid);
		for(j=0;j<P;j++){
			// Calculate C[i][j]
			val = 0;
			for(k=0;k<M;k++){
				val = val + A[i][k]*B[k][j];
				}
			C[i][j] = val;
			}
		}
	return(C);
	}

