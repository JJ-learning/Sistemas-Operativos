#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define clave (key_t) 232
//VARIABLES GLOBALES


int main(int argc, char const *argv[])
{
	if(argc<1)
	{
		fprintf(stderr, "Error en la línea de argumentos\n" );
		exit(-1);
	}
	else
	{		

		int nprocesos;
		pid_t pid;
		int childpid, status;

		int shmid;
		int *contador;
		
		fprintf(stderr, "Indruzca el número de procesos:\n" );
		scanf("%s", &nprocesos);
		//CREAMOS LA ZONA DE MEMORIA
		if((shmid=shmget(clave, sizeof(int), IPC_CREAT |0777))==-1)
		{
			fprintf(stderr, "Error en el shmget\n");
			exit(-1);
		}
		if((contador=(int *)shmat(shmid, NULL, 0))==(int *)-1)
		{
			fprintf(stderr, "Error en el shmat\n" );
			exit(-1);
		}
		*contador=0;

		for (int i = 0; i < nprocesos; ++i)
		{
			pid=fork();
			if(pid==-1)
			{
				perror("Error en el fork");
				fprintf(stderr, "Error en el fork. Errno value: %d\n", errno);
				exit(EXIT_FAILURE);
			}
			if(pid==0)
			{
				*contador+=100;
				fprintf(stderr, "Soy el hijo %d y mi padre es %d.\n", getpid(), getppid());
				fprintf(stderr, "Mi suma total es: %d\n", *contador);
				
				if(shmdt(contador)==-1)
				{
					fprintf(stderr, "Error en el shmdt\n" );
					exit(-1);
				}
				exit(EXIT_SUCCESS);
			}
		}
		for (int i = 0; i < nprocesos; ++i)
		{
			childpid=wait(&status);
			if (childpid == -1)
			{
            	perror("waitpid");
            	exit(EXIT_FAILURE);
        	}
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
		//LIBERAMOS MEMORIA
		if(shmdt(contador)==-1)
		{
			fprintf(stderr, "Error en el shmdt\n" );
			exit(-1);
		}
		//DESTRUIMOS LA MEMORIA
		if(shmctl(shmid, IPC_RMID, NULL)==-1)
		{
			fprintf(stderr, "Error en el shmat\n" );
			exit(-1);
		}
		exit(EXIT_SUCCESS);
	}
	return 0;
}