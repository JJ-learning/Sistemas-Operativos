//Ejerccio 7
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

#define clave (key_t) 232

int main()
{
	int shmid, childpid, status;
	pid_t pid;
	int i, errno;
	int N;

	int *contador;

	/*Creamos zona de memoria*/
	if((shmid = shmget(clave, sizeof(int), IPC_CREAT | 0777)) == -1)
	{
		printf("Error en el shmget...\n");
		exit(EXIT_FAILURE);
	}
	/*Apuntamos a esa zona de memoria*/
	contador = (int*)shmat(shmid, NULL, 0);
	if(contador==NULL)
	{
		printf("Error en el shmat...\n");
		exit(EXIT_FAILURE);
	}

	/*Creamos los hijos pertinentes*/
	printf("Introduce el núemro de hilos que desea:\n");
	scanf("%d", &N);
	for(i=0;i<N;i++)
	{
		//Creamos el proceso
		pid=fork();
		if(pid == -1)
		{
			perror("Error en el fork");
			printf("Errno value=%d\n", errno);
			exit(EXIT_FAILURE);
		}
		else if(pid==0)
		{
			//Hacemos lo que nos pide
			*contador+=100;
			//Liberamos la memoria del contador
			if(shmdt(contador)==-1)
			{
				printf("Error en el shmdt\n");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
	}

	/*Esperamos a la finalizacion de los hijo*/
	for (i = 0; i < N; ++i)
	{
		childpid=wait(&status);
		if(childpid>0)
		{
			if (WIFEXITED(status)) {
                printf("child %d exited, status=%d\n",childpid, WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
            }
		}
		else if(childpid==-1)
		{
			printf("Error en el wait\n");
			exit(EXIT_FAILURE);
		}
	}

	//Imprimimos el valor de la variable

	printf("La variable contador vale:%d\n", *contador);

	/*liberamos memoria*/
	if(shmdt(contador)==-1)
	{
		printf("Error al liberar contador\n");
		exit(EXIT_FAILURE);
	}

	/*Destruimos la zona de memoria*/
	if(shmctl(shmid, IP_RMID, NULL)==-1)
	{
		printf("Error al destuir la memoria\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
