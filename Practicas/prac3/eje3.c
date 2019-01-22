//Ejercicio 3 de la practica 3

#include <pthread.h> 
#include <stdlib.h> 
#include <stdio.h>

pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
int v[5]={1,1,1,1,1};
int indice=4;

void imprimeV()
{
	int i;
	for(i=0;i<5;i++)
	{
		printf("%d    ", v[i]);
	}
	puts("");
}

void* funcionPro()
{
	int i,s;
	//Bloqueamos el semáforo
	s=pthread_mutex_lock(&mtx);
	if(s!=0)
	{
		printf("pthread_mutex_lock error...\n");
	}
	//Sección critica
	do
	{
		if(v[indice]==0)
		{
			v[indice]=1;
			indice++;	
		}
		imprimeV();
	}while(v[4]==0);
	//DEsbloqueamos el mutex
	s=pthread_mutex_unlock(&mtx);
	if(s!=0)
	{
		printf("pthread_mutex_unlock error...\n");
	}
	return NULL;
}
void* funcionCon()
{
	int i,s;
	//Bloqueamos el semáforo
	s=pthread_mutex_lock(&mtx);
	if(s!=0)
	{
		printf("pthread_mutex_lock error...\n");
	}
	//Sección critica
	do
	{
		if(v[indice]!=0)
		{
			v[indice]=0;
			indice--;	
		}
		imprimeV();
	}while(v[0]!=0);
	//DEsbloqueamos el mutex
	s=pthread_mutex_unlock(&mtx);
	if(s!=0)
	{
		printf("pthread_mutex_unlock error...\n");
	}
	return NULL;
}





int main()
{
	pthread_t productor;
	pthread_t consumidor;

	int i, error;

	error=pthread_create(&productor, NULL, (void*)funcionPro, NULL);
	if(error!=0)
	{
		printf("Error al iniciar el pthread.\n");
	}

	error=pthread_create(&consumidor,NULL, (void*)funcionCon, NULL);
	if(error!=0)
	{
		printf("Error al iniciar el pthread.\n");
	}

	error=pthread_join(productor, NULL);
	if(error!=0)
	{
		printf("Error al iniciar el pthread.\n");
	}
	error=pthread_join(consumidor,NULL);
	if(error!=0)
	{
		printf("Error al iniciar el pthread.\n");
	}
	exit(EXIT_SUCCESS);


}