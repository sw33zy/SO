#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

int my_system(char* command){
	char* args[N];
	char* token;
	char* rest = command;
	size_t i = 0;

	while((token = strtok_r(rest," ",&rest)))
		args[i++] = strdup(token);
	args[i] = NULL;

	if(!fork()){
		int exec_ret = execvp(args[0],args);
		_exit(exec_ret);
	}
}

int main(int argc, char const *argv[])
{
	char buffer[N];
	int status;
	puts("Insert a command:");
	while (fgets(buffer,1024,stdin)){
		buffer[strcspn(buffer,"\n\r")] = 0;
		int ret = my_system(buffer);
		wait(&status);
		puts("Insert a command:");
		
	}
	return 0;
}