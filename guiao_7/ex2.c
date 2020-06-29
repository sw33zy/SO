#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	if(argc < 3){
		perror("Usage: multigrep <palavra> <file> ...");
		return 5;
	}

	int file_count = argc - 2;
	char** files = argv + 2;
	int pids[file_count];

	for( int i = 0; i < file_count; i++){
		int pid = -1;
		if((pid = fork()) == 0){
			printf("grep #%d with pid %d for file %s\n", i, getpid(), files[i]);

			//	sleep((i+1)*5);
			if(execlp("grep","grep", argv[1], files[i], NULL) < 0){
				perror("exec grep");
				exit(10);
			}
		}
		pids[i] = pid;
	}

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


	return 0;
}