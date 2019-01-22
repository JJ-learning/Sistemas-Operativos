//ejercicio 1 de la practica 2


#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <string.h>



void *hiloMensaje(char* mensa)
{
	int i;
	for(i=0;i<strlen(mensa);i++)
	{
		printf("%c\n", mensa[i]);
		sleep(1);//hacemos que 	
	}
	pthread_exit(NULL);//Finalizamos la tarea que hace el hilo
	

}


int main()
{
	pthread_t hilo1, hilo2;

	char n[]="hola";
	char m[]="mundo";

	//Creación de los hilos con la función y la variable correspondiente
	pthread_create(&hilo1, NULL, (void*)hiloMensaje, (char*)n);
	pthread_join(hilo1, NULL);

	pthread_create(&hilo2, NULL, (void*)hiloMensaje, (char*)m);
	pthread_join(hilo2, NULL);
	//Esperamos a la finalización de cada hilo
	
	

	//Finalizamos los hilos y salimos dle programa
	printf("Los hilos han finalizado.\n");
	exit(EXIT_SUCCESS);

}