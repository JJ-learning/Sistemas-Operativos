#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void * suma()
{
	int x=rand()%10;
	int y=rand()%10;
	int *aux=(int *) malloc(sizeof(int));

	*aux=x+y;
	printf("%d + %d = %d\n", x, y, *aux);
	pthread_exit((void*)aux);
}


int main(int argc, char const *argv[])
{
	if(argc!=2)
	{
		printf("Error en la línea de argumentos: ./a.out nHilos\n");
		exit(-1);
	}
	else
	{
		int n=atoi(argv[1]);
		int i;
		pthread_t thd[n];
		int sumaTotal=0;
		int *sumaDevuelta=(int*)malloc(sizeof(int)*n);
		srand(time(NULL));
		for (i=0;i<n;i++)
		{
			if(pthread_create(&thd[i], NULL, (void *)suma, NULL)==-1)
			{
				printf("Error en la llamada pthread_create\n");
				exit(EXIT_FAILURE);
			}

			if(pthread_join(thd[i], (void *)&sumaDevuelta)==-1)
			{
				printf("Error en la llamada pthread_join\n");
				exit(EXIT_FAILURE);
			}
			sumaTotal=sumaTotal+ *sumaDevuelta;
		}
		printf("La suma total es: %d\n", sumaTotal);
		exit(EXIT_SUCCESS);

	}	
	return 0;
}