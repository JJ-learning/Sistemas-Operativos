/*
Implemente un programa que cree dos hebras. Cada hebra ejecutará una
función a la que se le pasará como parámetro una cadena, concretamente
a la primera hebra se le pasará la cadena “hola” y a la segunda “mundo”.
La función que deben ejecutar ambas debe imprimir carácter a carácter la
cadena recibida, haciendo un sleep(1) entre cada impresión de carácter.
Observe los resultados obtenidos.
Repita lo mismo pero recogiendo las dos cadenas por la linea de argumentos.
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
 
void *hiloMensaje(char* mensaje){
  int i;
  for (i = 0; i < strlen(mensaje); i++) {
    printf("%c\n", mensaje[i]);
    //putchar(mensaje[i]);
    sleep(1);
  }
  pthread_exit(NULL); //Fin de la hebra sin devolver nada
}
int main(void)
{
  system("clear");
  pthread_t thd1, thd2;
  char cadena1[] = "HOLA";
  char cadena2[] = "MUNDO";
 
  //Declaración de dos hebras
  pthread_create(&thd1, NULL, (void *)hiloMensaje, (void *) &cadena1); // No hace falta poner & para una cadena
  pthread_join(thd1, NULL); // wait
 
  pthread_create(&thd2, NULL, (void *)hiloMensaje, (void *) &cadena2);
  
    pthread_join(thd2, NULL);
 
    /*Si no se ponen estos join() en el programa principal y simplemente lanzamos los dos hilos y finalizamos, lo más probable es que los hilos no lleguen a ejecutarse completamente o incluso que no lleguen ni a empezar antes de que el programa principal termine.*/
    printf("Han finalizado las threads.\n");
    exit(EXIT_SUCCESS);
}