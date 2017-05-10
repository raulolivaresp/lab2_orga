 #ifndef REGISTROS_H
 #define REGISTROS_H

#include "estructuras.h"

////////////////////////////////////////////////////////////////////////////
//////////////  Funciones sobre los registros   ////////////////////////////
////////////////////////////////////////////////////////////////////////////

//inicializamos todos los registros en 0
registros* iniciarRegistros(registros* r);

//editar el valor de un registro
registros* editarRegistro(registros* r, char reg[5], int n);

//obtener el valor de un registro
int valorRegistro(char reg[5], registros* r);

//lee el archivo q contiene los valores de los registros y los guarda
registros* leerArchivoRegistros(char* archivo, registros* r);

/////////////////////////////////////////////////////////////
///// FUNCIONES PARA IMPRIMIR LOS REGISTROS POR CONSOLA /////
/////////////////////////////////////////////////////////////

//imprime los registros por la consola de comandos
void imprimirRegistros(registros* );

//funcion para escribir los registros en un archivo.
void imprimirEnArchivo(char* archivo, registros*r, int ciclo);

//finaliza escritura del archivo con </table>
void cierreArchivo(char* archivo);

#endif /* REGISTROS_H */