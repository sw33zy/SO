#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	int pipe_fd[2];
	if(pipe(pipe_fd) < 0){
		perror("Couldn't create pipe");
		exit(1);
	}

	if(fork() == 0){
		close(pipe_fd[0]);
		dup2(pipe_fd[1],1);
		close(pipe_fd[1]);

		execlp("ls","ls","/etc",NULL);
		_exit(1);

	}

	if (fork() == 0) {
		close(pipe_fd[1]);
		dup2(pipe_fd[0],0);
		close(pipe_fd[0]);

		execlp("wc","wc","-l",NULL);
		_exit(1);
	}

	
	close(pipe_fd[0]);
	close(pipe_fd[1]);

	wait(NULL);
	wait(NULL);
	
	return 0;
}