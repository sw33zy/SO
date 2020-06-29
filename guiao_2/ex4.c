#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	pid_t cpid, wpid;
	int i;
	int status;

	for(i=0; i<10; i++){
		
		if((cpid = fork()) == 0) {
			//child process
			printf("PID:  %d\nPPID: %d\n", getpid(), getppid());
			_exit(i);
		}
	}
	//parent process waits for all
	while((wpid = wait(&status)) != -1){
		printf("Exit code: %d\n", WEXITSTATUS(status));
	}
	
	return 0;
}
