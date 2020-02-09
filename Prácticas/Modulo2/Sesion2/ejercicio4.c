#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ftw.h>
#define IFXGRPOTH 011

int conpermiso = 0, tam = 0;

int regFiles(const char *pathname, const struct stat* stat, int flags, struct FTW* ftw)
{
	if(S_ISREG(stat->st_mode)) //Si es un archivo regular
	{
		printf("%s %u \n", pathname, stat->st_ino);
		if((stat->st_mode & IFXGRPOTH) == IFXGRPOTH)
		{
			conpermiso++;
			tam += stat->st_size;
		}
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	char pathname[100];
	
	printf("Los i-nodos son:\n");
	
	if(nftw(argc >= 2 ? argv[1] : ".", regFiles, 10, 0) != 0)
		perror("Error en nftw");
	
	printf("Existen %d archivos regulares con permiso x para grupo y otros\n", conpermiso);
	printf("El tamaño total ocupado por dichos archivos es %d bytes\n", tam);
	
	return 0;
}
