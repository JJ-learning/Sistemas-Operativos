//Ejercico 1b Practica 1
#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>


int main()
{
	system("clear");
	pid_t pid;
	int status, childpid;
	int n,i;

	printf("Introduzca el número de hijos:");
	scanf("%d", &n);
	for ( i = 0; i < n; ++i)
	{
		pid=fork();

		if(pid==-1)
		{
			perror("fork error");
            printf("errno value= %d\n", errno); exit(EXIT_FAILURE); 
		}
		else if (pid==0)
		{
			printf("Soy el hijo %d y mi padre es %d \n", getpid(), getppid());
			
		}
		else if(pid>0) //Para el ejercicio 1b
		{
			childpid=wait(&status); 
			puts("");
			printf("EL hijo ha terminado %d ha terminado, status=%d\n",childpid, WEXITSTATUS(status));
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
			exit(i);	
		}
		
	}
	/*
	for(i=0;i<n;i++)
		{
			childpid=wait(&status);
			//Para el control de errores
			printf("EL hijo ha terminado %d ha terminado, status=%d\n",childpid, WEXITSTATUS(status));
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
		}*/
	

}