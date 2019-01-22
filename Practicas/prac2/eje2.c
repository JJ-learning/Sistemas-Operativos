//ejercicio 2 de la practica 2

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>


void *numAle()
{
	int num1,num2;
	int *suma=(int*)malloc(sizeof(int));
	num1=rand()%10+1;
	num2=rand()%10+1;

	*suma=num1+num2;

	printf("%d + %d = %d \n", num1, num2, *suma);
	pthread_exit((void*)suma);
}



int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("Error en la línea de argumentos\n");
		exit(-1);
	}
	else
	{
		int n=atoi(argv[1]);
		int *suma=(int*)malloc(sizeof(int));
		int i, sumaTotal=0;
		pthread_t hilo;
		srand(time(NULL));

		for(i=0;i<n;i++)
		{
			pthread_create(&hilo, NULL, (void*)numAle, NULL);
			pthread_join(hilo, (void**)&suma);
			sumaTotal+=*suma;
		}
		printf("La suma total es: %d\n", sumaTotal);
		exit(EXIT_SUCCESS);

	}
}