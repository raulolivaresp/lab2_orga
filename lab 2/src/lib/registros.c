#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "estructuras.h"



////////////////////////////////////////////////////////////////////////////
//////////////  Funciones sobre los registros   ////////////////////////////
////////////////////////////////////////////////////////////////////////////

//inicializamos todos los registros en 0
registros* iniciarRegistros(registros* r){
    r = (registros*) malloc (sizeof(registros));
    r->zero=0;
    r->t0=0;
    r->t1=0;
    r->t2=0;
    r->t3=0;
    r->t4=0;
    r->t5=0;
    r->t6=0;
    r->t7=0;
    r->t8=0;
    r->t9=0;
    r->s0=0;
    r->s1=0;
    r->s2=0;
    r->s3=0;
    r->s4=0;
    r->s5=0;
    r->s6=0;
    r->s7=0;
    r->a0=0;
    r->a1=0;
    r->a2=0;
    r->a3=0;
    r->v0=0;
    r->v1=0;
    r->k0=0;
    r->k1=0;
    r->at=0;
    r->ra=0;
    r->gp=0;
    r->fp=0;
    r->pc=0;
    r->sp=0;
   
    return r;
}
//editar el valor de un registro
registros* editarRegistro(registros*r, char reg[5], long n){
    if (reg[1] == 'z' && reg[2]=='e'){  r->zero=0;    }
    if (reg[1] == 't' && reg[2]=='0'){  r->t0=n;    }
    if (reg[1] == 't' && reg[2]=='1'){  r->t1=n;    }
    if (reg[1] == 't' && reg[2]=='2'){  r->t2=n;    }
    if (reg[1] == 't' && reg[2]=='3'){  r->t3=n;    }
    if (reg[1] == 't' && reg[2]=='4'){  r->t4=n;    }
    if (reg[1] == 't' && reg[2]=='5'){  r->t5=n;    }
    if (reg[1] == 't' && reg[2]=='6'){  r->t6=n;    }
    if (reg[1] == 't' && reg[2]=='7'){  r->t7=n;    }
    if (reg[1] == 't' && reg[2]=='8'){  r->t8=n;    }
    if (reg[1] == 't' && reg[2]=='9'){  r->t9=n;    }
    if (reg[1] == 's' && reg[2]=='0'){  r->s0=n;    }
    if (reg[1] == 's' && reg[2]=='1'){  r->s1=n;    }
    if (reg[1] == 's' && reg[2]=='2'){  r->s2=n;    }
    if (reg[1] == 's' && reg[2]=='3'){  r->s3=n;    }
    if (reg[1] == 's' && reg[2]=='4'){  r->s4=n;    }
    if (reg[1] == 's' && reg[2]=='5'){  r->s5=n;    }
    if (reg[1] == 's' && reg[2]=='6'){  r->s6=n;    }
    if (reg[1] == 's' && reg[2]=='7'){  r->s7=n;    }
    if (reg[1] == 'a' && reg[2]=='0'){  r->a0=n;    }
    if (reg[1] == 'a' && reg[2]=='1'){  r->a1=n;    }
    if (reg[1] == 'a' && reg[2]=='2'){  r->a2=n;    }
    if (reg[1] == 'a' && reg[2]=='3'){  r->a3=n;    }
    if (reg[1] == 'v' && reg[2]=='0'){  r->v0=n;    }
    if (reg[1] == 'v' && reg[2]=='1'){  r->v1=n;    }
    if (reg[1] == 'a' && reg[2]=='t'){  r->at=n;    }
    if (reg[1] == 'k' && reg[2]=='0'){  r->k0=n;    }
    if (reg[1] == 'k' && reg[2]=='1'){  r->k1=n;    }
    if (reg[1] == 'r' && reg[2]=='a'){  r->ra=n;    }
    if (reg[1] == 'g' && reg[2]=='p'){  r->gp=n;    }
    if (reg[1] == 'f' && reg[2]=='p'){  r->fp=n;    }
    if (reg[1] == 'p' && reg[2]=='c'){  r->pc=n;    }
    if (reg[1] == 's' && reg[2]=='p'){  r->sp=n;    }

    return r;
}
//obtener el valor de un registro
int valorRegistro(char reg[5], registros* r){
    long n=0;
    if (reg[1] == 'z' && reg[2]=='e'){  n=r->zero;    }
    if (reg[1] == 'a' && reg[2]=='t'){  n=r->at;    }
    if (reg[1] == 'v' && reg[2]=='0'){  n=r->v0;    }
    if (reg[1] == 'v' && reg[2]=='1'){  n=r->v1;    }
    if (reg[1] == 'a' && reg[2]=='0'){  n=r->a0;    }
    if (reg[1] == 'a' && reg[2]=='1'){  n=r->a1;    }
    if (reg[1] == 'a' && reg[2]=='2'){  n=r->a2;    }
    if (reg[1] == 'a' && reg[2]=='3'){  n=r->a3;    }    
    if (reg[1] == 't' && reg[2]=='0'){  n=r->t0;    }
    if (reg[1] == 't' && reg[2]=='1'){  n=r->t1;    }
    if (reg[1] == 't' && reg[2]=='2'){  n=r->t2;    }
    if (reg[1] == 't' && reg[2]=='3'){  n=r->t3;    }
    if (reg[1] == 't' && reg[2]=='4'){  n=r->t4;    }
    if (reg[1] == 't' && reg[2]=='5'){  n=r->t5;    }
    if (reg[1] == 't' && reg[2]=='6'){  n=r->t6;    }
    if (reg[1] == 't' && reg[2]=='7'){  n=r->t7;    }
    if (reg[1] == 's' && reg[2]=='0'){  n=r->s0;    }
    if (reg[1] == 's' && reg[2]=='1'){  n=r->s1;    }
    if (reg[1] == 's' && reg[2]=='2'){  n=r->s2;    }
    if (reg[1] == 's' && reg[2]=='3'){  n=r->s3;    }
    if (reg[1] == 's' && reg[2]=='4'){  n=r->s4;    }
    if (reg[1] == 's' && reg[2]=='5'){  n=r->s5;    }
    if (reg[1] == 's' && reg[2]=='6'){  n=r->s6;    }
    if (reg[1] == 's' && reg[2]=='7'){  n=r->s7;    }
    if (reg[1] == 't' && reg[2]=='8'){  n=r->t8;    }
    if (reg[1] == 't' && reg[2]=='9'){  n=r->t9;    }   
    if (reg[1] == 'k' && reg[2]=='0'){  n=r->k0;    }
    if (reg[1] == 'k' && reg[2]=='1'){  n=r->k1;    }
    if (reg[1] == 'g' && reg[2]=='p'){  n=r->gp;    }
    if (reg[1] == 's' && reg[2]=='p'){  n=r->sp;    }
    if (reg[1] == 'f' && reg[2]=='p'){  n=r->fp;    }
    if (reg[1] == 'r' && reg[2]=='a'){  n=r->ra;    }
    if (reg[1] == 'p' && reg[2]=='c'){  n=r->pc;    }

    return n;
}
//lee el archivo q contiene los valores de los registros y los guarda
registros* leerArchivoRegistros(char* archivo, registros* r){
    
    FILE * File;
    char elemento[50];
    char nombre[5];
    char numeroChar[15];
    long numeroInt=0;
    int i = 0; //elemento 
    int n = 0; //registros 

    //rellena con vacio '\0' el resto de los elementos del arreglo
    while(i<50){
        elemento[i]='\0';
        if (i<30){
            numeroChar[i]='\0';                   
        }
        if (i<5){
            nombre[i]='\0';                   
       }
        i++;
        }
    i=0;

    File= fopen(archivo, "r");
    //archivo encontrado?
    if(File==NULL){
        printf("Archivo vacio");
    }
    //si es q encontro el archivo
    else{
        while(feof(File) == 0){
            fgets(elemento,50,File);
            if(elemento[0]!='\0' && elemento[0]!='\n'){ 
                //printf("elemento: %s\n", elemento);
                //ingresa el nombre del registro al arreglo nombre
                while(elemento[i]!='\0' && elemento[i]!='\n' && elemento[i]!=' '){
                    nombre[n] = elemento[i];
                    n++;
                    i++;
                }           
                while(n<5){
                    nombre[n]='\0';
                    n++;
                }
                n=0;
                i++;
                while(elemento[i]!='\0' && elemento[i]!='\n'){
                    numeroChar[n] = elemento[i];
                    n++;
                    i++;
                }            
        
                if(numeroChar[1]=='x'){
                    sscanf(numeroChar, "%x", &numeroInt);
                }
                if(numeroChar[1]!='x'){
                    numeroInt = atol(numeroChar);
                }
                r = editarRegistro(r, nombre, numeroInt);

                n=0;
                i=0;
                numeroInt = 0;
                //rellena con vacio '\0' el resto de los elementos del arreglo
                while(i<50){
                    elemento[i]='\0';
                    if (i<15){
                        numeroChar[i]='\0';                   
                    }
                    if (i<5){
                        nombre[i]='\0';                   
                    }
                    i++;
                }
                i=0;
            }
        }
    }

    fclose(File);
    return r;
}

