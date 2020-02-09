#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#define IFXGRPOTH 011

void regFiles(char *pathname, int *conpermiso, int *tam)
{
	DIR *directorio;
	struct dirent *archivo;
	struct stat atributos;
	char pathArchivo[100];
	
	if( (directorio = opendir(pathname)) == NULL)
	{
		perror("Error en opendir");
		exit(EXIT_FAILURE);
	}
	
	while( (archivo = readdir(directorio)) != NULL)
	{
		sprintf(pathArchivo, "%s/%s", pathname, archivo->d_name);
		
		if(stat(pathArchivo, &atributos) < 0)
		{
			perror("Error en stat");
			exit(EXIT_FAILURE);
		}
		
		if(S_ISREG(atributos.st_mode)) //Si es un archivo regular
		{
			printf("%s %u \n", pathArchivo, atributos.st_ino);
			if((atributos.st_mode & IFXGRPOTH) == IFXGRPOTH)
			{
				(*conpermiso)++;
				(*tam) += atributos.st_size;
			}
		}
		
		if(S_ISDIR(atributos.st_mode) && strcmp(archivo->d_name, ".") != 0 && strcmp(archivo->d_name, "..") != 0)
			regFiles(pathArchivo, conpermiso, tam);
	}
	
	if((closedir(directorio)) < 0)
	{
		perror("Error en closedir");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	char pathname[100];
	
	if (argc == 2)
		strcpy(pathname, argv[1]);
	else if (argc == 1)
		strcpy(pathname, ".");
	else
	{
		printf("Uso: ejercicio3 [pathname]\n");
		exit(EXIT_FAILURE);
	}
	
	int conpermiso = 0, tam = 0;
	
	printf("Los i-nodos son:\n");
	
	regFiles(pathname, &conpermiso, &tam);
	
	printf("Existen %d archivos regulares con permiso x para grupo y otros\n", conpermiso);
	printf("El tamaño total ocupado por dichos archivos es %d bytes\n", tam);
	
	return 0;
}
