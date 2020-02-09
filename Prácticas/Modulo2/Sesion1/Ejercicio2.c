#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc, char *argv[])
{
int fdr,fdw;
char buf1[80];
char salto_linea[2]="\n";
char bloque[10];
char nbloques[28];
char caracter[3];


if (argc==2){
    if((fdr=open(argv[1], O_RDONLY)) < 0) {
        printf("\nError %d en open de lectura",errno);
        perror("\nError en open");
        exit(EXIT_FAILURE);
    }
}
else
    fdr=STDIN_FILENO;

if((fdw=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0){
        printf("\nError %d en open de escritura",errno);
        perror("\nError en open");
        exit(EXIT_FAILURE);
}

if (lseek(fdw, 28, SEEK_SET) == -1){
    perror("\nError en lseek");
    exit(EXIT_FAILURE);
}

int i=0, nleidos;

while ((nleidos=read(fdr,buf1,80)) != 0){
    if (nleidos == -1){
        printf("\nError %d en read",errno);
        perror("\Error en read");
        exit(EXIT_FAILURE);
    }
    else{
        sprintf(bloque,"Bloque %d\n", i);
        if(write(fdw, bloque,strlen(bloque)) != strlen(bloque)){
            perror("\nError en write1");
            exit(EXIT_FAILURE);
        }
        
        if(write(fdw,buf1,nleidos) != nleidos){
            perror("\nError en write4");
            exit(EXIT_FAILURE);
        }
        if(write(fdw, salto_linea,1) != 1){
            perror("\nError en write5");
            exit(EXIT_FAILURE);
        }
    }
    i++;
}

if (lseek(fdw, 0, SEEK_SET) == -1){
    perror("\nError en lseek");
    exit(EXIT_FAILURE);
}

sprintf(nbloques, "El numero de bloques es %d\n", i);
if(write(fdw, nbloques, strlen(nbloques)) != strlen(nbloques)){
    perror("\nError en write6");
    exit(EXIT_FAILURE);
}

close(fdr);
close(fdw);

return EXIT_SUCCESS;
}
