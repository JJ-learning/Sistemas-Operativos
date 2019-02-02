#include <stdio.h>
#include <sys/types.h>//pid_t
#include <errno.h>//Errores
#include <stdlib.h>
#include <unistd.h> //fork()
#include <sys/wait.h>

int main(int argc, char **argv)
{
	system("clear");
	pid_t hijo, hijo2;
	int childpid, status;

	hijo=fork();
	if(hijo==-1)
	{
		perror("Fork error...");
		fprintf(stderr, "Errno value:%d\n", errno);
		exit(EXIT_FAILURE);
	}
	if(hijo==0)
	{
		fprintf(stderr, "Soy el hijo %d y mi padre es %d\n", getpid(), getppid());
		if(execlp(argv[1], argv[1], NULL)==-1)
		{
			perror("execlp error...");
			fprintf(stderr, "Errno value: %d\n", errno);
			exit(EXIT_FAILURE);
		}
	}

	hijo2=fork();
	if(hijo2==-1)
	{
		perror("Fork error...");
		fprintf(stderr, "Errno value:%d\n", errno);
		exit(EXIT_FAILURE);
	}
	if(hijo2==0)
	{
		fprintf(stderr, "Soy el hijo2 %d y mi padre es %d\n", getpid(), getppid());
		if(execvp(argv[2], &argv[2])==-1)
		{
			perror("execlp error...");
			fprintf(stderr, "Errno value: %d\n", errno);
			exit(EXIT_FAILURE);
		}
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
	}
	exit(EXIT_SUCCESS);	
	return 0;
}