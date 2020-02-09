#include <stdio.h>
#include <signal.h>

void handler (int signum)
{
	static int contador[31];
	
	contador[signum]++;
	printf("La señal %d se ha realizado %d veces.\n", signum, contador[signum]);
}

int main()
{
	struct sigaction sa;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);

	printf("No puedo manejar la señal %d\n", 9);
	printf("No puedo manejar la señal %d\n", 19);
	
	for (int i = 1; i <= 30; i++)
	{
		if (i != 9 && i != 19)
			if (sigaction(i, &sa, NULL) == -1)
			{
				printf("error en el manejador");
			}
	}
	
	while(1);
}
