// Homework 1: ME766
//Achyut Panchal: 09D01002
// This code calculates openMP matrix multiplication

#include <iostream>
#include <stdio.h>

// Import function printMat
void printMat(float **a, int n, int m);
float** ompMatMult(float **A, float **B, int N, int M, int P);
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
	
	// Print A and B matrix
	std::cout << "Printing matrix A" << std::endl;
	//printMat(A,N,N);
	std::cout << "Printing matrix B" << std::endl;
	//printMat(B,N,N);
	
	//Find multiplication
	float **C;
	
	//OpenMP
	C = ompMatMult(A,B,N,N,N);
	
	std::cout << "Printing matrix C" << std::endl;
	//printMat(C,N,N);
	
	return(0);
	}

