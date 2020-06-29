#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	int input_fd = open("/etc/passwd", O_RDONLY);
	int output_fd = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	int error_fd = open("erros.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664); 

	int stdin_fd_backup = dup(0);
	int stdout_fd_backup = dup(1);
	int stderr_fd_backup = dup(2);


	int stdin_fd = dup2(input_fd, 0);
	int stdout_fd = dup2(output_fd, 1);
	int sterr_fd = dup2(error_fd, 2);

	close(input_fd);
	close(output_fd);
	close(error_fd);

	pid_t pid = -1;

	if((pid = fork()) == 0) {
		char buffer[10];
		int bytes = 0;

		while((bytes = read(0, &buffer, 10)) > 0){
			write(1, &buffer, bytes);
			write(2, &buffer, bytes);
		}
	}

	else{
		wait(NULL);

		dup2(stdin_fd_backup,0);
		dup2(stdout_fd_backup,1);
		dup2(stderr_fd_backup,2);

		close(stdin_fd_backup);
		close(stdout_fd_backup);
		close(stderr_fd_backup);

		char str[] = "Success.\n";
		write(1, str, strlen(str) + 1);	

	}
	return 0;
}

