//Ejercicio 3.b de la practica 3

#include <pthread.h> 
#include <stdlib.h> 
#include <stdio.h>

pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
int v[5]={15,145,78,65,20};
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
	int i,x;
	//Bloqueamos el semáforo
	pthread_mutex_lock(&mtx);
	pthread_cond_wait(&cond, &mtx); //Suspende el proceso hasta que se active la condición

	//Sección crítica
	for(i=0;i<10;i++)
	{
		printf("Entramos en la función del productor\n");
		if(v[4]!=0)
		{
			printf("Se ha bloqueado la condición\n");
		}
		else 
		{
			x=(rand()%10)+1;
			indice++;
			v[indice]=x;
			printf("Se ha añadido correctamente\n");
		}
		imprimeV();
		printf("Salimos de la funcionPro\n");

		sleep(1);
	}
	pthread_exit(NULL);
}
void* funcionCon()
{
	int i,x,s;
	//Bloqueamos el semáforo
	pthread_mutex_lock(&mtx);
	//pthread_cond_wait(&cond, &mtx); //Suspende el proceso hasta que se active la condición

	//Sección crítica
	for(i=0;i<10;i++)
	{
		if(v[0]!=0)
		{
			v[indice]=0;
			indice--;
			printf("Elemento eliminado correctamente.\n");
			imprimeV();
			s=pthread_mutex_unlock(&mtx);
			if (s != 0)
        		printf("mutex_unlock error...\n");
        	s=pthread_cond_signal(&cond);
        	if (s != 0)
        		printf("mutex_unlock error...\n");
		}
		
		
		printf("Salimos de la funcionCon\n");
		sleep(1);
	}
	pthread_exit(NULL);
}





int main()
{
	pthread_t productor;
	pthread_t consumidor;
	srand(time(NULL));

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
	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond);
	exit(EXIT_SUCCESS);


}