#include <stdio.h>
#include <sys/types.h>//pid_t
#include <errno.h>//Errores
#include <stdlib.h>
#include <unistd.h> //fork()
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
	system("clear");
	pid_t pid;
	int status, childpid;
	int n, i;

	printf("Introduzca el número de hijos\n");
	scanf("%d", &n);

	for (i = 0; i < n; ++i)
	{
		pid=fork();
		if(pid==-1)
		{
			perror("Error en el fork...");
			printf("Errno value: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		else if(pid==0)
		{
			printf("Soy el hijo %d y mi padre es %d\n", getpid(),getppid());
			exit(EXIT_SUCCESS);
		}
		/*else if(pid>0)
		{

		}*/
	}
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