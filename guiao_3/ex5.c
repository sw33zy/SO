#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	for(int i = 0 ; i < argc ; i++){
		if(!fork()){
			execlp(argv[i],argv[i],NULL);
		}
	}
	for(size_t i = 1; i < argc; i++)
		wait(NULL);
	return 0;
}