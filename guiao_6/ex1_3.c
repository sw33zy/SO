#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int fd;
	if ((fd = open("fifo", O_RDONLY)) < 0){
		perror("open");
		exit(1);
	}
	printf("open done\n");

	char buf[100];
	int bytes_read = 0;

	while((bytes_read = read(fd, buf, 100)) > 0 ){
		if(write(1, buf, bytes_read) < 0){
			perror("write");
			exit(1);
		}
	}

	close(fd);
	return 0;
}