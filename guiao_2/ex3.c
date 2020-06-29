#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	int i;
	int status;

	for(i=0; i<10; i++){
		pid = fork();
		if(!pid) {
			//child process
			printf("PID:  %d\nPPID: %d\n", getpid(), getppid());
			_exit(i);
		}
		else {
			//parent process
			pid = wait(&status);
			printf("Child %d finished! Exit code: %d\n", pid, WEXITSTATUS(status));
		}
	}
	return 0;
}