#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct person {
	char name[100];
	int age;
} Person;

int main(int argc, char const *argv[])
{
	if (argc < 4) {
		perror("Wrong number of arguments");
		return 1;
	}

	int fd;
	Person person;

	switch(*(argv[1] + 1)){
		case 'i':
			puts("Insert mode");
			fd = open("registo.txt", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
			if(fd == -1) {
				perror ("ERROR: Couldn't open or create file / directory");
				return 1;
			}

			strcpy(person.name,argv[2]);
			person.age = atoi(argv[3]);

			if (write(fd,&person,sizeof(struct person)) < 1) {
				perror("ERROR: Couldn't write to registry file.");
				close(fd);
				return 1;
			}


			struct stat st;
			fstat(fd,&st);
			off_t file_size = st.st_size;
			int pos = (int)file_size / sizeof(struct person);

			printf("Insertion successeful - registo %d\n", pos);

			close(fd);
			break;

		case 'u':
			puts("Update mode");
			int fd = open("registo.txt", O_RDWR);
			if(fd == -1) {
				perror ("ERROR: Couldn't open  registry file");
				return 1;
			}

			int registry = -1;
			int i = 1;

			if (isdigit(*argv[2])) {
				registry = atoi(argv[2]);
			}

			while(read(fd, &person, sizeof(struct person))){
				if((registry == -1 && strcmp(person.name, argv[2])==0) || registry == i) {
					person.age = atoi(argv[3]);
					lseek(fd, - sizeof(struct person), SEEK_CUR);
					if(write(fd, &person, sizeof(struct person)) < 1){
						perror("ERROR: Couldn't write to registry file.\n");
						close(fd);
						return 1;
					}
					puts("Update successeful");
					goto UPDATE_SUC;
				}
				i++;
			}
			puts("ERROR - Registry entry not found");
			UPDATE_SUC:
			close(fd);
			break;
		default:
			puts("Invalid mode");
			break;
	}

	fd = open ("registo.txt",O_RDONLY);
	while (read(fd, &person, sizeof(struct person)) > 0){
		printf("%s - %d\n", person.name, person.age);
	}
	close(fd);
	return 0;
}
