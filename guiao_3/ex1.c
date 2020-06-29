#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	execlp("ls","-l",NULL);
	printf("Test\n");
	return 0;
}