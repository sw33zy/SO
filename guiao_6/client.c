#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv)
{
    int output = open("fifo2", O_RDONLY);
    int server = open("fifo", O_WRONLY);
    if (server < 0) {
        printf("Server offline\n");
        return 1;
    }
    char str1[100] , str2[] = " ";
    for (int i = 0; i < argc; i++){
    	strcpy(str1,argv[i]);
    	strcat(str1,str2);
        write(server, str1, strlen(str1));
    }
    write(server, "\n", 4);

    char buf[100];
    int bytes_read = 0;
    
    if((bytes_read = read(output, buf, 100)) > 0 ){
        if(write(1, buf, bytes_read) < 0){
                perror("write");
                exit(1);
            }
    }
    close(server);
    close(output);
    return 0;
}