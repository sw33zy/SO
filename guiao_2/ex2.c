#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int status;

	pid_t pid = fork();

	switch(pid) {
		case(-1):
			perror("Fork failed.");
			return 1;
		case(0):
			//processo filho
			printf("---Child process---\n");
			printf("PID:  %d\nPPID: %d\n", getpid(), getppid());
			break;
		default:
			//processo pai
			wait(&status);
			printf("---Parent process---\n");
			printf("PID:  %d\nPPID: %d\nCID:  %d", getpid(), getppid(), pid);
			_exit(0);
	}
	return 0;
}