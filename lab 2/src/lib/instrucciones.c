#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "estructuras.h"

////////////////////////////////////////////////////////////////////////////
//////////////  Funciones sobre las instrucciones   ////////////////////////
////////////////////////////////////////////////////////////////////////////

//agregar una instruccion a la lista de instrucciones
instruccion* agregarInstruccion(char nombre[50],int PC ,instruccion* primero){

    instruccion* ultimo = NULL;
    ultimo = primero;
    int i = 0;
    int esUnaInstruccion=1;

    while(primero != NULL && ultimo->siguiente !=NULL){
        ultimo= ultimo->siguiente;
    }

    instruccion* nuevo;
    nuevo = (instruccion *) malloc (sizeof(instruccion));
    while(i<50){
        if (nombre[i]==':'){
           esUnaInstruccion=0;
        }
        i++;
    }
    i=0;

    while(nombre[i] != '\0' ){
            nuevo-> nombreInstruccion[i] = nombre[i];
            i++;
    }
    nuevo->posicionPC=PC;
    nuevo->siguiente = NULL;
    i=0;
    if(primero == NULL ){
        primero=nuevo;
        ultimo=nuevo;
     }

     else{
         ultimo -> siguiente = nuevo;
         ultimo = nuevo;
     }

     return primero;
}
//lee un archivo y va guardando las instrucciones dentro de una lista
instruccion* leerInstruccion(char* archivo, instruccion* lista){
	
	FILE * File;
	char elemento[100];
	char nombre[50];
	int i = 0;
    int PC= 0;
    int esUnaInstruccion= 1;

	File= fopen(archivo, "r");
	
	//archivo encontrado?
	if(File==NULL){
        printf("Archivo vacio");
    }
    //si es q encontro el archivo
    else{
    	while(feof(File) == 0){
    		fgets(elemento,100,File);
    		if(elemento[0]!='\0' && elemento[0]!='\n'){ 
    			//ingresa los elementos al arreglo nombre
    			while(elemento[i]!='\0' && elemento[i]!='\n'){
    				nombre[i] = elemento[i];
    				i++;
    				if (elemento[i]==':')
                    {
                        esUnaInstruccion=0;
                    }

    			}
    			//rellena con vacio '\0' el resto de los elementos del arreglo
    			while(i<50){
    				nombre[i]='\0';
    				i++;
    			}
    			i=0;
                if(esUnaInstruccion==1){
                    lista=agregarInstruccion(nombre, PC, lista);
                    PC=PC+4;
                }
                if(esUnaInstruccion==0){
                    lista=agregarInstruccion(nombre, -4, lista);
                }        
                esUnaInstruccion=1;
    		}
    		//limpieza del arreglo 
    		while(i<50){
    			nombre[i]='\0';
    			i++;
    		}
    		i=0;

    		while(i<100){
    			elemento[i]='\0';
    			i++;
    		}
    		i=0;

     	}
    }

    fclose(File);
    return lista;
}
//buscar la instruccion donde apunta las instrucciones J o branch
int buscarAddress(instruccion* lista, char address[30]){
    int pcAddress=0;
    int tamanoAddress=0;
    int i=0;
    int iguales=0;
    int addressEncontrado=0;
    int ultimoAddress=0;

    instruccion* auxiliar = NULL;
    instruccion* auxiliar2 = NULL;
    instruccion* ultimo = NULL;
    int ultimo2=0;

    auxiliar = lista;
    ultimo=lista;
    //buscamos de forma normal la direccion del address 
    while(auxiliar!=NULL && addressEncontrado==0){
        while(auxiliar->nombreInstruccion[i]!='\0' && auxiliar->nombreInstruccion[i]!=':' && address[i]!='\0'){
            if (address[i]==auxiliar->nombreInstruccion[i]){
                iguales++;
            }
            tamanoAddress++;
            i++;
        }
        if (tamanoAddress==iguales){
           addressEncontrado=1;
        }
        tamanoAddress=0;
        iguales=0;
        i=0;
        //saltamos a la siguiente instruccion
        pcAddress=pcAddress+4;
   
        //saltamos a las siguientes instruccciones
        auxiliar2=auxiliar;
        auxiliar=auxiliar->siguiente;
    };
    
    printf("nombre ultimo instruccion: %s\n", auxiliar2->nombreInstruccion );

    //buscamos si se trata del ultimo address
    while(ultimo->siguiente!=NULL){
        ultimo=ultimo->siguiente;
    }
    //si se llego al ultimo pc lo asigamos()
    if (ultimo->nombreInstruccion==auxiliar2->nombreInstruccion && ultimo->posicionPC==auxiliar2->posicionPC){
        ultimoAddress=1;
    }


    if((addressEncontrado==1) && (ultimoAddress==0)){
        pcAddress=auxiliar->posicionPC;
    }
    if((addressEncontrado==1) && (ultimoAddress==1)){
        pcAddress=5000;
        //pcAddress=ultimo2+4;
        printf("fin programa\n");
    }
    if (addressEncontrado==0){
        pcAddress=-4;
        printf("error no se a encotnrado: %s\n", address);
    }

    return pcAddress;
}

