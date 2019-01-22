/*Ejercicio 7 de la practica 2
Implemente un programa que cree dos hebras y cada una incremente 50 veces en un 
bucle una variable global (recuerde que la variable global, al estar en el mismo 
espacio de memoria para las dos hebras, es compartida, y que su uso es “peligroso”).
 Imprima al final del programa principal el valor de la variable (en cada ejecución
 posiblemente obtenga un valor diferente a 100 – problema de concurrencia –). 
 Intente razonar el resultado, el cual le servirá como concepto introductorio de la
siguiente práctica de la asignatura.
*/

#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>	


int global=0;
void *hiloMensaje()
{
	//int global=0;
	int i;

	for(i=0;i<1000000000;i++)
	{
		global++;
	}
	//printf("El valor de la variable antes de salir del join es: %d\n", global);
	printf("El hilo ha terminado.\n");
	pthread_exit(NULL);
}



int main()
{
	pthread_t hilo[2];
	//pthread_t hilo2;
	int i;
	
	//int aux=0;
for(i=0;i<2;i++)
{
	if(pthread_create(&hilo[i], NULL, (void *) hiloMensaje, NULL)) 
	{
	  fprintf(stderr, "Error creating thread\n");
	  exit(EXIT_FAILURE); 
	}
	if(pthread_join(hilo[i], NULL)!=0)
	{
	  fprintf(stderr, "Error joining thread\n");
	  exit(EXIT_FAILURE);  
	}
}
/*
	//printf("Al terminar el primer join el valor es: %d\n", global);
	//aux=global;
	if(pthread_create(&hilo2, NULL, (void *) hiloMensaje, (void*)&global)) 
	{
	  fprintf(stderr, "Error creating thread\n");
	  exit(EXIT_FAILURE); 
	}
	if(pthread_join(hilo2, NULL))
	{
	  fprintf(stderr, "Error joining thread\n");
	  exit(EXIT_FAILURE);  
	}
	//aux+=aux;

	//pthread_create (&hilo1, NULL, (void *) hiloMensaje, (void *) &global); 
	//pthread_create (&hilo2, NULL, (void *) hiloMensaje, (void *) &global);

	//pthread_join(hilo1, global); 
	//pthread_join(hilo2, global);
*/
	printf("El resultado de incrementar la variable es: %d \n", global);

	exit(EXIT_SUCCESS);

}