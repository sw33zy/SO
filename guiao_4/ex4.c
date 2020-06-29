#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	int input_fd;
	int output_fd;

	if(strcmp(argv[1],"-i") == 0) {
		input_fd = open(argv[2], O_RDONLY);

	} else exit(1);

	if(strcmp(argv[3],"-o") == 0) {
		output_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	} else exit(1);

	dup2(input_fd,0);
	dup2(output_fd,1);

	close(input_fd);
	close(output_fd);

	argv[argc] = NULL;

	if(fork() == 0) {
		execvp(argv[5],argv + 5);
		_exit(1);
	}
	else wait(NULL);
	return 0;

}