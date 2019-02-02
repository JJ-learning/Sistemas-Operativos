/* Ejercicio 6 P2
Como se comentó en la práctica 1, los procesos a diferencia de los hilos, no comparten el mismo
espacio de memoria, por lo que si queremos que accedan a las mismas variables en memoria, estos
deben compartirla. Realice un programa que expanda N procesos hijos. Cada hijo debe compartir
una variable denominada contador, que debe estar inicializada a cero. Esta variable debe ser
incrementada por cada hilo 100 veces. Imprima la variable una vez finalicen los hilos y analice el
resultado obtenido. Un resultado previsible para 3 procesos sería 300, así ha sido?
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int global=0;

void * funcion()
{
	global=global+100;
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	if (argc!=2)
	{
		printf("Error. Pruebe con-> ./a.out <nThreads>\n");
	}
	else
	{
		system("clear");
		int N=atoi(argv[1]);
		pthread_t *thd = (pthread_t*)malloc(N*sizeof(pthread_t));
		int i;

		for(i=0;i<N;i++)
		{
			if(pthread_create(&thd[i], NULL, (void *)funcion, NULL))
			{
				fprintf(stderr, "Error creating thread\n");
				exit(EXIT_FAILURE);
			}
			if(pthread_join(thd[i], NULL))
			{
				fprintf(stderr, "Error joining thread\n");
				exit(EXIT_FAILURE);				
			}
		}

		printf("Global= %d\n", global);
		exit(EXIT_SUCCESS);
	}
	return 0;
}