#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	if (argc < 3) {
		perror("Wrong number of arguments");
		return 1;
	}

	int buf = 100;

	if (argc == 4) buf = atoi(argv[3]); 

	clock_t start_time = clock();

	int source = open(argv[1], O_RDONLY);
	if (source == -1) {
		perror ("ERROR: No such file or directory");
		return 1;
	}

	int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);

	char *buffer = malloc (buf);
	ssize_t bytesRead;
	
	while((bytesRead = read (source, buffer, buf)) > 0) {
		write(dest, buffer, bytesRead);
	}

	printf("Execution time: %1fs\n", (double) (clock() - start_time) / CLOCKS_PER_SEC);

	close(source);
	close(dest);
	return 0;
}