//Ejercicio 7 de la Practica 1

#include	<signal.h>
#include	<stdio.h>
#include	<unistd.h>
#include <stdlib.h>


static void sig_alrm(int signo)
{
	printf("RIIIIIING\n");
	return;
}


unsigned int sleep1(unsigned int seg)
{
	alarm(seg); //Comienza el tiempo
	pause(); //Despierta la señal que hemos capturado
}

int main()
{
	int i=0;
	int j;
	for(j=0;j<10000000000;j++)
	{
		signal(SIGALRM, sig_alrm);
	//printf("Una alarma dentro de 5 segundos.\n");
		sleep1(5);
		i++;
		if(i == 4)
		{
			int kill(pid_t, int sig);
			exit(EXIT_SUCCESS);
		}
		else
		{
			//printf("Una alarma dentro de 3 segundos.\n");
			i++;
			sleep1(3);
			//printf("Una alarma dentro de 1 segundo.\n");
			i++;
			sleep1(1);			
		}
	
	}
	
}