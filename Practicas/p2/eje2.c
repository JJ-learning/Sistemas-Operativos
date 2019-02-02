/*
Implemente un programa que cree un número N de hebras. Cada hebra creará
2 números aleatorios (consulte la web para la generación de aleatorios) y
guardará su suma en una variable para ello, que será devuelta a la hebra
llamadora (la que invocó pthread_create()). La hebra principal ira
recogiendo los valores devueltos por las N hebras y los ira sumando en una
variable no global cuyo resultado mostrará al final por pantalla. Para ver
que los resultados finales son los que usted espera, muestre los números
que va creando cada hebra y su suma, de forma que pueda comparar esas
sumas parciales con la suma final de todos los números creados por todas
las hebras. Utilice macros definidas y comprobación de errores en sus
programas (errno y comprobación de valores devueltos en cada llamada,
con sus posibles alternativas),
será valorado en el examen final de la asignatura.
*/
 
 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
 
void * numAleatorios()
{
  int numeroaleatorio_1, numeroaleatorio_2;
  int * suma=(int*)malloc(sizeof(int));
 
  numeroaleatorio_1 = rand() % 11;
  numeroaleatorio_2 = rand() % 11;
 
  *suma = numeroaleatorio_1 + numeroaleatorio_2;
  puts("Creaccion del numero aleatorio finalizada");
  printf("La suma %d = %d + %d \n", *suma, numeroaleatorio_1, numeroaleatorio_2);
    pthread_exit((void*)suma);
}
 
int main(int argc, char **argv) {
  if(argc != 2)
  {
    puts("Error en la ejecucion del programa ./a.out <Nº de hebras>");
  }
  else
  {
    system("clear");
    pthread_t thd;
    int N = atoi(argv[1]),i;
    int * suma=(int*)malloc(sizeof(int));
    int x,y,sumaTotal = 0;
    srand (time(NULL));
 
    for (i = 0; i < N; i++) {
 
      //Creación de la hebra
      if(pthread_create(&thd, NULL, (void *) numAleatorios, NULL))
      {
        fprintf(stderr, "Error creating thread\n");
        exit(EXIT_FAILURE);
      }
 
      //Recogiendo valores
      if(pthread_join(thd, (void**)&suma)!= 0)
      {
        fprintf(stderr, "Error joining thread\n");
        exit(EXIT_FAILURE);
      }
      else
      {
        sumaTotal = sumaTotal+*suma;
      }
    }
    //Imprimiendo Valores
    printf("\nSuma total = %d.\nHan finalizado los thread.\n",sumaTotal);
    exit(EXIT_SUCCESS);
  }
}