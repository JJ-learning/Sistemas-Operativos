/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "eje2.h"

persona *
buscarapellido_1_svc(vector_personas *argp, struct svc_req *rqstp)
{
	static persona  result;
	int i;
	persona aux2;
	char aux[MAXIMO];
	fprintf(stderr, "Desde el servidor\n");
	strcpy(aux, argp->vector.vector_val[0].apellido);
	FILE *f;
	f=fopen("persona.txt", "r");
	printf("hola\n");
	while(fscanf(f, "%s, %s, %d, %s", aux2.nombre, aux2.apellido, aux2.edad, aux2.provincia)==4)
	{
		for(i=0;i<argp->vector.vector_len;i++)
		{
			if(strcmp(argp->vector.vector_val[i].apellido, aux)==0)
			{
				result=argp->vector.vector_val[i];
			}
		}
		
	}
	return &result;
}

persona *
menoredad_1_svc(vector_personas *argp, struct svc_req *rqstp)
{
	static persona  result;

	/*
	 * insert server code here
	 */

	return &result;
}
