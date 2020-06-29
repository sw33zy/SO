#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	int fd;
	if ((fd = open("fifo", O_RDONLY)) < 0){
		perror("open");
		exit(1);
	}
	printf("open done\n");

	int pid = -1;
	if ((pid = fork()) == 0){
		dup2(fd,0);
		close(fd);

		execlp("cat","cat",NULL);
		_exit(1);

	}

	close(fd);

	int status = 0;
	wait(&status);
	return 0;
}