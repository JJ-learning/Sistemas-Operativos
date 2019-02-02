#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define clave1 (key_t) 232
#define clave2 (key_t) 233

int *toten;

int main(int argc, char const *argv[])
{
	system("clear");
	int childpid, status;
	pid_t hijo;
	int i,n;
	int shmidT, shmidC;
	int *contador;

	//Creamos las zonas de memorias
	if((shmidT=shmget(clave1, sizeof(int*), IPC_CREAT|0777))==-1)
	{
		perror("shmget error...");
		fprintf(stderr, "Errno value: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	if((shmidC=shmget(clave2, sizeof(int*), IPC_CREAT|0777))==-1)
	{
		perror("shmget error...");
		fprintf(stderr, "Errno value: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	//Apuntamos a las zonas de memoria
	if((toten=(int*)shmat(shmidT, NULL,0))==NULL)
	{
		perror("shmat error...");
		fprintf(stderr, "Errno value: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	*toten=0;

	if((contador=(int*)shmat(shmidC, NULL,0))==NULL)
	{
		perror("shmat error...");
		fprintf(stderr, "Errno value: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	//Inicializamos las variables
	*contador=0;
	

	fprintf(stderr, "Introduzca el número de hijos\n" );
	scanf("%d", &n);

	for (int i = 0; i < n; ++i)
	{
		hijo=fork();
		if(hijo==-1)
		{
			perror("Error ene le fork");
			fprintf(stderr, "Errno value: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		else if(hijo==0)
		{
			if((*toten)!=i)
			{
				usleep(200);
			}
			*contador+=100;
			(*toten)++;
			//Liberamos memoria
			if(shmdt(contador)==-1)
			{
				perror("Error ene le shmdt");
				fprintf(stderr, "Errno value: %d\n", errno);
				exit(EXIT_FAILURE);
			}
			if(shmdt(toten)==-1)
			{
				perror("Error ene le shmdt");
				fprintf(stderr, "Errno value: %d\n", errno);
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
	}
	for (i = 0; i < n; ++i)
	{
		childpid=wait(&status);
		fprintf(stderr, "El hijo %d ha terminado con un statdo: %d\n", childpid, WEXITSTATUS(status));
		if (WIFEXITED(status)) 
		{
        	printf("child exited, status=%d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status)) 
		{
        	printf("child killed (signal %d)\n", WTERMSIG(status));
    	}
    	else if (WIFSTOPPED(status)) 
    	{
        	printf("child stopped (signal %d)\n", WSTOPSIG(status));
		}
		else if (WIFCONTINUED(status)) 
		{
        	printf("child continued\n");
		}
		else
		{
        	printf("Unexpected status (0x%x)\n", status);
    	}
	}

	fprintf(stderr, "LA SUMA GLOBAL ES %d\n", *contador);
	//Liberamos memoria
	if(shmdt(contador)==-1)
	{
		perror("Error ene le shmdt");
		fprintf(stderr, "Errno value: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	if(shmdt(toten)==-1)
	{
		perror("Error ene le shmdt");
		fprintf(stderr, "Errno value: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	//Destruimos la z memoria
	if((shmctl(shmidT, IPC_RMID, NULL))==-1)
	{
		perror("Error ene le shmctl");
		fprintf(stderr, "Errno value: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	if((shmctl(shmidC, IPC_RMID, NULL))==-1)
	{
		perror("Error ene le shmctl");
		fprintf(stderr, "Errno value: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
	return 0;

}