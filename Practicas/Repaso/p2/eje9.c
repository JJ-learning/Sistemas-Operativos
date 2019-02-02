#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define N 3

sem_t con, sc, pro;

void producir(int id)
{
	printf("Soy el productor %d y lleno el buffer\n", id);
	sleep(rand()%5);
	
}

void consumir(int id)
{
	printf("Soy el consumidor %d y consumo del buffer\n", id);
	sleep(rand()%5);
}

void *Producir(int *id)
{
	while(1)
	{
		sem_wait(&pro);
		sem_wait(&sc);

		producir(*id);

		sem_post(&sc);
		sem_post(&con);
	}

}

void *Consumir(int *id)
{
	while(1)
	{
		sem_wait(&con);
		sem_wait(&sc);

		consumir(*id);

		sem_post(&sc);
		sem_post(&pro);
	}
	pthread_exit(NULL);
}

int main()
{
	int i, id[N];

	sem_init(&con, 0, 0);
	sem_init(&sc, 0, 1);
	sem_init(&pro, 0, N);
	pthread_t productor[N], consumidor[N];

	for(i=0;i<N;i++)
	{
		id[i]=i;
		if(pthread_create(&consumidor[i], NULL, (void *)Consumir, (void*)&id[i])!=0)
		{
			printf("Error en la llamada pthread_create\n");
			exit(EXIT_FAILURE);
		}
		if(pthread_create(&productor[i], NULL, (void *)Producir, (void*)&id[i])!=0)
		{
			printf("Error en la llamada pthread_create\n");
			exit(EXIT_FAILURE);
		}
	}
	for(i = 0; i < N; ++i)
	{
		if(pthread_join(productor[i], NULL)!=0)
		{
			printf("Error en la llamada pthread_join\n");
			exit(EXIT_FAILURE);
		}
		if(pthread_join(consumidor[i], NULL)!=0)
		{
			printf("Error en la llamada pthread_join\n");
			exit(EXIT_FAILURE);
		}
	}

	sem_destroy(&con);
	sem_destroy(&sc);
	sem_destroy(&pro);

}
