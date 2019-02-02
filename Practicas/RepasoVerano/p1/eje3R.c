#include <stdio.h>
#include <sys/types.h>//pid_t
#include <errno.h>//Errores
#include <stdlib.h>
#include <unistd.h> //fork()
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
	system("clear");
	pid_t hijo1, hijo2;
	int childpid, status;
	int suma=0;

	hijo1=fork();
	if(hijo1==-1)
	{
		perror("Error en el fork");
		fprintf(stderr, "Errno value: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	else if(hijo1==0)
	{
		suma=suma+(getpid()%10);
		printf("Soy el hijo1 %d y mi padre es %d, mi suma es: %d\n", getpid(), getppid(), suma);
		exit(suma);
	}
	
	hijo2=fork();
	if(hijo2==-1)
	{
		perror("Error en el fork");
		fprintf(stderr, "Errno value: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	else if(hijo2==0)
	{	
		suma=suma+(getpid()%10);
		printf("Soy el hijo2 %d y mi padre es %d, mi suma es: %d\n", getpid(), getppid(), suma);

		hijo1=fork();
		if(hijo1==-1)
		{
			perror("Error en el fork");
			fprintf(stderr, "Errno value: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		else if(hijo1==0)
		{
			suma=suma+(getpid()%10);
			printf("Soy el nieto1 %d y mi padre es %d, mi suma es: %d\n", getpid(), getppid(), suma);
			exit(suma);
		}

		hijo2=fork();
		if(hijo2==-1)
		{
			perror("Error en el fork");
			fprintf(stderr, "Errno value: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		else if(hijo2==0)
		{
			suma=suma+(getpid()%10);
			printf("Soy el nieto2 %d y mi padre es %d, mi suma es: %d\n", getpid(), getppid(), suma);
			//exit(EXIT_SUCCESS);
			exit(suma);
		}
		exit(suma);
	}
	fprintf(stderr, "La suma total es: %d\n", suma);
	while((childpid=wait(&status))!=-1)
	{
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
		exit(EXIT_SUCCESS);	
	}
	return 0;
}