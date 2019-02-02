/*
En concurrencia, el problema del productor-consumidor19 es un problema típico,
y su enunciado general es el siguiente:
Hay un proceso generando algún tipo de datos (registros, caracteres, aumento de
variables, modificaciones en arrays, modificación de ficheros, etc) y
poniéndolos en un buffer. Hay un consumidor que está extrayendo datos de
dicho buffer de uno en uno.
El sistema está obligado a impedir la superposición de las operaciones sobre
los datos, es decir, sólo un agente (productor o consumidor) puede acceder al
buffer en un momento dado (así el productor no sobrescribe un elemento que esté
 leyendo el consumidor, y viceversa). Estaríamos hablando de la sección crítica.
Si suponemos que el buffer es limitado y está completo, el productor debe
esperar hasta que el consumidor lea al menos un elemento para así poder seguir
 almacenando datos. En el caso de que el buffer esté vacío el consumidor debe
 esperar a que se escriba información nueva por parte del productor.
Existen variaciones del problema productor-consumidor, como por ejemplo en el
caso de que el buffer sea ilimitado. Consulte la Web si desea obtener más
información sobre ello.
Una vez haya estudiado más detenidamente el problema del productor-consumidor
realice las siguientes tareas:
a) Implemente el problema para hilos teniendo en cuenta que la sección crítica
va a ser un array de enteros con una capacidad de 5 elementos. Haga una
implementación usando mutexs pero no variables de condición, por lo que se
producirá espera activa en casos en los que no haya sitio donde producir o no
haya items que consumir.
*/
 
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
 

#define N 5
#define MAX_ITEMS 20
 
int buffer[N];
int contador = 0;
pthread_mutex_t semaforo = PTHREAD_MUTEX_INITIALIZER; //GLOBAL MUTEX
 
void *funcion_Consumidor()
{
  int num_items = 0,pos_buffer=0, item;
 
  while (num_items<= MAX_ITEMS)
  {
    pthread_mutex_lock(&semaforo);
    if (contador!=0) {
      item= buffer[pos_buffer];
      printf("Soy el cliente y leo de %d el valor %d\n", pos_buffer, item);
      pos_buffer = (pos_buffer + 1) % N;
      contador= contador - 1;
      num_items++;
    }
    pthread_mutex_unlock(&semaforo);
  }
    pthread_exit(NULL); 
}
 
void *funcion_Productor()
{
    int num_items=0,pos_buffer=0;
 
    while (num_items<= MAX_ITEMS)
    {
        pthread_mutex_lock(&semaforo);
        if (contador!=N) {
            buffer[pos_buffer]= rand()%20;
            printf("Soy el productor y escribo en %d el valor = %d\n", pos_buffer, buffer[pos_buffer]);
            pos_buffer = (pos_buffer + 1) % N;
            contador= contador + 1;
            num_items++;
        }
        pthread_mutex_unlock(&semaforo);
    }
    pthread_exit(NULL);
}

int main(void)
{
  system("clear");
  pthread_t hilo_consumidor, hilo_productor;
  int error;
 
  error = pthread_create(&hilo_productor, NULL, (void*)funcion_Productor, NULL);
  if (error != 0)
      printf("Error pthread_create...\n");
 
  error = pthread_create(&hilo_consumidor, NULL, (void*)funcion_Consumidor, NULL);
  if (error != 0)
      printf("Error pthread_create...\n");
  error = pthread_join(hilo_consumidor, NULL);
  if (error != 0)
      printf("Error pthread_join...\n");
  error = pthread_join(hilo_productor, NULL);
  if (error != 0)
      printf("Error pthread_join...\n");
}
 
