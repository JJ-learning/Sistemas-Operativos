#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	int status,childpid;
	int n,i;

	printf("Intruduzca el número de hijo que quiere:\n");
	scanf("%s", &n);
	for(i=0;i<n;i++)
	{
		pid=fork()

		if(pid==-1)
		{
			perror("fork error");
			printf("errno value: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		else if(pid==0);
		{
			printf("Soy el hijo %d y mi padre es %d\n", getpid(), getppid());
			exit(EXIT_SUCCESS);
		}
		else if(pid>0)
		{
			childpid=wait(&status);
			printf("El hijo %d ha terminado, status=%d\n", childpid, WEXITSTATUS(status));
			if (WIFEXITED(status)) 
					{
                    printf("child %d exited, status=%d\n",childpid, WEXITSTATUS(status));
               } 
					else if (WIFSIGNALED(status)) 
					{
                    printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
               } 
					else if (WIFSTOPPED(status)) 
					{
                    printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
               } 
		}
	}
	for(i=0;i<n;i++)
		{
			childpid=wait(&status);
			//Para el control de errores
			printf("EL hijo ha terminado %d ha terminado, status=%d \n",childpid, WEXITSTATUS(status));
			 if (WIFEXITED(status)) 
					{
                    printf("child %d exited, status=%d\n",childpid, WEXITSTATUS(status));
               } 
					else if (WIFSIGNALED(status)) 
					{
                    printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
               } 
					else if (WIFSTOPPED(status)) 
					{
                    printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
               } 
		}
}