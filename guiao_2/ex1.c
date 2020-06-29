#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	printf("PID:  %d\nPPID: %d\n", getpid(), getppid());
	return 0;
}