//definir codigo instruccion
int definirCodigoOperacion(char nombre[50]){

    int n = 99; //NULL
    // operacion add
    if(nombre[0]=='a' && nombre[1]=='d' && nombre[2]=='d'){
        n=1;
    }
    // operacion addi
    if(nombre[0]=='a' && nombre[1]=='d' && nombre[2]=='d' && nombre[3]=='i'){
        n=2;
    }
    // operacion sub
    if(nombre[0]=='s' && nombre[1]=='u' && nombre[2]=='b' ){
        n=3;
    }
    // operacion subi
    if(nombre[0]=='s' && nombre[1]=='u' && nombre[2]=='b' && nombre[3]=='i'){
        n=4;
    }
    // operacion mul
    if(nombre[0]=='m' && nombre[1]=='u' && nombre[2]=='l' ){
        n=5;
    }
    // operacion div
    if(nombre[0]=='d' && nombre[1]=='i' && nombre[2]=='v' ){
        n=6;
    }
    //operacion lw
    if (nombre[0]=='l' && nombre[1]=='w'){
        n=7;
    }
    // operacion sw 
    if (nombre[0]=='s' && nombre[1]=='w'){
        n=8;
    }
    //operacion la
    if (nombre[0]=='l' && nombre[1]=='a'){
        n=9;
    }
    // operacion j
    if (nombre[0]=='j'){
        n=10;
    }
    //operacion jal
    if (nombre[0]=='j' && nombre[1]=='a' && nombre[2]=='l'){
        n=11;
    }
    // operacion jr 
    if (nombre[0]=='j' && nombre[1]=='r'){
        n=12;
    }
    //operacion beq
    if (nombre[0]=='b' && nombre[1]=='e' && nombre[2]=='q'){
        n=13;
    }
    //operacion blt
    if (nombre[0]=='b' && nombre[1]=='l' && nombre[2]=='t'){
        n=14;
    }
    //operacion bgt
    if (nombre[0]=='b' && nombre[1]=='g' && nombre[2]=='t'){
        n=15;
    }

    return n;
}

//buscar Ultima instruccion;
int ultimaInstruccion(instruccion* lista){

    instruccion* auxiliar=NULL;
    auxiliar=lista;
    int ultimoPC=0;

    while(auxiliar->siguiente!=NULL){
        if(ultimoPC<auxiliar->posicionPC){
            ultimoPC=auxiliar->posicionPC;
        }
        auxiliar=auxiliar->siguiente;
    }

    ultimoPC=ultimoPC+4;
    printf("pc ultima instruccion: %d\n", ultimoPC );
    return ultimoPC;
}


//////////////////////////////////////////////////////////////////
///// FUNCIONES PARA IMPRIMIR LAS INSTRUCCIONES POR CONSOLA //////
//////////////////////////////////////////////////////////////////
void imprimirListaInstrucciones(instruccion* lista){

	instruccion* auxiliar=NULL;
    auxiliar = lista;
    while(auxiliar->nombreInstruccion!=NULL && auxiliar!=NULL){
        printf("nombreInstruccion: %s\n",auxiliar->nombreInstruccion);
        printf("posicionPC: %d\n",auxiliar->posicionPC);
        auxiliar=auxiliar->siguiente;
    }

}

