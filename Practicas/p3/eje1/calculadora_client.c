/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calculadora.h"


void
calculadora_1(char *host)
{
	int i;
	int n;//Números que quiere el usuario
	CLIENT *clnt;
	int  *result_1;
	vector_cal  media_1_arg;
	int  *result_2;
	vector_cal  maximo_1_arg;
	int  *result_3;
	vector_cal  factorial_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA, CALCULADORA_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	fprintf(stderr, "Introduce la cantidad de números\n" );
	scanf("%d", &n);

	//Programa 1
	media_1_arg.vector.vector_len = n;
	media_1_arg.vector.vector_val = malloc (sizeof(int)*n);
	for(i=0;i<n;i++)
	{
		media_1_arg.vector.vector_val[i]=rand()%10;
	}

	result_1 = media_1(&media_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else
	{	
		system("clear");
		fprintf(stderr, "---Desde el cliente---\n");
		fprintf(stderr, "Media = %d\n", *result_1);
	}

	//Programa 2
	maximo_1_arg.vector.vector_len = n;
	maximo_1_arg.vector.vector_val = malloc (sizeof(int)*n);
	for(i=0;i<n;i++)
	{
		maximo_1_arg.vector.vector_val[i]=rand()%10;
	}
	
	result_2 = maximo_1(&maximo_1_arg, clnt);
	if (result_2 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else
	{
		fprintf(stderr, "Máximo = %d\n", *result_2);
	}

	//Programa 3
	factorial_1_arg.vector.vector_len = n;
	factorial_1_arg.vector.vector_val = malloc (sizeof(int)*n);
	fprintf(stderr, "Introduce el número para el que quieres calcular el factorial\n");
	scanf("%d", &factorial_1_arg.vector.vector_val[0]);	

	result_3 = factorial_1(&factorial_1_arg, clnt);
	if (result_3 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else
	{
		fprintf(stderr, "Factorial = %d\n", *result_3);
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	srand(time(NULL));
	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	calculadora_1 (host);
exit (0);
}
