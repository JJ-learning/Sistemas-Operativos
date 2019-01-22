//Ejercicio 2 de la practica 3

#include <pthread.h> 
#include <stdlib.h> 
#include <stdio.h>


pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; //GLOBAL MUTEX
void *hilo1()
{
	char aux[]="*";
	int s,i;

	for(i=0;i<5;i++)
	{

		//Bloqueamos el mutex
		s = pthread_mutex_lock(&mtx); 
	    if (s != 0)
	        printf("mutex_lock error...\n"); 
	    //Entramos a la sección crítica
	    printf("%s", aux);
	   
	    //Desbloqueamos el mutex
	    s = pthread_mutex_unlock(&mtx); 
	    if (s != 0)
	        printf("mutex_unlock error...\n");
	} 
	 sleep(2);
    return NULL;
}
void *hilo2()
{
	char aux[]="?";
	int s,i;

	for(i=0;i<5;i++)
	{
		//Bloqueamos el mutex
		s = pthread_mutex_lock(&mtx); 
	    if (s != 0)
	        printf("mutex_lock error...\n"); 
	    //Entramos a la sección crítica
	    printf("%s", aux);
	    //Desbloqueamos el mutex
	    s = pthread_mutex_unlock(&mtx); 
	    if (s != 0)
	        printf("mutex_unlock error...\n"); 

	}
	sleep(2);
    return NULL;
}
void *hilo3()
{
	char aux[]="+";
	int s,i;

	for(i=0;i<5;i++)
	{
		//Bloqueamos el mutex
		s = pthread_mutex_lock(&mtx); 
	    if (s != 0)
	        printf("mutex_lock error...\n"); 
	    //Entramos a la sección crítica
	    printf("%s", aux);
	    //Desbloqueamos el mutex
	    s = pthread_mutex_unlock(&mtx); 
	    if (s != 0)
	        printf("mutex_unlock error...\n");
	} 
	 sleep(2);
    return NULL;
}

int main(int argc, char **argv)
{
	pthread_t th1, th2, th3;
	
	int i;
	

	pthread_create(&th1, NULL, (void*)hilo1, NULL);
	pthread_create(&th2, NULL, (void*)hilo2, NULL);
	pthread_create(&th3, NULL, (void*)hilo3, NULL);
	
	
	
	pthread_join(th1, NULL);
	pthread_join(th2,NULL);
	pthread_join(th3, NULL);
	
	for(i=0;i<5;i++)
	{
		printf("-");
	}

}