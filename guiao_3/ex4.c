#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv)
{	
	execv("./ex3",argv);
	return 0;
}