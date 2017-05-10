 #ifndef INSTRUCCIONES_H
 #define INSTRUCCIONES_H

#include "estructuras.h"

////////////////////////////////////////////////////////////////////////////
//////////////  Funciones sobre las instrucciones   ////////////////////////
////////////////////////////////////////////////////////////////////////////

//agregar una instruccion a la lista de instrucciones
instruccion* agregarInstruccion(char nombre[50],int PC ,instruccion* primero);

//lee un archivo y va guardando las instrucciones dentro de una lista
instruccion* leerInstruccion(char* archivo, instruccion* lista);

//buscar la instruccion donde apunta las instrucciones J o branch
int buscarAddress(instruccion* lista, char address[30]);

//definir que instruccion es la que se ha ingresado
int definirCodigoOperacion(char nombre[50]);

//buscar Ultima instruccion;
int ultimaInstruccion(instruccion* lista);

//////////////////////////////////////////////////////////////////
///// FUNCIONES PARA IMPRIMIR LAS INSTRUCCIONES POR CONSOLA //////
//////////////////////////////////////////////////////////////////
void imprimirListaInstrucciones(instruccion* lista);

#endif /* INSTRUCCIONES_H */