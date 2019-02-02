#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int childpid, status, errno, childpid2, status2;
	pid_t pid1, pid2;

	pid1=fork();
	if(pid1==-1)
	{
		perror("Error en el fork.");
		printf("Errno value=%d\n", errno);
		exit(EXIT_FAILURE);
	}
	else if(pid1==0)
	{
		printf("Soy el hijo: %d y mi padre es: %d\n", getpid(), getppid());
		if((execlp(argv[1], argv[1], NULL))==-1)
		{
			perror("Fallo en la ejecucion de execlp.");
			printf("Errno value=%d\n", errno);
			exit(EXIT_FAILURE);
		}
	}
	pid2=fork();
	if(pid2==-1)
	{
		perror("Error en el fork.");
		printf("Errno value=%d\n", errno);
		exit(EXIT_FAILURE);
	}
	else if(pid2==0)
	{
		printf("Soy el hijo %d y mi padre es :%d\n", getpid(), getppid());
		if(execvp(argv[2], &argv[2])< 0)
		{
			perror("Error en el execvp.");
			printf("Errno value:%d\n",  errno);
			exit(EXIT_FAILURE);
		}
	}

	if(pid1>0)
	{
		childpid=wait(&status);
		printf("El hijo %d ha terminado, status=%d\n",getppid(), WEXITSTATUS(status));
	}
	if(pid2>0)
	{
		childpid2=wait(&status2);
		printf("El hijo %d ha terminado, status=%d\n",getppid(), WEXITSTATUS(status2));
	}
	exit(EXIT_SUCCESS);



	return 0;
}