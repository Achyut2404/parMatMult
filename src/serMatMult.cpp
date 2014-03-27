// Homework 1: ME766
// Achyut Panchal: 09D01002
// This code calculates serial matrix multiplication

#include <iostream>
#include <stdio.h>

// Import functions printMat
void printMat(float **a, int n, int m);
float** serialMatMult(float **A, float **B, int N, int M, int P);
float** randMat1(int M, int N);
float** randMat2(int M, int N);

int main(){
	/* Driver function for matrix multiply*/
	int N;
	std::cout<< "Enter matrix size: "<<'\n'; 
	std::cin >> N;
	int i,j;
	
	float **A;
	A = randMat1(N, N);
	
	float **B;
	B = randMat2(N, N);

	// Assign random matrix values
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			A[i][j] = 1.0*(i+j)/N;
			B[i][j] = 1.0*(i*j)/N/N;
			}
		}
	
	// Print A and B matrix
	std::cout << "Printing A matrix" << std::endl;
	//printMat(A,N,N);
	std::cout << "Printing B matrix" << std::endl;
	//printMat(B,N,N);
	
	//Find multiplication
	float **C;
	
	//Serial
	C = serialMatMult(A,B,N,N,N);

	// Print C matrix
	std::cout << "Printing C matrix" << std::endl;
	//printMat(C,N,N);

	return(0);
	}
