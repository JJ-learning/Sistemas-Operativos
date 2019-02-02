//Ejercicio 3 Practica 1

#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>
#include <sys/wait.h>

int main()
{
	system("clear");
	pid_t pid, pid2;
	int childpid, status;
	int suma=0;

	pid = fork();
	if(pid==-1)
	{
		perror("fork error");
	    printf("errno value= %d\n", errno); 
	    exit(EXIT_FAILURE);
	}
	if(pid == 0)
	{
		suma+=getpid()%10;
		printf("Soy el hijo %d, y mi padre es: %d y mi suma es %d \n", getpid(), getppid(), suma);
		exit(suma);
	}
	if(pid >0)
	{
		childpid=wait(&status);
		//Control  de errores
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
	}

	pid2 = fork();
	if(pid2 == -1)
	{
		perror("fork error");
	    printf("errno value= %d\n", errno); 
	    exit(EXIT_FAILURE);
	}
	if(pid2 == 0)
	{
		suma+=getpid()%10;
		printf("Soy el hijo 2 %d y mi padre es: %d y mi suma es: %d\n", getpid(), getppid(), suma);
		pid=fork();
		if(pid == -1)
		{
			perror("fork error");
	    	printf("errno value= %d\n", errno); 
	    	exit(EXIT_FAILURE);
		}
		if(pid == 0)
		{	
			suma+=getpid()%10;
			printf("Soy el nieto %d, y mi padre es: %d y mi suma es:%d\n", getpid(), getppid(), suma);
			exit(suma);
		}
		if(pid >0)
		{
			childpid=wait(&status);
			//Control de errores
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
		}
		pid2 =fork();
		if(pid2 == -1)
		{
			perror("fork error");
	    	printf("errno value= %d\n", errno); 
	    	exit(EXIT_FAILURE);
		}
		if(pid2 == 0)
		{
			suma+=getpid()%10;
			printf("Soy el nieto 2: %d, y mi padre es: %d y mi suma es: %d\n", getpid(), getppid(), suma);
			pid = fork();
			if(pid== -1)
			{
				perror("fork error");
	    		printf("errno value= %d\n", errno); 
	    		exit(EXIT_FAILURE);
			}
			if(pid == 0)
			{
				suma+=getpid()%10;
				printf("Soy el bisnieto %d, y mi padre es: %d y mi suma es: %d\n", getpid(), getppid(), suma);
				exit(suma);
			}
			if(pid>0)
			{
				childpid=wait(&status);
							//Control de errores
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
			}
		}
		if(pid2 > 0)
		{
			childpid= wait(&status);
						//Control de errores
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
			exit(suma);
		}
	}
	if(pid2 > 0)
	{
		childpid = wait(&status);
					//Control de errores
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
		exit(suma);
	}
	
}

