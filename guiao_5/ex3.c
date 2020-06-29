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

	pid_t pid = -1;
	if((pid = fork()) == 0){
		close(pipe_fd[1]);

		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);

		execlp("wc","wc",NULL);
		_exit(1);
	} else {
		close(pipe_fd[0]);

		int bytes = 0;
		char buf[10];
		while((bytes = read(0, buf, 10)) > 0){
			write(pipe_fd[1], buf, bytes);
		}
		close(pipe_fd[1]);
		wait(NULL);
	}
	return 0;
}