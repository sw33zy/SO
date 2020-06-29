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

	//criar processo filho
	//herda descritores de ficheiro do processo pai
	pid_t pid = -1;
	if((pid = fork()) == 0){
		//fechar descritores que não são necessários
		close(pipe_fd[1]);

		char buf[10];
		int bytes = read(pipe_fd[0],buf, 10);
		printf("Li %d bytes: %s\n",bytes,buf);
		_exit(0);


	} else {
		close(pipe_fd[0]);

		char* str = "teste";
		//sleep(10);
		write(pipe_fd[1],str,strlen(str) + 1);

		wait(NULL);
	}
	return 0;
}