#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "estructuras.h"

////////////////////////////////////////////////////////////////////////////
//////////////        Funciones de la memoria      /////////////////////////
////////////////////////////////////////////////////////////////////////////

//Agrega un elemento a la memoria, en posicion sp
memoria* agregarMemoria(memoria* m, int posicionN, int n){

    memoria* ultimo = NULL;
    memoria* auxiliar = NULL;
    ultimo = m;
    auxiliar = m;
    int encontrar = 0;
    int encontrarArreglo = 0;

    //buscamos si existe la posicionN en el arreglo
    if (m != NULL){
        while(auxiliar !=NULL && auxiliar->posicion != posicionN){
             auxiliar=auxiliar->siguiente;
        }
    } 
    if (auxiliar != NULL){
        if(posicionN == auxiliar->posicion){
            encontrar=1;
        }
    }

    //Si ya existe la posicion anteriormente
    if (encontrar==1){
        auxiliar->elemento=n;
    }
    
    //en caso que haya que agregar un nuevo nodo
    if (encontrar == 0){
        //apuntamos al ultimo elemento
        while(m != NULL && ultimo->siguiente !=NULL){
            ultimo= ultimo->siguiente;
        }

        //asignamos un nueva memoria
        memoria* nuevo;
        nuevo = (memoria *) malloc (sizeof(memoria));

        nuevo->posicion=posicionN;
        nuevo->elemento = n;
        if (encontrar == 0){
            nuevo->siguiente = NULL;
        }

        if(m == NULL ){
            m=nuevo;
            ultimo=nuevo;
         }

         else{
             ultimo -> siguiente = nuevo;
             ultimo = nuevo;
         }

    }

    return m;
}
//busca dato guardado en una posicionN de la memoria
int buscarMemoria(memoria* m, int posicionN){
    int n=0;
    int encontrar = 0 ;
    memoria* auxiliar = NULL;
    auxiliar = m;

    while(auxiliar !=NULL && encontrar==0){
        if (auxiliar->posicion==posicionN){
            n=auxiliar->elemento;
            encontrar=1;
            printf("posicion de memoria: %d\n", auxiliar->posicion);
            printf("elemento en memoria: %d\n", auxiliar->elemento);
        }
        auxiliar=auxiliar->siguiente;
    }

    if (encontrar==0){
        printf("No se a encontrado la posicion: %d\n", posicionN);
    }

    return n;
}



//////////////////////////////////////////////////////////////////
///// FUNCIONES PARA IMPRIMIR LA MEMORIA POR CONSOLA //////
//////////////////////////////////////////////////////////////////
void imprimirMemoria(memoria* m){
    memoria* auxiliar = NULL;
    auxiliar = m;
    while(auxiliar!=NULL){
        printf("posicion de memoria: %d\n", auxiliar->posicion);
        printf("elemento en memoria: %d\n", auxiliar->elemento);
        auxiliar=auxiliar->siguiente;
    }

}

