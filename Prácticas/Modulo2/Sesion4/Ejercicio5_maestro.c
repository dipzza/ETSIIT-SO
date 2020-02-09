#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char *argv[]) 
{	
	if (argc != 3)
	{
		printf("Usage: maestro <cotaInferior> <cotaSuperior>\n");
		exit(EXIT_FAILURE);
	}
	
	int 	fd1[2], 
			fd2[2], 
			leidos,
			numero,
			mitad = (strtol(argv[1], NULL, 10) + strtol(argv[2], NULL, 10))/2;
	pid_t 	PID;
	char 	mitadString[12];
	
	pipe(fd1);
	pipe(fd2);
	
	if ((PID = fork()) < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (PID == 0) 
	{
		close(fd1[0]);
		dup2(fd1[1], STDOUT_FILENO);
		sprintf(mitadString, "%d", mitad);
		if (execl("./esclavo","./esclavo", argv[1], mitadString, NULL) < 0)
		{
			perror("Error en execl");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		close(fd1[1]);
		while (read(fd1[0], &numero, sizeof(int)) > 0)
			printf("%d ", numero);
	}
	
	if ((PID = fork()) < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (PID == 0)
	{
		close(fd2[0]);
		dup2(fd2[1], STDOUT_FILENO);
		mitad++;
		sprintf(mitadString, "%d", mitad);
		if (execl("./esclavo","./esclavo", mitadString, argv[2], NULL) < 0)
		{
			perror("Error en execl");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		close(fd2[1]);
		while (read(fd2[0], &numero, sizeof(int)) > 0)
			printf("%d ", numero);
	}

	return EXIT_SUCCESS;
}


