#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const **argv)
{
	if(argc<2)
	{
		fprintf(stderr, "Error en la línea de argumentos\n");
		fprintf(stderr, "./a.out gnome-calculator gedit fichero1.txt....\n");
		exit(-1);
	}
	else
	{
		pid_t hijo, hijo2;
		int status, childpid;

		hijo=fork();
		if(hijo==-1)
		{
			perror("Error en el fork...");
			fprintf(stderr, "Errno value=%d\n", errno);
			exit(EXIT_FAILURE);
		}
		if(hijo==0)
		{
			fprintf(stderr, "Soy el hijo %d y mi padre es %d\n", getpid(), getppid());
			if(execlp(argv[1], argv[1], NULL)==-1)
			{
				perror("Error en el execlp...");
				fprintf(stderr, "errno value:%d\n", errno);
				exit(EXIT_FAILURE);
			}
		}

		hijo2=fork();
		if(hijo2==-1)
		{
			perror("Error en el fork...");
			fprintf(stderr, "Errno value=%d\n", errno);
			exit(EXIT_FAILURE);
		}
		if(hijo2==0)
		{
			fprintf(stderr, "Soy el hijo2 %d y mi padre es %d\n", getpid(), getppid());
			if(execvp(argv[2],&argv[2])<0)
			{
				perror("Error en el execlp...");
				fprintf(stderr, "errno value:%d\n", errno);
				exit(EXIT_FAILURE);
			}
		}
		while((childpid=wait(&status))!=-1)
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
		exit(EXIT_SUCCESS);
	}
		
	return 0;
}