#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	for (int i = 1 ; i < 11 ; i++){
		if(fork())
			break;
		else {
			printf("Sou o %d, e sou filho do %d\n", getpid(),getppid());
		}
	}
	int pid, status;
	while((pid=wait(&status)) != -1){
		printf("Sou o %d e o %d morreu\n", getpid(),pid);
	}
	return 0;
}