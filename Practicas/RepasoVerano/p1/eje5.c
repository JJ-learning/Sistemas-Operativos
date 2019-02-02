#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
	if(argc<2)
	{
		fprintf(stderr, "Usar ./a.out nºhijos\n" );
		exit(-1);	
	}
	else
	{

		pid_t pid;
		FILE *fich=fopen("aux.txt", "w");;
		int childpid, status;
		int n=atoi(argv[1]);
		
		for (int i = 0; i < n; ++i)
		{
			pid=fork();
			if(pid==-1)
			{
				perror("Error en el fork...");
				fprintf(stderr, "Errno value %d\n", errno);
				exit(EXIT_FAILURE);
			}
			if(pid==0)
			{
				fprintf(fich, "-----------------\n");
				fprintf(stderr, "Soy el hijo %d y mi padre es %d\n", getpid(), getppid());
				exit(EXIT_SUCCESS);
			}
		}
		
		
		fprintf(fich, "++++++++++++++++++\n");
		while((childpid=wait(&status))>0)
		{
			if(childpid==-1)
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
	            exit(EXIT_FAILURE);
	        }
		}
		fclose(fich);
		exit(EXIT_SUCCESS);
		return 0;
	}	
	
}