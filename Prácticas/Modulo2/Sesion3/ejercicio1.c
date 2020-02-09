#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	int num;
	
	if (argc != 2)
	{
		printf("Usage: ejercicio1 <integer>\n");
		exit(EXIT_FAILURE);
	}
	num = strtol(argv[1], NULL, 10);

	printf("Mensaje previo a la ejecución de fork\n");
	if((pid = fork()) < 0) 
	{
		perror("Error en el fork\n");
		exit(EXIT_FAILURE);
	}
	if(pid == 0) 
	{  
		if(num % 2 == 0)
			printf("El número es par\n");
		else
			printf("El número es impar\n");
	}
	else
	{
		if(num % 4 == 0)
			printf("El número es divisible por 4\n");
		else
			printf("El número no es divisible por 4\n");
	}
	
	exit(EXIT_SUCCESS);
}
