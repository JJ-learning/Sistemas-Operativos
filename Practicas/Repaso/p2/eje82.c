#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5
#define MAX_ITEM 20

pthread_mutex_t sc=PTHREAD_MUTEX_INITIALIZER;
int buffer[N];
int cont=0;

void *Consumir()
{
	int pos=0;
	int numItem=0;//Para comprobar que entra dentro de los 20 elementos máximos
	int cantidad;//Cantida que tiene el buffer en la posición N


	while(numItem<=MAX_ITEM)
	{
		pthread_mutex_lock(&sc);
		if(cont!=0)
		{
			cantidad=buffer[pos];
			printf("Soy el consumidor %d y repongo %d\n", pos, cantidad);
			pos = (pos+1)%N;
			numItem++;
			cont--;
		}
		pthread_mutex_unlock(&sc);
	}

	pthread_exit(NULL);

}

void *Producir()
{
	int pos=0;
	int numItem=0;


	while(numItem<=MAX_ITEM)
	{
		pthread_mutex_lock(&sc);
		if(cont!=N)
		{
			buffer[pos]=rand()%20;
			printf("Soy el productor %d y aniado %d\n", pos, buffer[pos]);
			pos = (pos+1)%N;
			numItem++;
			cont++;
		}
		pthread_mutex_unlock(&sc);
	}

	pthread_exit(NULL);
}


int main()
{
	pthread_t productor, consumidor;

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