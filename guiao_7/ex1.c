#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

typedef void (*sighandler_t)(int);

int ctrc_c_counter;
int time;

void sigint_handler( int signum){
	printf("Time elapsed: %d\n", time);
	ctrc_c_counter++;
}

void sigquit_handler(int signum){
	printf("Ctrl + C - %d times.\n", ctrc_c_counter);
	exit(1);
}

void sigalarm_handler(int signum){
	alarm(1);
	time++;
}


int main(int argc, char const *argv[])
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR){
		perror("signal sigint");
		exit(1);
	}

	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR){
		perror("signal sigquit");
		exit(1);
	}

	if (signal(SIGALRM, sigalarm_handler) == SIG_ERR){
		perror("signal sigalarm");
		exit(1);
	}

	alarm(1);

    while (1) {
        pause();
        printf("another second\n");
    }

	return 0;
}

