//Ejercicio 1 Practica 1.

#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>

int main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("Error en la línea de argumentos\n");
		exit(-1);
	}
	else
	{
		int childpid, status;
		int i;
		pid_t pid;
		int N=atoi(argv[1]);
		for(i=0;i<N;++i)
		{
			pid=fork();
			if(pid==-1)
			{
				perror("fork error");
				printf("errno value=%d\n", errno);
				exit(EXIT_FAILURE);
			}
			else if(pid==0)
			{
				printf("Soy el hijo: %d y mi padre es: %d\n", getpid(), getppid());
				//exit(0);
			}
		
		//for(i=0;i<N;++i)
		//{
			childpid=wait(&status); 
            if(childpid>0)
            {
            	if(childpid>0)
	            {
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
	            else 
				{
	                printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
	                exit(EXIT_FAILURE);
	            }	
	             exit(i);	
            }  	
           
		}
		printf("Los procesos han finalizado.\n");
		exit(EXIT_SUCCESS);

	}

}