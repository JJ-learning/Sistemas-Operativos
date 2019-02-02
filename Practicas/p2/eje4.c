/*
Implemente un programa que cuente las líneas de los ficheros de texto que se le pasen
como parámetros y al final muestre también el número de líneas totales (contando las
de todos los ficheros juntos). Ejemplo de llamada: ./a.out fichero1 fichero2 fichero3
Debe crear un hilo por fichero obtenido por linea de argumentos, de forma que todos
los ficheros se cuenten de manera paralela.
*/
 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
 
void * hiloMensaje(void *argv)
{
  char *comandos = (char * )argv;
  //int N = atoi(argv[1]),i;
  int * contador=(int*)malloc(sizeof(int));
  *contador = 0;
  char c;
 
  FILE * fich = NULL;
  fich = fopen(comandos,"r");
  if (fich != NULL)
  {
    while((c = fgetc(fich)) != EOF){
      if(c == '\n') ++(*contador);
    }
    fclose(fich);
  }else{
      puts("Error al abrir");
  }
  pthread_exit((void*)contador);
}
 
int main(int argc, char* argv[])
{
  if(argc <= 2)
  {
    puts("Error en la linea de comandos <Ejecutable> <Nº de hebras> <Ficheros>");
  }
  else
  {
    system("clear");
    int N = atoi(argv[1]),i;
    pthread_t *thd = (pthread_t*)malloc(N*sizeof(pthread_t));
    int * contador;
    int sumaTotal;
 
    for (i = 0; i < N; i++) {
      //Creación de la hebra
      if(pthread_create(&thd[i], NULL, (void *) hiloMensaje, argv[i+2]))
      {
        fprintf(stderr, "Error creating thread\n");
        exit(EXIT_FAILURE);
      }
      //Recogiendo valores
      if(pthread_join(thd[i], (void**)&contador)!= 0)
      {
        fprintf(stderr, "Error joining thread\n");
        exit(EXIT_FAILURE);
      }
      else
      {
        sumaTotal = sumaTotal+*contador;
      }
      //Imprimiendo Valores
      printf("Fichero no. %d: %d líneas (%s)\n",i+1,*contador,argv[i+2]);
      printf("----------\n");
    }
    exit(EXIT_SUCCESS);
  }
}