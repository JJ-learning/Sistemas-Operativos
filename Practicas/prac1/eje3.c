//Ejercicio 3 Practica 1

#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>

int main()
{
	pid_t pid, pid2;
	int childpid, status;

	pid = fork();
	if(pid==-1)
	{
		perror("fork error");
	    printf("errno value= %d\n", errno); 
	    exit(EXIT_FAILURE);
	}
	if(pid == 0)
	{
		printf("Soy el hijo %d, y mi padre es: %d \n", getpid(), getppid());
		exit(EXIT_SUCCESS);
	}
	if(pid >0)
	{
		childpid=wait(&status);
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
		printf("Soy el hijo 2 %d y mi padre es: %d\n", getpid(), getppid());
		pid=fork();
		if(pid == -1)
		{
			perror("fork error");
	    	printf("errno value= %d\n", errno); 
	    	exit(EXIT_FAILURE);
		}
		if(pid == 0)
		{
			printf("Soy el nieto %d, y mi padre es: %d \n", getpid(), getppid());
			exit(EXIT_SUCCESS);
		}
		if(pid >0)
		{
			childpid=wait(&status);
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
			printf("Soy el nieto 2: %d, y mi padre es: %d\n", getpid(), getppid());
			pid = fork();
			if(pid== -1)
			{
				perror("fork error");
	    		printf("errno value= %d\n", errno); 
	    		exit(EXIT_FAILURE);
			}
			if(pid == 0)
			{
				printf("Soy el bisnieto %d, y mi padre es: %d \n", getpid(), getppid());
				exit(EXIT_SUCCESS);
			}
			if(pid>0)
			{
				childpid=wait(&status);
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
				printf("Soy el bisnieto2 %d, y mi padre es: %d \n", getpid(), getppid());
			}
			if(pid2>0)
			{
				childpid=wait(&status);
				exit(EXIT_SUCCESS);
			}
		}
		if(pid2 > 0)
		{
			childpid= wait(&status);
			exit(EXIT_SUCCESS);
		}
	}
	if(pid2 > 0)
	{
		childpid = wait(&status);
		exit(EXIT_SUCCESS);
	}
	
}