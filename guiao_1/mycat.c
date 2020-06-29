#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	char buffer[1024];
	ssize_t bytesRead = 0;
	while ((bytesRead = read (0, buffer, 1024))){
		write(0,buffer, bytesRead);
	}
	return 0;
}