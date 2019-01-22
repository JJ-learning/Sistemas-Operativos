//Ejercicio 4 Practica 3

#include <pthread.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <semaphore.h>
#define N 2
sem_t con,cri,pro;


void aniadir(int id)
{
	printf("Soy el productor %d y voy a rellenar el buffer\n", id);
	sleep(rand()%5);
}

void extraer(int id)
{
	printf("Soy el consumidor %d y voy a consumir el buffer\n", id);
	sleep(rand()%5);
}



void *funcCon(int *id)
{
	while(1)
	{
		//Bloquemos los productores proque solo pasan 2
		sem_wait(&con);
		sem_wait(&cri);
		//Seccion critica
		extraer(*id);
		//Liberamos la sc
		sem_post(&cri);
		sem_post(&pro);
	}
}
void *funcPro(int *id)
{
	while(1)
	{
		//Bloquemos los productores proque solo pasan 2
		sem_wait(&pro);
		sem_wait(&cri);
		//Seccion critica
		aniadir(*id);
		//Liberamos la sc
		sem_post(&cri);
		sem_post(&con);
	}
}



int main()
{
	sem_init(&con, 0, 0);
	sem_init(&cri, 0, 1);//nombrevariable, sección crítica, nº que pueden entrar a la sc
	sem_init(&pro, 0, N);
	int v[5];
	pthread_t consumidor[5];
	pthread_t productor[5];
	int i;

	for(i =0; i<5;i++)
	{
		v[i]=i;
		pthread_create(&productor[i], NULL,(void*)funcPro, (void*)&v[i]);
		pthread_create(&consumidor[i], NULL,(void*)funcCon, (void*)&v[i]);
	}
	for(i=0;i<5;i++)
	{
		pthread_join(consumidor[i], NULL);
		pthread_join(productor[i], NULL);
	}

	sem_destroy(&con);
	sem_destroy(&cri);
	sem_destroy(&pro);
}