#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>

//Definimos una clave
#define clave (key_t) 233

int main()
{
	pid_t pid1, pid2;
	int i, shmid, status, childpid;
	int *contador;

	if((shmid = shmget(clave, sizeof(int), IPC_CREAT | 0777))==-1)
	{
		printf("Error en la llamada shmget\n");
		exit(EXIT_FAILURE);
	}

	//Obtenemos un puntero a la zona de memoria
	contador=(int*)shmat(shmid, NULL, 0);
	if(contador==NULL)
	{
		printf("Error en la llamada shmat\n");
		exit(EXIT_FAILURE);
	}
	*contador=0;

	pid1=fork();
	if(pid1==-1)
	{
		perror("Error en el fork");
		printf("Errno value:%d\n", errno);
		exit(EXIT_FAILURE);
	}
	else if(pid1==0)
	{
		*contador+=100;
		pid2=fork();
		if(pid2==-1)
		{
			perror("Error en el fork");
			printf("Errno value:%d\n", errno);
			exit(EXIT_FAILURE);
		}
		else if(pid2==0)
		{
			*contador+=100;
			if(shmdt(contador)==-1)
			{
				printf("Error en la llamada shmdt\n");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		if(pid2>0)
		{
			childpid=wait(&status);
		}
		if(shmdt(contador)==-1)
		{
			printf("Error en la llamada shmdt\n");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	if(pid1>0)
	{
		childpid=wait(&status);
	}

	pid2=fork();
	if(pid2==-1)
	{
		perror("Error en el fork");
		printf("Errno value:%d\n", errno);
		exit(EXIT_FAILURE);
	}
	else if(pid2==0)
	{
		*contador+=100;

		if(shmdt(contador)==-1)
		{
			printf("Error en la llamada shmdt\n");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	if(pid2>0)
	{
		childpid=wait(&status);
	}

	printf("La variable contador vale=%d\n", *contador);

	//Liberamos memoria
	if(shmdt(contador)==-1)
	{
		printf("Error en la llamada shmdt\n");
		exit(EXIT_FAILURE);
	}
	if(shmctl(shmid, IPC_RMID, NULL)==-1)
	{
		printf("Error en la llamada shmctl\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}