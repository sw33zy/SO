#include "vector.h"
#include <stdio.h>
#include <stdlib.h>


#define N 100

//variável global
int v[N];

int main(int argc, char const *argv[])
{
	int f;
	//variável global
	printf("variável global\n" );
	fill(v,N,1);
	f = find(v,N,0);
	printf("1. f:= %d\n", f);
	f = find(v,N,1);
	printf("0. f:= %d\n", f);
	//search out of bounds
	fill(v,N+20,3);
	f = find(v + N, 20, 3);
	printf("3. f:= %d\n", f);
	f = find(v + N, 20, 1);
	printf("4. f:= %d\n", f);
	//bounded search 
	int i = 5, j = 8;
	int f_bound = find (v+i, N-j, 3);
	printf("Bounded find = %d\n", f_bound);

	//variaável local
	printf("variável local\n" );
	int vector[N];
	fill(vector,N,1);
	f = find(vector,N,0);
	printf("1. f:= %d\n", f);
	f = find(vector,N,1);
	printf("0. f:= %d\n", f);
	//search out of bounds
	fill(vector,N+20,3);
	f = find(vector + N, 20, 3);
	printf("3. f:= %d\n", f);
	f = find(vector + N, 20, 1);
	printf("4. f:= %d\n", f);


	//variável alocada dinâmicamente 
	printf("variável alocada dinâmicamente \n" );
	int* vect = malloc (sizeof(int) * N);

	fill(vect,N,1);
	f = find(vect,N,0);
	printf("1. f:= %d\n", f);
	f = find(vect,N,1);
	printf("0. f:= %d\n", f);
	//search out of bounds
	fill(vect,N+20,3);
	f = find(vect + N, 20, 3);
	printf("3. f:= %d\n", f);
	f = find(vect + N, 20, 1);
	printf("4. f:= %d\n", f);


	return 0;
}