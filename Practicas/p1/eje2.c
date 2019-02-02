//Ejercicio 2 de la Practica 1

#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>

int main()
{
	pid_t pid;
	int status, childpid;

	pid = fork();

	switch(pid)
	{
		case -1: 
			perror("Error en el fork.");
			printf("error value= %d\n", errno);
			exit(EXIT_FAILURE);
		case 0:
			printf("Soy el hijo, tengo un PID : %d y mi padre es: %d \n", getpid(), getppid());
			//Al no hacer un exit, hacemos que el padre espere al hijo quedándo éste en estado zombie
		
	}
		childpid = wait(&status);
			
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
	                printf("Error en la invocacion de wai.t o la llamada ha sido interrumpida por una señal.\n");
	                exit(EXIT_FAILURE);
	            }				
		}
		else
		{
			sleep(20);
			exit(EXIT_SUCCESS);
		}
		
}