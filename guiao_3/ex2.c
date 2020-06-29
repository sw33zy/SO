#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	int status;
	if(!fork()){
		execlp("ls","ls","-l",NULL);
		_exit(0);
	}
	else{
		wait(&status);
		if(WIFEXITED(status))
			puts("Success");
		else 
			puts("Child error");
	}

	return 0;
}