//Ejercicio 5 de la Práctica 2
#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>



void *hiloMensaje(void *argv)
{	
	//int n=atoi(&argv[1]);
	char *argumento=(char*)argv;
	
	int *cont=(int*)malloc(sizeof(int));
	*cont=0;
	char c;
	printf("Estoy en la funcion hiloMensaje.\n");
	FILE *fich;
		fich=fopen(argumento, "r");
		if(fich!=NULL)
		{
			while((c=fgetc(fich))!=EOF)
			{
				if(c=='\n')
				{
					(*cont)++;
					//printf("%d\n", *cont);
				}
			}
			fclose(fich);
		}	
		else
		{
			printf("Error al abrir el fichero.\n");
		}
	
	pthread_exit((void*)cont);

	

}

int main(int argc, char **argv)
{
	if(argc<=2)
	{
		printf("Error en la línea de ordenes\n");
		exit(-1);
	}
	else
	{
		int N=atoi(argv[1]);
		pthread_t *hilo=(pthread_t*)malloc(sizeof(pthread_t)*N);
		int i;
		
		int *contador;
		int suma=0;

		for(i=0;i<N;i++)
		{
			if(pthread_create(&hilo[i], NULL, (void *) hiloMensaje, argv[i+2]) )
			{
			  fprintf(stderr, "Error creating thread\n");
			  exit(EXIT_FAILURE); 
			}
			if(pthread_join(hilo[i], (void*) &contador)) 
			{
			  fprintf(stderr, "Error joining thread\n");
			  exit(EXIT_FAILURE);  
			}
			else
			{
				//printf("%d\n", *contador);
				suma=suma+*contador;
				printf("La suma total de registros es:%d\n", suma);
			}

		}
		
		exit(EXIT_SUCCESS);

		


	}

}




