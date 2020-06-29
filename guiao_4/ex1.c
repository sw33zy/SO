#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int input_fd = open("/etc/passwd", O_RDONLY);
	int output_fd = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	int error_fd = open("erros.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664); 

	int stdin_fd = dup2(input_fd, 0);
	int stdout_fd = dup2(output_fd, 1);
	int sterr_fd = dup2(error_fd, 2);

	close(input_fd);
	close(output_fd);
	close(error_fd);

	char buffer[10];
	int bytes = 0;

	while((bytes = read(0, &buffer, 10)) > 0){
		write(1, &buffer, bytes);
		write(2, &buffer, bytes);
	}

	return 0;
}