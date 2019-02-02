//Ejercicio 2 Parc 2


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int *numAle()
{
	int x = rand()%11;
	int y = rand()%11;

	int *suma = (int*)malloc(sizeof(int));

	*suma = x + y;
	printf("La suma del número es: %d = %d + %d\n",*suma, x, y);
	pthread_exit((void *)suma);
}

int main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("Error en la linea de ordenes\n");
	}
	else
	{
		int i, sumTotal=0;
		pthread_t thd;
		int N = atoi(argv[1]);
		int * suma = (int*)malloc(sizeof(int)*N);

		srand(time(NULL));

		for(i=0;i<N;i++)
		{
			if(pthread_create(&thd, NULL, (void *)numAle, NULL))
			{
				fprintf(stderr, "Error en el pthread_create\n" );
				exit(EXIT_FAILURE);
			}


			if(pthread_join(thd, (void**)&suma))
			{
				fprintf(stderr, "Error en el join\n" );
				exit(EXIT_FAILURE);
			}
			sumTotal= sumTotal + *suma;
		}

		printf("La suma total es: %d \n", sumTotal);
		exit(EXIT_SUCCESS);
	}
	return 0;
}