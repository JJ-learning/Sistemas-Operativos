/*
Realice la multiplicación en paralelo de una matriz de 3x3 por un vector de 3x1. Para
ello cree tres hebras que se repartan las filas de la matriz y del vector. Cada hijo
debe imprimir la fila que le ha tocado y el resultado final de la multiplicación la
cual además envía al padre. El padre debe esperar por la terminación de cada hijo y
mostrar el vector resultante.
*/
 
#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <time.h>

struct param
{
  int m[3][3];
  int v[3];
  int indice;
};

void * multMatriz (struct param * p)
{
  int * resultado;
  resultado=(int *)malloc(sizeof(int));
  *resultado=0;
  int i;
  int subv[3];
  
  for (i=0;i<3;i++)
  {
    subv[i]=p->m[p->indice][i];
  }
  
  //Realizo la multiplicación
  for (i=0;i<3;i++)
  {
    *resultado=(*resultado) + subv[i]*p->v[i];
  }
  
  printf("%d\n",*resultado);
  
  pthread_exit(resultado);

}

int main()
{
  system("clear");
  pthread_t tid[3];
  int rparciales[3];
  int * aux;
  int resultado=0;
  int i,j;
  struct param p;
  
  //Relleno la matriz y el vector con números aleatorios, y los imprimo
  srand(time(NULL));
  
  printf("El vector inicial es:\n");
  for (i=0;i<3;i++)
  {
    p.v[i]=rand()%10;
    printf("%d ",p.v[i]);
  }
  printf("\n--------------------------------\n");
  printf("La matriz incial es:\n");
  for (i=0;i<3;i++)
  {
    for (j=0;j<3;j++)
    {
      p.m[i][j]=rand()%10;
      printf("%d ",p.m[i][j]);
    }
    printf("\n");
  }
  
  printf("El vector resultante:\n");
  //Ahora, divido el proceso de la multiplicación en tres hilos
  for (i=0;i<3;i++)
  {
    p.indice=i;
    pthread_create (&tid[i],NULL,(void *) multMatriz,(void *) &p);
    pthread_join (tid[i],(void **) &aux);
    rparciales[i]=*aux;
  }
    
  return 0;
}