/////////////////////////////////////////////////////////////
/////       FUNCIONES PARA IMPRIMIR LOS REGISTROS       /////
/////////////////////////////////////////////////////////////

//imprime los registros por la consola de comandos
void imprimirRegistros(registros* r){
	printf("$zero: %li\n", r->zero); 
	printf("$at: %li\n", r->at);
	printf("$v0: %li\n", r->v0);
	printf("$v1: %li\n", r->v1);
	printf("$a0: %li\n", r->a0);
	printf("$a1: %li\n", r->a1);
	printf("$a2: %li\n", r->a2);
	printf("$a3: %li\n", r->a3);

	printf("$t0: %li\n", r->t0);
	printf("$t1: %li\n", r->t1);
	printf("$t2: %li\n", r->t2);
	printf("$t3: %li\n", r->t3);
	printf("$t4: %li\n", r->t4);
	printf("$t5: %li\n", r->t5);
	printf("$t6: %li\n", r->t6);
	printf("$t7: %li\n", r->t7);
	printf("$s0: %li\n", r->s0);
	printf("$s1: %li\n", r->s1);
	printf("$s2: %li\n", r->s2);
	printf("$s3: %li\n", r->s3);
	printf("$s4: %li\n", r->s4);
	printf("$s5: %li\n", r->s5);
	printf("$s6: %li\n", r->s6);
	printf("$s7: %li\n", r->s7);

	printf("$t8: %li\n", r->t8);
	printf("$t9: %li\n", r->t9);

	printf("$k0: %li\n", r->k0);
	printf("$k1: %li\n", r->k1);
	printf("$gp: %li\n", r->gp);
	printf("$sp: %li\n", r->sp);
	printf("$fp: %li\n", r->fp);
	printf("$ra: %li\n", r->ra);
	printf("$pc: %li\n", r->pc);

}

