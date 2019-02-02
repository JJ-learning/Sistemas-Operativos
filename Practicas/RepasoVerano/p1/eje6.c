#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**********************************************************************/
// LA SOLUCION DEBE DE DAR 0 YA QUE LOS PROCESOS NO COMPARTEN MEMORIA //
/**********************************************************************/
int global=0;

int main(int argc, char const *argv[])
{
	system("clear");
	pid_t hijo;
	int childpid, status;
	int n, i;

	fprintf(stderr, "Introduzca el número de hijos\n");
	scanf("%d", &n);

	for(i=0; i<n;i++)
	{
		hijo=fork();
		if(hijo==-1)
		{
			perror("Fork error...");
			fprintf(stderr, "Errno value: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		if(hijo==0)
		{
			global++;
			fprintf(stderr, "SOy el hijo %d y mi padre es %d\n", getpid(), getppid());
			exit(global);
		}
	}
	for (i = 0; i < n; ++i)
	{
		childpid=wait(&status);
		fprintf(stderr, "La variable global es %d\n", global);
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
	
	exit(EXIT_SUCCESS);	
	return 0;
}