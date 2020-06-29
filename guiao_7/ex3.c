#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int* pids;
int pids_count = 0;
int timeout = 0;

void timeout_handler(int signum){
	for(int i = 0; i < pids_count; i++){
		printf("killing grep %d\n", pids[i]);

		if(pids[i] > 0){
			kill(pids[i],SIGKILL);
		}
	}

	timeout = 1;
}

int main(int argc, char *argv[])
{
	if(argc < 3){
		perror("Usage: multigrep <palavra> <file> ...");
		return 5;
	}

	int file_count = argc - 2;
	char** files = argv + 2;
	pids_count = file_count;
	pids = (int*) malloc(sizeof(int) * pids_count);

	for( int i = 0; i < file_count; i++){
		int pid = -1;
		if((pid = fork()) == 0){
			printf("grep #%d with pid %d for file %s\n", i, getpid(), files[i]);

			//sleep((i+1)*5);
			sleep(15);
			if(execlp("grep","grep", argv[1], files[i], NULL) < 0){
				perror("exec grep");
				exit(10);
			}
		}
		pids[i] = pid;
	}

	if(signal(SIGALRM, timeout_handler) == SIG_ERR){
		perror("timeout_handler");
		return 5;
	}
	alarm(10);

	int status = 0;
	int found = 0;
	int pid = -1;
	while(!found && (pid = wait(&status)) > 0){
		if(WIFEXITED(status)){
			switch(WEXITSTATUS(status)){
				case 0:
					//grep found word
					found = 1;
					printf("grep with pid %d found the word.\n", pid);
					break;

				case 1:
					//grep didn't find word
					printf("grep with pid %d did not find the word.\n", pid);
					break;

			}
		}
	}

	if(timeout)
		return 2;
	//alguns greps pdem estar ainda em execução
	if(!found) 
		return 1; //not found

	for(int i = 0; i < file_count; i++){
		printf("trying to kill grep with pid %d\n", pids[i]);
		
		if(pid != pids[i] && pids[i] > 0){
			kill(pids[i],SIGKILL);
			if(waitpid(pids[i], &status, 0) > 0){
				if(WIFEXITED(status)){
					printf("grep %d finished\n", pids[i]);
				} else {
					printf("grep %d was killed\n", pids[i]);
				}
			}
		}
		
	}

	free(pids);
	return 0;
}