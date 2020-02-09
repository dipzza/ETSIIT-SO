#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	pid_t childpid;
	int nprocs = 20, estado;

	printf("\nJerarquía tipo 2:PID:%d PPID:%d\n", getpid(), getppid());
	for (int i=1; i < nprocs; i++) 
	{
		if ((childpid = fork()) == -1) 
		{
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(-1);
		}
		if (!childpid)
		{
			printf("PID:%d PPID:%d\n", getpid(), getppid());
			break;
		}
	}
	
	wait(&estado);
}
