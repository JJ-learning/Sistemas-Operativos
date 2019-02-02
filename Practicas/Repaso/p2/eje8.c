#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5
#define MAX_ITEM 10

int buffer[N];
int contador = 0; 
pthread_mutex_t semaforo = PTHREAD_MUTEX_INITIALIZER;

void *Consumir()
{
	int numItem=0;
	int posBuffer=0;
	int cantidad;

	while(numItem<=MAX_ITEM)
	{
		pthread_mutex_lock(&semaforo);
		if(contador!=0)
		{
			cantidad=buffer[posBuffer];
			printf("Soy el consumidor y consumo de %d la cantidad %d\n",posBuffer, cantidad);
			posBuffer=(posBuffer + 1)%N;
			contador--;
			numItem++;	
		}
		pthread_mutex_unlock(&semaforo);
	}
	pthread_exit(NULL);
}

void * Producir()
{
	int numItem=0;
	int posBuffer=0;

	while(numItem<=MAX_ITEM)
	{
		pthread_mutex_lock(&semaforo);
		if(contador!=N)
		{
			buffer[posBuffer]= rand()%10;
			printf("Soy el productor y lleno en %d la cantidad: %d\n",posBuffer, buffer[posBuffer]);
			posBuffer = (posBuffer+1)%N;
			contador++;
			numItem++;
		}
		pthread_mutex_unlock(&semaforo);
	}
	pthread_exit(NULL);

}

int main()
{
	system("clear");
	int i;
	pthread_t consumidor, productor;


		if(pthread_create(&productor, NULL, (void *)Producir, NULL)!=0)
		{
			printf("Error en la llamada pthread_create\n");
			exit(EXIT_FAILURE);
		}
		if(pthread_create(&consumidor, NULL, (void *)Consumir, NULL)!=0)
		{
			printf("Error en la llamada pthread_create\n");
			exit(EXIT_FAILURE);
		}
		if(pthread_join(productor, NULL)!=0)
		{
			printf("Error en la llamada pthread_join\n");
			exit(EXIT_FAILURE);
		}
		if(pthread_join(consumidor, NULL)!=0)
		{
			printf("Error en la llamada pthread_join\n");
			exit(EXIT_FAILURE);
		}

}