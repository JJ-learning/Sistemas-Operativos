#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char **argv)
{
	if argc <= 2
	{
		printf("Error en la linea de comandos\n");
		exit(-1);
	}
	else
	{
		int n=atoi(argv[1]);//Numero de hebras
			
	}

	return 0;
}