/*Implemente un programa que a partir de un fichero de texto, realice concurrentemente tantas copias
del mismo como se indique. El programa recibirá por la linea de argumentos dos parámetros, el
nombre del fichero y el número de copias a realizar. El nombre de los ficheros de salida será el
mismo que el del fichero original seguido por un número de copia, por ejemplo: “fichero0”,
“fichero1”, “fichero2” en el caso de que haya que hacer tres copias del fichero original “fichero”.
Haga una hebra que se encargue de leer del fichero original, y tantas hebras más como copias del
fichero haya que hacer. La hebra que lee el fichero original irá cargando caracteres en un buffer
habilitado para ello y de un tamaño fijo (por ejemplo, un array de char de tamaño 1024). El resto de
hebras irán copiando bloques de memoria en su copia de fichero que tienen que crear. Utilice
mutexs y variables de condición para resolver el problema.*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

pthread_cond_t lee, escribe;
pthread_mutex_t mutex;



char cadena[1024];
char nombreFich[1024];

int copias=0;
int fin_fich=0;
int contador=0;

void * func_lee(){
  
  FILE * f_lee;
  
  f_lee=fopen(nombreFich,"r");
  
  while(1){
    
    pthread_mutex_lock(&mutex);
    
      if(fgets(cadena,1024,f_lee)!=NULL)
      {       
        printf("Soy el lector y leí del fichero: %s\n", cadena);
        
        pthread_cond_broadcast(&escribe);
        
        pthread_cond_wait(&lee,&mutex);
      
      }
      
      else
      {        
        fin_fich=1;
        pthread_cond_broadcast(&escribe);
      }
    
    pthread_mutex_unlock(&mutex);
  }
  
  pthread_mutex_unlock(&mutex);
  fclose(f_lee);
  pthread_exit(NULL);
  
}

void * func_escribe(int * indice){
  
  FILE * f_escribe;
  char copia[1024];
  
  sprintf(copia,"%s%d",nombreFich,*indice);
  
  f_escribe=fopen(copia,"w");
  
  while(1)
  {    
    pthread_mutex_lock(&mutex);
    
    pthread_cond_wait(&escribe,&mutex);
    
    if(fin_fich) break;
    
    fputs(cadena,f_escribe);
    
    
    if(contador < copias-1)
    {      
      printf("Soy el %lu y he leido: %s\n",pthread_self(), cadena);
      contador++;
    }
    
    else
    {      
      contador=0;
      printf("Soy el %lu y he leido: %s\n",pthread_self(), cadena);
      pthread_cond_broadcast(&lee);
    }
    
    pthread_mutex_unlock(&mutex);
  }

  pthread_mutex_unlock(&mutex);
  fclose(f_escribe);

  pthread_exit(NULL);
}



int main(int argc,char ** argv){
  
  int i;
  int vector[copias];
  
  if(argc!=3)
  {
    printf("Error en la linea de ordenes, poner nombre del fichero y luego el numero de copias\n");
    exit(-1);
    }
  
  strcpy(nombreFich,argv[1]);
  
  copias=atoi(argv[2]);
  
  //Declaramos las variables de condición
  pthread_cond_init(&lee,NULL);
  pthread_cond_init(&escribe,NULL);
  //Declaramos el mutex
  pthread_mutex_init(&mutex,NULL);
  
  pthread_t hilos[copias+1];
  
  for(i=1;i<=copias;i++){
    
    vector[i]=i;
    pthread_create(&hilos[i],NULL,(void*)func_escribe,(void*)&vector[i]);
    }
  
  pthread_create(&hilos[0],NULL,(void*)func_lee,NULL);
  
  for(i=1;i<=copias;i++){
    
    pthread_join(hilos[i],NULL);
    }
  
  pthread_join(hilos[0],NULL);
}

