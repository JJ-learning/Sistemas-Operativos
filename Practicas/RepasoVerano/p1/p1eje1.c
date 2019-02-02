#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	pid_t pid1;
	int status, childpid;
	int num, i;

	printf("Introduzca el número de hijos:\n");
	scanf("%d", &num);

	for (i = 0; i < num; ++i)
	{
		pid1=fork();
		if(pid1==-1)
		{
			perror("Error en el fork");
			fprintf(stderr, "Errno value: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		else if(pid1==0)
		{
			printf("Soy el hijo con pid %d y mi padre es %d\n", getpid(), getppid());
			exit(EXIT_SUCCESS);//SI LO QUEREMOS EN FORMA DE ABANICO DEJAMOS EL exit 
		}
		/*
			SI QUEREMOS QUE SEAN SUCESIVOS, TENEMOS QUE PONER AQUÍ EL WAIT Y CON UN IF(PID>0) Y QUITAR EL exit DE PID1==0
		*/
	}
	for (int i = 0; i < num; ++i)
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
	        exit(EXIT_SUCCESS);
	}



}