#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

sem_t pro, sc, con;

void consumir(int id)
{
	printf("Soy el consumidor %d y voy a consumir del buffer\n", id);
}

void producir(int id)
{
	printf("Soy el productor %d y voy a rellenar el buffer\n", id);
}

void *Consumir(int *id)
{
	sem_wait(&con);
	sem_wait(&sc);

	consumir(*id);

	sem_post(&sc);
	sem_post(&pro);

	pthread_exit(NULL);

}


void *Producir(int *id)
{
	sem_wait(&pro);
	sem_wait(&sc);

	producir(*id);

	sem_post(&sc);
	sem_post(&con);

	pthread_exit(NULL);

}

int main()
{
	sem_init(&pro, 0, N);
	sem_init(&sc, 0, 1);
	sem_init(&con, 0, 0);
	pthread_t consumidor[N], productor[N];
	int i, pos;

	for(i=0;i<N;i++)
	{
		pos=i;
		if(pthread_create(&productor[i], NULL, (void *)Producir, (void *)&pos)!=0)
		{
			printf("Error en la llamada pthread_create\n");
			exit(EXIT_FAILURE);
		}
		if(pthread_create(&consumidor[i], NULL, (void *)Consumir, (void*)&pos)!=0)
		{
			printf("Error en la llamada pthread_create\n");
			exit(EXIT_FAILURE);
		}
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

}