//funcion para escribir los registros en un archivo.
void imprimirEnArchivo(char* archivo, registros*r, int ciclo){
    FILE *fp;
    
    char cadena[100] = "<h1>Tabla registros.</h1>\n";
    char inicioTabla[20] ="<TABLE BORDER>";
    char finTabla[10] ="</TABLE>";
    char tablaCabezera[200] = "<TR><TH>Ciclo</TH> <TH>PC</TH> <TH>zero</TH><TH>$at</TH><TH>$v0</TH> <TH>$v1</TH> <TH>$a0</TH> <TH>$a1</TH> <TH>$a2</TH> <TH>$a3</TH>";
    char tablaCabezera2[250] = "<TH>$t0</TH><TH>$t1</TH><TH>$t2</TH><TH>$t3</TH><TH>$t4</TH><TH>$t5</TH><TH>$t6</TH><TH>$t7</TH> <TH>$s0</TH><TH>$s1</TH><TH>$s2</TH><TH>$s3</TH><TH>$s4</TH><TH>$s5</TH><TH>$s6</TH><TH>$s7</TH><TH>$t8</TH><TH>$t9</TH>";
    char tablaCabezera3[100] = "<TH>$k0</TH><TH>$k1</TH><TH>$gp</TH><TH>$sp</TH><TH>$fp</TH><TH>$ra</TH>    </TR>"; 
    fp = fopen ( archivo, "a" );
    
    //fputs( cadena, fp );
    if (ciclo==1){
        fprintf(fp, "%s", cadena);
        fprintf(fp, "%s", inicioTabla);
        fprintf(fp, "%s", tablaCabezera);
        fprintf(fp, "%s", tablaCabezera2);
        fprintf(fp, "%s", tablaCabezera3);
    }

        fprintf(fp, "<TR><TH>C%d</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH>\n",ciclo, r->pc, r->zero, r->at, r->v0, r->v1,r->a0, r->a1,r->a2, r->a3);
        fprintf(fp, "<TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH>\n",r->t0, r->t1,r->t2, r->t3, r->t4,r->t5, r->t6, r->t7,r->s0, r->s1,r->s2, r->s3);
        fprintf(fp, "<TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH>", r->s4,r->s5, r->s6,r->s7,r->t8,r->t9);
        fprintf(fp, "<TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH><TH>%li</TH>", r->k0,r->k1, r->gp,r->sp,r->fp,r->ra);
        
        fprintf(fp, "</TR>" );

    fclose ( fp );
}

void cierreArchivo(char* archivo){
    FILE *fp;
    char finTabla[10] ="</TABLE>";

    fp = fopen ( archivo, "a" );
        
    fprintf(fp, "%s", finTabla);
 
    fclose ( fp );
}