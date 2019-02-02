/*
Implementar un programa para realizar la suma en forma paralela de los
valores de un vector de 10 números enteros que van de 0 a 9 (puede probar
on aleatorios). Utilice una cantidad de hilos indicada como parámetro de
entrada por la linea de argumentos y reparta la suma del vector entre ellos
(como considere oportuno). La suma debe ser el subtotal devuelto por cada
hilo. Haga comprobación de errores en su programa.
*/
 
#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <unistd.h>
#include <time.h>
 
typedef struct param
{
    int partes;
    int v[10];
    int indice;
 
}PARAM;
 
 
 
void *hiloMensaje(void * param)
{
    int i=0;
    PARAM *parametro=(void*)param;//hacemos un casting para poder utilizar la variable
    int *suma=(int*)malloc(sizeof(int));
    int *sumareal=(int*)malloc(sizeof(int));
 
    printf("Los número del vector según las partes es:\n");
    do
    {
        if(i==parametro->partes)
        {
            printf("\nLa suma del subtotal es: %d\n", *suma);
            i=0;
            *sumareal+=*suma;
            *suma=0;
        }
        else
        {
            *suma=*suma + parametro->v[parametro->indice];
            printf("%d ", parametro->v[parametro->indice]);
            parametro->indice++;
            i++;    
        }
        
    }while(parametro->indice<10);

    printf("\nLa suma del subtotal es: %d\n", *suma);
    *sumareal+=*suma;
    puts("");
    pthread_exit((void*)sumareal);
}
 
int main(int argc, char **argv)
{
    if(argc!=2)
    {
        printf("Error en la línea de órdenes. Pruebe con -> ./a.out <nº hilos>\n");
        exit(-1);
    }
    else
    {
        system("clear");
        PARAM parametro;
        int N=atoi(argv[1]);//Numero de hilos
        pthread_t *hilo=(pthread_t*)malloc(sizeof(pthread_t)*N);
        srand(time(NULL));
        int i;
        int suma=0;
        int *sumareal=(int*)malloc(sizeof(int));
        int total=0;
 
        printf("El vector de la estructura es:\n");
 
        parametro.partes=10/N;//numero de elementos a pasar al hilo
        parametro.indice=0;
 
        for(i=0;i<10;i++)
        {
            parametro.v[i]=rand()%10;
            printf("%d ", parametro.v[i]);
            suma=suma+parametro.v[i];
        }
        printf("\nLa suma total del vector es: %d\n", suma);
 
        for(i=0;i<N;i++)
        {
            pthread_create(&hilo[i], NULL, (void*)hiloMensaje, (void*)&parametro);
 
            if(pthread_join(hilo[i], (void*)&suma)!=0)//Comprobación de errores
            {
                printf("Error en el join.\n");
                exit(EXIT_FAILURE);
            }
            total+=suma;
        }
        
        exit(EXIT_SUCCESS);        
    }
     
}