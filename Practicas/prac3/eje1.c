//Ejercicio 1 de la Practica 3

#include <pthread.h> 
#include <stdlib.h> 
#include <stdio.h>

#define NUM_CLI 3
#define NUM_PRO 5

int camisetas[NUM_PRO]={95,80,45,100,55};
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; //GLOBAL MUTEX

void *clientes(int *indice)
{
	int loc, j, s;

	int camiseta =rand()%5;
	int cant=rand()%10;

	printf("Soy el cliente %d, compro %d unidades de la camiseta %d \n", *indice, cant, camiseta);

	//Bloqueamos el mutex
	s = pthread_mutex_lock(&mtx);
	if(s!=0)
	{
		printf("mutex_lock error....\n");
	}

	//Entramos en la sección critica
	loc=camisetas[camiseta];
	loc=loc-cant;
	camisetas[camiseta]=loc;

	//Desbloqueamos el mutex
	s=pthread_mutex_unlock(&mtx);
	if(s !=0)
	{
		printf("mutex_unlock error...\n");
	}
	return NULL;
}

void *proveedores(int *indice)
{
	int loc,j,s;

	int camiseta=rand()%5;
	int cant=rand()%10;
	printf("Soy el proveedor %d, ingreso %d unidades de la camiseta %d \n",*indice, cant, camiseta);

	//Bloqueamos el mutex
	s=pthread_mutex_lock(&mtx);
	if(s!=0)
		printf("mutex_lock error...\n");

	//Entramos en la sección crítica
	loc=camisetas[camiseta];
	loc=loc+cant;
	camisetas[camiseta]=loc;

	//Desbloqueamos el mutex
	s=pthread_mutex_unlock(&mtx);
	if(s!=0)
		printf("mutex_unlock error...\n");

	return NULL;


}


int main(int argc, char **argv)
{
	//srand(time(NULL));
	pthread_t th1[NUM_CLI], th2[NUM_PRO];
	int i;
	int cant_cli=0, cant_pro=0;
	int indice_cli[NUM_CLI], indice_pro[NUM_PRO];

	for(i=0;i<NUM_PRO;i++)
	{
		printf("Antes era la camiseta[%d]=%d\n", i, camisetas[i]);
	}

	for(i=0;i<NUM_PRO+NUM_CLI;i++)
	{
		if(cant_cli<NUM_CLI)
		{
			indice_cli[i]=cant_cli;
			pthread_create(&th1[i], NULL, (void*)clientes, &indice_cli[i]);
			cant_cli++;
		}
		if(cant_pro<NUM_PRO)
		{
			indice_pro[i]=cant_pro;
			pthread_create(&th2[i], NULL, (void*)proveedores, &indice_pro[i]);
			cant_pro++;
		}
	}

	printf("Main Thread, Stopping in the join call...\n");
	for(i=0;i<NUM_CLI;i++)
        pthread_join(th1[i], NULL);
    for(i=0;i<NUM_PRO;i++)
        pthread_join(th2[i], NULL);
    
    for(i=0;i<NUM_PRO;i++)
        printf("Ahora es la camiseta[%d] = %d\n", i, camisetas[i]);
        
    exit(EXIT_SUCCESS); 
}