/*Ejercicio3 P1*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
	pid_t hijo1, hijo2;
	int status, childpid;
	int suma=0;

	hijo1=fork();
	if(hijo1==-1)
	{
		perror("Error en el fork...");
		fprintf(stderr, "Errno value:%d\n", errno);
		exit(EXIT_FAILURE);
	}
	if(hijo1==0)
	{
		suma+=getpid()%100;
		fprintf(stderr, "Soy el hijo %d y mi padre es %d y mi suma es %d\n", getpid(), getppid(), suma);
		
	}
	if(hijo1>0)
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
	       exit(suma);
	}
	hijo2=fork();
	if(hijo2==-1)
	{
		perror("Error en el fork...");
		fprintf(stderr, "Errno value:%d\n", errno);
		exit(EXIT_FAILURE);
	}
	if(hijo2==0)
	{
		suma+=getpid()%100;
		fprintf(stderr, "Soy el hijo2 %d y mi padre es %d y mi suma es %d\n", getpid(), getppid(), suma);

		hijo1=fork();
		if(hijo1==-1)
		{
			perror("Error en el fork...");
			fprintf(stderr, "Errno value:%d\n", errno);
			exit(EXIT_FAILURE);
		}
		if(hijo1==0)
		{
			suma+=getpid()%100;
			fprintf(stderr, "Soy el nieto %d y mi padre es %d y mi suma es %d\n", getpid(), getppid(), suma);
		}
		if(hijo1>0)
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
		        exit(suma);
		}
		hijo2=fork();
		if(hijo2==-1)
		{
			perror("Error en el fork...");
			fprintf(stderr, "Errno value:%d\n", errno);
			exit(EXIT_FAILURE);
		}
		if(hijo2==0)
		{
			suma+=getpid()%100;
			fprintf(stderr, "Soy el nieto2 %d y mi padre es %d y mi suma es %d\n", getpid(), getppid(), suma);

			hijo1=fork();
			if(hijo1==-1)
			{
				perror("Error en el fork...");
				fprintf(stderr, "Errno value:%d\n", errno);
				exit(EXIT_FAILURE);
			}
			if(hijo1==0)
			{
				suma+=getpid()%100;
				fprintf(stderr, "Soy el bisnieto %d y mi padre es %d y mi suma es %d\n", getpid(), getppid(), suma);
			}
			if(hijo1>0)
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
			        exit(suma);
			}
		if(hijo2>0)
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
		        exit(suma);
		}		
	}
	if(hijo2>0)
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
	        exit(suma);
	}
}
	fprintf(stderr, "La suma total es %d\n", suma);
	return 0;
}