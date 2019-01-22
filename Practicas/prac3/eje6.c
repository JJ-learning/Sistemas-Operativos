//Ejericio 6 de la practica 3

#include <pthread.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <semaphore.h>

#define N 5
#define IZQ(X) (((X)-1)%N)
#define DER(X) (((X)+1)%N)

sem_t cri;
sem_t vsem[N];
int estado[N]={0,0,0,0,0};
	/*
		0. Pensando
		1. Hambriemto(Coge el tenedor)
		2. Comiendo
	*/

void pensar(int id)
{
	printf("Soy el fiĺosofo %d y estoy to rayao pensando fumandome un petaajajajaj\n", id);
	sleep(rand()%4);
}
void comer(int id)
{
	printf("Soy el filósofo %d y estoy hinchadome a comer ahí a jierros.\n", id);
	sleep(rand()%4);
}
void prueba(int id)
{
	if(estado[id]==1 && estado[IZQ(id)]!=2 && estado[DER(id)]!=2)
	{
		estado[id]=2;
		sem_post(&vsem[id]);
	}
}

void cogerTenedores(int id)
{
	//Bloqueamos sc
	sem_wait(&cri);

	estado[id]=1;
	prueba(id);
	sem_post(&cri);

	sem_wait(&vsem[id]);//El filosofo deja de comer
}

void dejarTenedor(int id)
{
	//Bloqueamos la sección critica
	sem_wait(&cri);

	estado[id]=0;
	prueba(IZQ(id));
	prueba(DER(id));

	sem_post(&cri);
}

void *filosofos(int *id)
{
	while(1)
	{
		pensar(*id);
		cogerTenedores(*id);
		comer(*id);
		dejarTenedor(*id);


	}
	pthread_exit(NULL);
}


int main()
{
	pthread_t th[N];
	int i, v[N];
	sem_init(&cri, 0,1);

	for(i=0;i<N;i++)
	{
		sem_init(&vsem[i], 0, 0);
	}

	for(i=0;i<N;i++)
	{
		v[i]=i;
		pthread_create(&th[i], NULL, (void*)filosofos, (void*)&v[i]);
	}
	for(i=0;i<N;i++)
	{
		pthread_join(th[i], NULL);
	}

	sem_destroy(&cri);
	for(i=0;i<N;i++)
	{
		sem_destroy(&vsem[i]);
	}
}

