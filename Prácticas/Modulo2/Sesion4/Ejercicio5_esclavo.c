#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(int n)
{
	int raiz = sqrt(n);
	int isPrime = 1;
	
	for (int i = 2; i <= raiz; i++)
		if (n % i == 0)
			isPrime = 0;
	
	return isPrime;
}

int main(int argc, char *argv[]) 
{
	int inferior, superior;
	
	inferior = strtol(argv[1], NULL, 10);
	superior = strtol(argv[2], NULL, 10);
	
	if (inferior % 2 == 0)
		inferior++;
	
	for (int i = inferior; i <= superior; i += 2)
		if (isPrime(i))
			write(STDOUT_FILENO, &i, sizeof(int));

	return EXIT_SUCCESS;
}
