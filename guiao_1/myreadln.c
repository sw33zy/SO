#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>


ssize_t readln(int fd, char* line, size_t size){
	ssize_t i=0;
	while (i < size - 1) {
		ssize_t bytes_read = read(fd, &line[i], 1);
		if (bytes_read < 1) break;
		if (line[i++] =='\n') break;
	}
	line[i] = 0;
	return i;
}

ssize_t readln2(int fd, char* line, size_t size){
	ssize_t bytes_read = read(fd, line, size);
	if (!bytes_read) return 0;

	size_t line_length = strcspn(line, "\n") + 1;
	if (bytes_read < line_length) line_length = bytes_read;
	line[line_length]=0;

	lseek(fd, line_length - bytes_read, SEEK_CUR);
	return line_length;
}

int main(int argc, char const *argv[])
{
	char line[1024];
	int file = open(argv[1], O_RDONLY);

	size_t size;

	clock_t start = clock();

	int i = 0;
	while ((size= readln2(file,line,1024))){
		char lineno[100];
		sprintf(lineno, "%*d ", 6, i++);
		write(STDOUT_FILENO, lineno, strlen(lineno));
		write(STDOUT_FILENO, line, size);
	}

	printf("\nExecution time: %1fs\n", (double) (clock() - start) / CLOCKS_PER_SEC);
	close(file);
	return 0;
}