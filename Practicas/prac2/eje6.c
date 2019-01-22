//Ejercicio 6 d el práctica 2
#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>	

typedef struct elem
{
	int m_[3][3];
	int v_[3];
	
}ELEM;


void *hiloMensaje(void *elemento)
{
	ELEM *ele=(ELEM*)elemento;
	int i,j;
	int *aux=(int*)malloc(sizeof(int));

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			*aux=*aux+(ele[i].v_[i] * ele[i].m_[i][j]);
		}
	}
	printf("%d ", *aux);
	pthread_exit((void*)aux);
}

int main()
{
	
	ELEM *elemento=(ELEM*)malloc(sizeof(ELEM)*3);
	pthread_t *hilo=(pthread_t*)malloc(sizeof(pthread_t)*3);
	int i,j;
	int v[3]={1,2,3};
	int m[3][3]={{1,1,1},{1,1,1},{1,1,1}};

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			elemento[i].v_[j]=v[j];
		}
			
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			elemento[i].m_[i][j]=m[i][j];
		}
			
	}
	

	for(i=0;i<3;i++)
	{
		if(pthread_create(&hilo[i], NULL, (void *) hiloMensaje, (void*)&elemento)) 
		{
		  fprintf(stderr, "Error creating thread\n");
		  exit(EXIT_FAILURE); 
		}
		if(pthread_join(hilo[i], (void*)&elemento)) 
		{
		  fprintf(stderr, "Error joining thread\n");
		  exit(EXIT_FAILURE);  
		}
		else
		{
			printf("%d ", *elemento);
		}
	}

}
