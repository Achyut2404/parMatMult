all: serMatMult ompMatMult testOmp mpiMatMult

mpiMatMult: matFuncs.o mpiMatMult.o
	mpic++ mpiMatMult.o matFuncs.o -o mpiMatMult

serMatMult: serMatMult.o matFuncs.o
	g++ serMatMult.o matFuncs.o -o serMatMult
	
ompMatMult: ompMatMult.o matFuncs.o ompMatFuncs.o
	g++ ompMatMult.o matFuncs.o ompMatFuncs.o -o ompMatMult -fopenmp
	
testOmp: testOmp.o matFuncs.o ompMatFuncs.o
	g++ testOmp.o matFuncs.o ompMatFuncs.o -o testOmp -fopenmp

serMatMult.o: serMatMult.cpp
	g++ -c serMatMult.cpp

matFuncs.o: matFuncs.cpp
	g++ -c matFuncs.cpp
	
ompMatFuncs.o: ompMatFuncs.cpp
	g++ -c ompMatFuncs.cpp -fopenmp

ompMatMult.o: ompMatMult.cpp
	g++ -c ompMatMult.cpp
	
testOmp.o: testOmp.cpp
	g++ -c testOmp.cpp

mpiMatMult.o: mpiMatMult.cpp
	mpic++ -c mpiMatMult.cpp

clean:
	rm -rf *o serMatMult ompMatMult testOmp mpiMatMult
