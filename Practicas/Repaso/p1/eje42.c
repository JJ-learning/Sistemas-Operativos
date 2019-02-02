#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	int i, childpid, errno, status;
	pid_t pid1, pid2;

	pid1=fork();
	if(pid1==-1)
	{
		perror("Error en el fork");
		printf("Errno value: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	else if(pid1==0)
	{
		printf("Soy el hijo %d y mi padre es: %d \n", getpid(), getppid());
		if((execlp(argv[1], argv[1], NULL))==-1)
		{
			printf("Error en la llamada execlp, errno value:%d\n", errno);
			exit(EXIT_FAILURE);
		}
	}

	pid2=fork();
	if(pid2==-1)
	{
		perror("Error en el fork...");
		printf("Errno value:%d\n", errno);
	}
	else if(pid2==0)
	{
		printf("Soy el hijo %d y mi padre es: %d \n", getpid(), getppid());
		if((execvp(argv[2], &argv[2]))==-1)
		{
			printf("Error en la llamada execvp, errno value: %d\n", errno);
			exit(EXIT_FAILURE);
		}
	}


	if(pid1>0)
	{
		childpid=wait(&status);
		if(childpid==0)
		{
			if(WIFEXITED(status))
			{
				printf("Hijo %d acaba de terminar. Valor:%d\n", getpid(), WEXITSTATUS(status));
			}
			if(WIFSIGNALED(status))
			{
				printf("Hijo %d muerto, Valor: %d \n", getpid(), WTERMSIG(status));
			}
			if(WIFSTOPPED(status))
			{
				printf("Hijo %d parado, Valor: %d\n", getpid(), WSTOPSIG(status));
			}
		}
	}
	if(pid2>0)
	{
		childpid=wait(&status);
		if(childpid>0)
		{
			if(WIFEXITED(status))
			{
				printf("Proceso %d acaba de terminar. Valor:%d\n", getpid(), WEXITSTATUS(status));
			}
			if(WIFSIGNALED(status))
			{
				printf("Proceso %d muerto, Valor: %d \n", getpid(), WTERMSIG(status));
			}
			if(WIFSTOPPED(status))
			{
				printf("Proceso %d parado, Valor: %d\n", getpid(), WSTOPSIG(status));
			}
		}
	}
	exit(EXIT_SUCCESS);
}