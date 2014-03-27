// Homework 1: ME766
// Achyut Panchal: 09D01002
// This code defines basic matrix operations

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

void printMat(float **a,int n, int m){
	/* prints a N X M matrix*/
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			std::cout << a[i][j] << ' ';
			}
		std::cout << std::endl;
		}
	}

float matDiffMax(float **A, float **B,int n, int m){
	/* Finds the maximum error between matrix elements*/
	int i,j;
	float errMax,err;
	errMax = 0.0;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			err = abs(A[i][j]-B[i][j]);
			errMax =  std::max(errMax,err);
			}
		}
	return(errMax);
	}

float** serialMatMult(float **A, float **B, int N, int M, int P){
	/* Serial matrix multiply of N x M into M X P square matrices A and B */
	int i,j,k;
	float val;

	// Initiate C matrix
	float **C;
	C = new float *[N];
	for (i=0;i<N;i++){
		C[i] = new float[P];
		}

	// Calculate matrix multiplication
	for(i=0;i<N;i++){
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

float** randMat1(int M, int N){
	/* return random matrix  if size M X N. */
	float **A;
	int i,j;
	A = new float *[M];
	for (i=0;i<M;i++){
		A[i] = new float[N];
		}

	// Assign random matrix values
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			A[i][j] = 1.0*(i+j)/N;
			}
		}
	return(A);
	}

float** randMat2(int M, int N){
	/* return random matrix  if size M X N. */
	float **B;
	int i,j;
	B = new float *[M];
	for (i=0;i<M;i++){
		B[i] = new float[N];
		}

	// Assign random matrix values
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			B[i][j] = 1.0*(i*j)/M/N;
			}
		}
	return(B);
	}
