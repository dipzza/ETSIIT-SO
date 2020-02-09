#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Uso: ejercicio2 <pathname> <permisos>\n");
		exit(EXIT_FAILURE);
	}
	
	
	DIR *path;
	
	if( (path = opendir(argv[1])) == NULL)
	{
		perror("Error en opendir");
		exit(EXIT_FAILURE);
	}
	
	struct dirent *archivo;
	struct stat atributos;
	char pathArchivo[50];
	int permisos = strtol(argv[2], NULL, 8);
	
	while( (archivo = readdir(path)) != NULL)
	{
		sprintf(pathArchivo, "%s/%s", argv[1], archivo->d_name);
		
		if(stat(pathArchivo, &atributos) < 0)
		{
			perror("Error en stat");
			exit(EXIT_FAILURE);
		}
		
		if(S_ISREG(atributos.st_mode)) //Si es un archivo regular
		{
			printf("%s : %o ", archivo->d_name, atributos.st_mode);
			
			if (chmod(pathArchivo, permisos) < 0)
				printf("%s : %d %o\n", archivo->d_name, errno, atributos.st_mode);
			else
				stat(pathArchivo, &atributos);
			
			printf("%o\n", atributos.st_mode);
		}
	}
	
	if((closedir(path)) < 0)
	{
		perror("Error en closedir");
		exit(EXIT_FAILURE);
	}
}
