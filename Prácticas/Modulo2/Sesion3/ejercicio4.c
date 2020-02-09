#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	int estado;
	
	for (int i=0; i < 5; i++)
	{
		if ((pid = fork()) == -1) 
		{
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			printf("Soy el hijo %d\n", getpid());
			break;
		}
	}
	
	if (pid != 0)
		for (int i=0; i<5; i++)
		{
			if ((pid = wait(&estado)) == -1)
			{
				perror("Error in wait");
				exit(EXIT_FAILURE);
			}
			printf("Acaba de finalizar mi hijo %d\nMe quedan %d hijos vivos\n", pid, 4 - i);
		}
}
