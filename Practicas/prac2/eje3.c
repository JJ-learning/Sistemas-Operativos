//Ejercicio 3 de la práctica 2
#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <unistd.h>
#include <time.h>

typedef struct param
{
	int partes;
	int v[10];
	int indice;

}PARAM;



void *hiloMensaje(void * param)
{
	int i;
	PARAM *parametro=(void*)param;//hacemos un casting para poder utilizar la variable
	int *suma=(int*)malloc(sizeof(int));

	printf("Los número del vector según las partes es:\n");
	for(i=0;i<(parametro->partes + parametro->indice);i++)
	{
		*suma=*suma + parametro->v[parametro->indice];
		printf("%d ", parametro->v[parametro->indice]);
	}
	puts("");
	pthread_exit((void*)suma);
}

int main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("Error en la línea de órdenes\n");
		exit(-1);
	}
	else
	{
		PARAM parametro;
		int N=atoi(argv[1]);//Numero de hilos
		pthread_t *hilo=(pthread_t*)malloc(sizeof(pthread_t)*N);
		srand(time(NULL));
		int i;
		int suma=0;
		int *sumareal=(int*)malloc(sizeof(int));
		int total=0;

		printf("El vector de la estructura es:\n");

		parametro.partes=10/N;//numero de elementos a pasar al hilo
		parametro.indice=0;

		for(i=0;i<10;i++)
		{
			parametro.v[i]=rand()%10;
			printf("%d ", parametro.v[i]);
			suma=suma+parametro.v[i];
		}
		puts("");
		printf("La suma total del vector es: %d\n", suma);

		for(i=0;i<N;i++)
		{
			pthread_create(&hilo[i], NULL, (void*)hiloMensaje, (void*)&parametro);

			if(pthread_join(hilo[i], (void**)&suma)!=0)//Comprobación de errores
			{
				printf("Error en el join.\n");
				exit(EXIT_FAILURE);
			}
			else
			{	
				total=total+*sumareal;
				printf("%d ", *sumareal);
			}
		}
		puts("");

		printf("La suma total del vector es:%d\n", total);
		exit(EXIT_SUCCESS);

		
	}
	
}
