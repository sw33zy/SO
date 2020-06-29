#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main()
{
    if( mkfifo("fifo", 0622) < 0) {
    	perror("mkfifo");
    } 

    return 0;
}