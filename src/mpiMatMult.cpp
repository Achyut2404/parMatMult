// Homework 1: ME766
// Achyut Panchal: 09D01002
// This code calculates matrix multiplication with openmpi

#include <iostream>
#include <stdio.h>
#include "mpi.h"

// Import functions printMat and serialMatMult
void printMat(float **a, int n, int m);
float** serialMatMult(float **A, float **B, int N, int M, int P);
float** randMat1(int M, int N);
float** randMat2(int M, int N);
float matDiffMax(float** A, float** B, int n, int m);

int* parRow(int N, int NProcs, int my_PE_num){
	/* Divides row division of matrix for mpi parallel */
	int startRow = my_PE_num*(N/NProcs);
	int endRow = startRow + (N/NProcs) -1;
	int NPar = (N/NProcs);
	int leftRows = N%NPar;

	if (leftRows != 0 && my_PE_num<=(leftRows-1)){
		NPar = NPar + 1;
		startRow = startRow + my_PE_num;
		}
	
	if (leftRows != 0 && my_PE_num>(leftRows-1)){
		startRow = startRow + leftRows;
		}

	endRow = startRow + NPar -1;

	int *parRowDat;
	parRowDat = new int[3];
	parRowDat[0] = startRow;
	parRowDat[1] = endRow;
	parRowDat[2] = NPar;
	return(parRowDat);
	}

int main(int argc, char** argv){
	int i,j,k;
	int my_PE_num,NProcs;
	
	// Check whether MPI and serial gives the same result
	bool check = 0;
	
	//Initiate MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_PE_num);
	MPI_Comm_size(MPI_COMM_WORLD, &NProcs);
	
	MPI_Status status;

	int N;
	
	if (my_PE_num==0){
		// Get input for matrix size
		std::cout<< "Enter matrix size: "<<'\n'; 
		std::cin >> N;
		}
	
	// Broadcast N Value
	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// Check whether total number of processors is acceptable or not
	if (NProcs>N){
		std::cout << "Process number should be less then matrix dimension"<<std::endl;
		}

	float **A, **B, **C;
	// Treat Process 0 as master process
	//Generate matrices A and B in master process
	if (my_PE_num==0){
		
		A = randMat1(N, N);

		B = randMat2(N, N);
		}
	
	// Divide matrix A in parts for different process
	int *parRowDat = parRow(N, NProcs, my_PE_num);
	int startRow = parRowDat[0];
	int endRow = parRowDat[1];
	int NPar = parRowDat[2];
	
	// Initiate APar and BPar
	float **APar;
	APar = new float *[NPar];
	for (i=0;i<NPar;i++){
		APar[i] = new float[N];
		}

	float **BPar;
	BPar = new float *[N];
	for (i=0;i<N;i++){
		BPar[i] = new float[N];
		}
	
	// Send appropriate arrays from master process to other process
	
	int startRowToSend, endRowToSend, NParToSend;
	float* toSendPtr, *toRecvPtr;	
	// Send A matrix
	if (my_PE_num==0){
	
		for (i=0;i<NPar;i++){
			APar[i] = A[i];
			}

		for (i=1;i<NProcs;i++){
			int *rowDat = parRow(N, NProcs, i);
			startRowToSend = rowDat[0];
			endRowToSend = rowDat[1];
			NParToSend = rowDat[2];
			for (j=0; j<NParToSend; j++){
				toSendPtr = &A[startRowToSend + j][0];
				MPI_Send(toSendPtr , N, MPI_FLOAT, i, j, MPI_COMM_WORLD);
				}
			}
		}
	
	// Receive messages
	if (my_PE_num!=0){
		for (j=0;j<NPar;j++){
			MPI_Recv(&APar[j][0] , N, MPI_FLOAT, 0 , j, MPI_COMM_WORLD, &status);
			}
		}

	// Send B matrix
	if (my_PE_num==0){
		BPar = B;
		for (i=1;i<NProcs;i++){
			for (j=0; j<N; j++){
				MPI_Send(&B[j][0] , N, MPI_FLOAT, i, j+N, MPI_COMM_WORLD);
				}
			}	
		}
	
	// Receive messages
	if (my_PE_num!=0){
		for (j=0;j<N;j++){
			MPI_Recv(&BPar[j][0] , N, MPI_FLOAT, 0 , j+N, MPI_COMM_WORLD, &status);
			}
		}
	
	//Calculate Cpar matrix
	float **CPar;
	CPar = serialMatMult(APar,BPar,NPar,N,N);
	
	// Let the master process get back all values and construct back the original matrix
		
	// Initiate C matric in master process
	if (my_PE_num==0){
		C = new float *[N];
		for (i=0;i<N;i++){
			C[i] = new float[N];
			}
		}


	// Send C Matrix
	if (my_PE_num!=0){
		for (j=0;j<NPar;j++){
			MPI_Send(&CPar[j][0] , N, MPI_FLOAT, 0 , j+2*N, MPI_COMM_WORLD);
			}
		}
	
	// MPI receive	
	if (my_PE_num==0){
		
		for (i=0;i<NPar;i++){
			C[i] = CPar[i];
			}

		for (i=1;i<NProcs;i++){
			int *rowDat = parRow(N, NProcs, i);
			startRowToSend = rowDat[0];
			endRowToSend = rowDat[1];
			NParToSend = rowDat[2];
			for (j=0; j<NParToSend; j++){
				toRecvPtr = &C[startRowToSend+j][0];
				MPI_Recv(toRecvPtr , N, MPI_FLOAT, i, j+2*N, MPI_COMM_WORLD, &status);
				}
			}
		}

	// Check if there is some error by comparing answer to serial answer
	if (my_PE_num==0){
		if (check==1){
			// Do serial Calculation
			float **Cser;
			Cser = serialMatMult(A,B,N,N,N);
			float errMPI;
			errMPI = matDiffMax(C,Cser,N,N);
			std::cout << "Error between serial and MPI is " << errMPI << std::endl;
			}
		}
	
	MPI_Finalize();
	return(0);
	}

