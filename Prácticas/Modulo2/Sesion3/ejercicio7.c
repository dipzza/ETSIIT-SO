#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char **argv)
{
	int estado;
	int background = 0;
	pid_t pid;
	char **args;
	
	if (argc < 2)
	{
		printf("Usage: ejercicio7 <pathtobinary> [arg1] ... [argi] [bg]\n");
		exit(EXIT_FAILURE);
	}
	
	for (int i=0; i<argc - 1; i++)
	{
		if (strcmp(argv[i + 1], "bg") == 0)
			background = 1;
		else
			if (background)
				args[i - 1] = argv[i + 1];
			else
				args[i] = argv[i + 1];
	}
	if (background)
		args[argc - 2] = NULL;
	else
		args[argc - 1] = NULL;
	

	if ((pid = fork()) < 0)
	{
		perror("Error in fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execvp(argv[1], args) < 0)
		{
			perror("Error in execvp");
			exit(EXIT_FAILURE);
		}
	}
	
	if (!background)
	{
		wait(&estado);
		printf("Hijo finalizado con estado %d\n", estado);
	}
}
