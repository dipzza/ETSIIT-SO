#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	pid_t pid[5], pidfin;
	int estado, childs=5;
	
	for (int i=0; i < 5; i++)
	{
		if ((pid[i] = fork()) == -1) 
		{
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(EXIT_FAILURE);
		}
		if (pid[i] == 0)
		{
			printf("Soy el hijo %d\n", getpid());
			exit(EXIT_SUCCESS);
		}
	}
	

	for (int i=0; i<5; i+=2)
	{
		if ((pidfin = waitpid(pid[i], &estado, 0)) == -1)
		{
			perror("Error in wait");
			exit(EXIT_FAILURE);
		}
		printf("Acaba de finalizar mi hijo %d\nMe quedan %d hijos vivos\n", pid[i], --childs);
	}
	for (int i=1; i<5; i+=2)
	{
		if ((pidfin = waitpid(pid[i], &estado, 0)) == -1)
		{
			perror("Error in wait");
			exit(EXIT_FAILURE);
		}
		printf("Acaba de finalizar mi hijo %d\nMe quedan %d hijos vivos\n", pid[i], --childs);
	}
}
