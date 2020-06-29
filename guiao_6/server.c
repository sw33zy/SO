#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int log_fd = -1;
	if((log_fd = open("log.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666)) < 0){
		perror("open log");
		exit(1);
	}

	printf("log open done\n");

	int fifo_fd = -1;
	int input = open("fifo2", O_WRONLY);
	while((fifo_fd = open("fifo", O_RDONLY)) > 0){
		

		printf("fifo open done\n");

		char buf[100];
		int bytes_read = 0;

		while((bytes_read = read(fifo_fd, buf, 100)) > 0 ){
			write(input,"recebido",strlen("recebido"));
			if(write(log_fd, buf, bytes_read) < 0){
				perror("write");
				exit(1);
			}
		}

		close(fifo_fd);
	}

	close(log_fd);

	return 0;
}