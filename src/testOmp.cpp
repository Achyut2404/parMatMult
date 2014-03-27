// Homework 1: ME766
//Achyut Panchal: 09D01002
// This code compares results by openMP and serial multiplication, and tells if there is any error

#include <iostream>
#include <stdio.h>

//import matrix multiply and error functions
void freeMat(float** a, int n, int m);
float** serialMatMult(float **A, float **B, int N, int M, int P);
float** ompMatMult(float **A, float **B, int N, int M, int P);
float matDiffMax(float **A, float **B, int n, int m);
float** randMat1(int M, int N);
float** randMat2(int M, int N);

int main(){
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
	
	//Find multiplication
	float **CSer;
	float **COmp;
	
	//Serial
	CSer = serialMatMult(A,B,N,N,N);

	//OpenMP
	COmp = ompMatMult(A,B,N,N,N);
	
	//Check if there is error in parallel calculation
	float errmp;
	errmp = matDiffMax(CSer,COmp,N,N);
	std::cout << "Maximum Error in openMP is: "<< errmp << '\n';
	
	// Free matrix spaces
	freeMat(A,N,N);
	freeMat(B,N,N);
	freeMat(CSer,N,N);
	freeMat(COmp,N,N);

	return(0);
	}

