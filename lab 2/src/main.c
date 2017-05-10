#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "lib/estructuras.h"
#include "lib/registros.h"
#include "lib/instrucciones.h"
#include "lib/memoria.h"
#include "lib/buffer.h"

//Colores para la consola de comandos.

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

////////////////////////////////////////////////////////////////////////////
//////////////          Funciones para modificar buffer ID-EX       ////////
////////////////////////////////////////////////////////////////////////////

//obtiene las lineas de control de la operacion a realizar
bufferIDEX* definirLineasControl(bufferIFID* bufferFD, bufferIDEX* bufferIE){
    //definir codigo Operacion
    int code = 99;
    code = definirCodigoOperacion(bufferFD->instruccion);
    //ALUOp
    // 10 = + ; 01 = - ; 11 = * ; 00 = / ; 02 = nada ;
    // operacion add
    if(code==1){
        bufferIE->ALUSrc=0;
        bufferIE->ALUOp=10;
        bufferIE->RegDst=1;
        bufferIE->Branch=2;
        bufferIE->MemWrite=0;
        bufferIE->MemRead=0;
        bufferIE->RegWrite=1;
        bufferIE->MemToReg=0;
    }
 // operacion addi
    if(code==2){
        bufferIE->ALUSrc=1;
        bufferIE->ALUOp=10;
        bufferIE->RegDst=0;
        bufferIE->Branch=2;
        bufferIE->MemWrite=0;
        bufferIE->MemRead=0;
        bufferIE->RegWrite=1;
        bufferIE->MemToReg=0;
    }
    // operacion sub
    if(code==3){
        bufferIE->ALUSrc=0;
        bufferIE->ALUOp=01;
        bufferIE->RegDst=1;
        bufferIE->Branch=2;
        bufferIE->MemWrite=0;
        bufferIE->MemRead=0;
        bufferIE->RegWrite=1;
        bufferIE->MemToReg=0;
    }
    // operacion subi
    if(code==4){
        bufferIE->ALUSrc=1;
        bufferIE->ALUOp=01;
        bufferIE->RegDst=0;
        bufferIE->Branch=2;
        bufferIE->MemWrite=0;
        bufferIE->MemRead=0;
        bufferIE->RegWrite=1;
        bufferIE->MemToReg=0;
    }
    // operacion mul
    if(code==5){
        bufferIE->ALUSrc=0;
        bufferIE->ALUOp=11;
        bufferIE->RegDst=1;
        bufferIE->Branch=2;
        bufferIE->MemWrite=0;
        bufferIE->MemRead=0;
        bufferIE->RegWrite=1;
        bufferIE->MemToReg=0;
    }
    // operacion div
    if(code==6){
        bufferIE->ALUSrc=0;
        bufferIE->ALUOp=00;
        bufferIE->RegDst=1;
        bufferIE->Branch=2;
        bufferIE->MemWrite=0;
        bufferIE->MemRead=0;
        bufferIE->RegWrite=1;
        bufferIE->MemToReg=0;
    }
    //operacion lw
    if (code==7){
        bufferIE->ALUSrc=1;
        bufferIE->ALUOp=10;
        bufferIE->RegDst=0;
        bufferIE->Branch=2;
        bufferIE->MemWrite=0;
        bufferIE->MemRead=1;
        bufferIE->RegWrite=1;
        bufferIE->MemToReg=1;    
    }
    //operacion sw
    if (code==8){
        bufferIE->ALUSrc=1;
        bufferIE->ALUOp=10;
        bufferIE->RegDst=0;
        bufferIE->Branch=2;
        bufferIE->MemWrite=1;
        bufferIE->MemRead=0;
        bufferIE->RegWrite=0;
        bufferIE->MemToReg=2;    
    }

    //operacion beq
    if (code==13){
        bufferIE->ALUSrc=0;
        bufferIE->ALUOp=3;
        bufferIE->RegDst=2;
        bufferIE->Branch=1;
        bufferIE->MemWrite=2;
        bufferIE->MemRead=2;
        bufferIE->RegWrite=2;
        bufferIE->MemToReg=2;    
    }
    //operacion blt
    if (code==14){
        bufferIE->ALUSrc=0;
        bufferIE->ALUOp=4;
        bufferIE->RegDst=2;
        bufferIE->Branch=1;
        bufferIE->MemWrite=2;
        bufferIE->MemRead=2;
        bufferIE->RegWrite=2;
        bufferIE->MemToReg=2;    
    }
    //operacion bgt
    if (code==15){
        bufferIE->ALUSrc=0;
        bufferIE->ALUOp=5;
        bufferIE->RegDst=2;
        bufferIE->Branch=1;
        bufferIE->MemWrite=2;
        bufferIE->MemRead=2;
        bufferIE->RegWrite=2;
        bufferIE->MemToReg=2;    
    }

    // operacion NOP
    if(code==99){
        bufferIE->ALUSrc=2;
        bufferIE->ALUOp=2;
        bufferIE->RegDst=2;
        bufferIE->Branch=2;
        bufferIE->MemWrite=2;
        bufferIE->MemRead=2;
        bufferIE->RegWrite=2;
        bufferIE->MemToReg=2;
    }
    return bufferIE;
}
//obtiene Rs, Rt, Rd del registro
bufferIDEX* definirFormatoInstruccion(instruccion* l, bufferIDEX* bIE, char instruccion[50]){
    //definimos q formato posee la instruccion(R, I o J)
    int code = definirCodigoOperacion(instruccion);
    //limpiamos los elementos del buffer ID-EX
    char imm[30];
    int i = 0;
    int n = 0;
    bIE->Readdata1=0;
    bIE->Readdata2=0;
    bIE->SignExtend=0;
    while(i<30){
        imm[i]='\0';
        if(i<5){
            bIE->Rs[i]='\0';
            bIE->Rt[i]='\0';
            bIE->Rd[i]='\0';        
        }
        i++;
    }
    i=0;

    //saltar la parte de operacion de la instruccion 
    while(instruccion[i-1]!=' ' &&  instruccion[i] != '\0' ){
        i++;
    }
    printf("instruccion: %s\n", instruccion);
    //agregamos registros de la instruccion R
    if (code == 1 || code == 3 || code == 5 || code == 6){
        while(instruccion[i]!=',' && instruccion[i] != '\0'){
            bIE->Rd[n]=instruccion[i];
            i++;
            n++;
        }
        i=i+2;
        n=0;
        while(instruccion[i]!=',' && instruccion[i] != '\0'){
            bIE->Rs[n]=instruccion[i];
            i++;
            n++;
        }
        i=i+2;
        n=0;
        while(instruccion[i]!=',' && instruccion[i] != '\0'){
            bIE->Rt[n]=instruccion[i];
            i++;
            n++;
        }
        printf("bIE->Rd: %s\n", bIE->Rd);
        printf("bIE->Rs: %s\n", bIE->Rs);     
        printf("bIE->Rt: %s\n", bIE->Rt);                
    }
    //formato tipo I, beg bgt, blt
    if (code == 13 || code == 14 || code == 15){
        while(instruccion[i]!=',' && instruccion[i] != '\0'){
            bIE->Rs[n]=instruccion[i];
            i++;
            n++;
        }
        i=i+2;
        n=0;
        while(instruccion[i]!=',' && instruccion[i] != '\0'){
            bIE->Rt[n]=instruccion[i];
            i++;
            n++;
        }
        i=i+2;
        n=0;
        while(instruccion[i]!=',' && instruccion[i] != '\0'){
            imm[n]=instruccion[i];
            i++;
            n++;
        }
        //asignar posicion en Brach a saltar
        bIE->SignExtend=buscarAddress(l, imm);

        printf("bIE->Rs: %s\n", bIE->Rs);
        printf("bIE->Rt: %s\n", bIE->Rt);     
        printf("imm: %s\n", imm);                
        printf("SignExtend: %d\n", bIE->SignExtend);
    }
    //formato tipo I, addi y  subi
    if (code == 2 || code == 4 ){
        while(instruccion[i]!=',' && instruccion[i] != '\0'){
            bIE->Rt[n]=instruccion[i];
            i++;
            n++;
        }
        i=i+2;
        n=0;
        while(instruccion[i]!=',' && instruccion[i] != '\0'){
            bIE->Rs[n]=instruccion[i];
            printf("rs definirFormatoInstruccion: %s\n", bIE->Rs);
            i++;
            n++;
        }
        i=i+2;
        n=0;
        while(instruccion[i]!=',' && instruccion[i] != '\0'){
            imm[n]=instruccion[i];
            i++;
            n++;
        }
        bIE->SignExtend=atoi(imm);
        printf("bIE->Rs: %s\n", bIE->Rs);
        printf("bIE->Rt: %s\n", bIE->Rt);     
        printf("imm: %s\n", imm);                
        printf("SignExtend: %d\n", bIE->SignExtend);   
    }
    //formato tipo I, lw ,  sw
    if (code == 7 || code == 8){
        while(instruccion[i]!=',' && instruccion[i] != '\0'){
            bIE->Rt[n]=instruccion[i];
            i++;
            n++;
        }
        i=i+2;
        n=0;
        while(instruccion[i]!=',' && instruccion[i] != '('){
            imm[n]=instruccion[i];
            i++;
            n++;
        }
        i++;
        n=0;
        while(instruccion[i]!=',' && instruccion[i] != ')'){
            bIE->Rs[n]=instruccion[i];
            i++;
            n++;
        }
        bIE->SignExtend=atoi(imm);
        printf("bIE->Rs: %s\n", bIE->Rs);
        printf("bIE->Rt: %s\n", bIE->Rt);     
        printf("imm: %s\n", imm);                
        printf("SignExtend: %d\n", bIE->SignExtend);   
    }
    //formato tipo I, la
    if (code == 9){
        while(instruccion[i]!=',' && instruccion[i] != '\0'){
            bIE->Rt[n]=instruccion[i];
            i++;
            n++;
        }
        i=i+3;
        n=0;
        while(instruccion[i]!=',' && instruccion[i] != ')' && instruccion[i] != '\0'){
            bIE->Rs[n]=instruccion[i];
            i++;
            n++;
        }
        i++;
        n=0;
        printf("bIE->Rs: %s\n", bIE->Rs);
        printf("bIE->Rt: %s\n", bIE->Rt);     
    }

    return bIE;
}


////////////////////////////////////////////////////////////////////////////
//////////////        Etapas del procesador      ///////////////////////////
////////////////////////////////////////////////////////////////////////////
bufferIFID* EtapaIF(bufferIFID* buffer, instruccion* lista, registros* r){

    //limpiar bufferIF-ID antes q sea reutilizado
    buffer=ifidEnCero(buffer);

    //llevar el bufferIF-ID a 0
    int i=0;
    while(i<50){
        buffer->instruccion[i] = '\0';
        i++;
    }
    //buscar instruccion correspondiente al pc actual
    instruccion* auxiliar;
    auxiliar = lista;
    int posicionPC = 0; 
    i = 0;
    while(auxiliar->posicionPC != r->pc ){
        auxiliar=auxiliar->siguiente;
        if (auxiliar->nombreInstruccion[0] != '\0'){
            //posicionPC = posicionPC+4;
        }
    }

    // asignar pc y instruccion al bufferIF-ID
    buffer->addPc = r->pc;
    while(auxiliar->nombreInstruccion[i] != '\0'){
        buffer->instruccion[i] = auxiliar->nombreInstruccion[i];
        i++;
    }
    //asignar +4 al PC
    r->pc = r->pc+4;

    return buffer;
}

bufferIDEX* EtapaID(bufferIFID* bufferFD, bufferIDEX* bufferIE, instruccion* lista, registros* r){
    //limpiamos la informacion del buffer id-ex
    bufferIE = idexEnCero(bufferIE);
    int a = 0;
    //pasamos el nombre de la instruccion
    while(a<50){
    bufferIE->instruccion[a]=bufferFD->instruccion[a];
    a++;
    }

    //obtener lineas de control de la operacion
    bufferIE = definirLineasControl(bufferFD, bufferIE);
    bufferIE->addPc=bufferFD->addPc;
    //obtener Registros a usar
    bufferIE = definirFormatoInstruccion(lista, bufferIE, bufferFD->instruccion);
    //obtener valores de los registros
    bufferIE->Readdata1=valorRegistro(bufferIE->Rs, r);
    bufferIE->Readdata2=valorRegistro(bufferIE->Rt, r);
    //si la operacion es un J, Jal o jr
    int codigoInstruccion = definirCodigoOperacion(bufferFD->instruccion);
    if (codigoInstruccion == 10 || codigoInstruccion == 11 || codigoInstruccion == 12){
        char address[30];
        char registroJr[5]; 
        int i = 0;
        int n = 0;
        while(i<30){
            address[i]='\0';
            if (i<5){   registroJr[i]='\0'; }
            i++;
        }
        i=0;
        //ponemos i cuando empieza el address
        while(bufferFD->instruccion[i-1]!=' '){
            i++;
        }
        //caso J
        if(codigoInstruccion == 10){
            while(bufferFD->instruccion[i]!='\0'){
                address[n]=bufferFD->instruccion[i];
                i++;
                n++;
            }
            r->pc=buscarAddress(lista, address);

        }
        //caso jal
        if(codigoInstruccion == 11){
            while(bufferFD->instruccion[i]!='\0'){
                address[n]=bufferFD->instruccion[i];
                i++;
                n++;
            }      
            //guardamos pc siguiente en $ra
            r->ra=r->pc;   
            //saltamos al address
            r->pc=buscarAddress(lista, address); 
            //printf("address: %s\n", address);
            //printf("pc: %d\n", r->pc );
        }
        //caso Jr
        if(codigoInstruccion == 12){
            while(bufferFD->instruccion[i]!='\0'){
                registroJr[n]=bufferFD->instruccion[i];
                i++;
                n++;
            }
            //printf("registroJr\n");
            //ingresamos el valor de JR en el pc
            r->pc = valorRegistro(registroJr, r);
        }
    }

    return bufferIE;
}

bufferEXMEM* EtapaEX(bufferIDEX* bIE, bufferEXMEM* bEM){
    int i=0;
    long entradaAlu1=0;
    long entradaAlu2=0;

    //limpiamos buffer EX-MEM
    bEM = exmenEnCero(bEM);
    //pasamos el nombre de la instruccion
    while(i<50){
    bEM->instruccion[i]=bIE->instruccion[i];
    i++;
    }
    i=0;

    //asignamos las lineas de control al buffer EX-MEM
    bEM->Branch=bIE->Branch;
    bEM->MemWrite=bIE->MemWrite;
    bEM->MemRead=bIE->MemRead;
    bEM->RegWrite=bIE->RegWrite;
    bEM->MemToReg=bIE->MemToReg;
    bEM->zero=0;
    bEM->ALUresult=0;
    bEM->Readdata2=bIE->Readdata2;//obtenemos el valor de rt para aplicar en la memoria

    //ingresar valores de entrada a la ALU
    entradaAlu1=bIE->Readdata1;
    //ALUSrc = 0 entrda= rt  //ALUSrc = 1 entrda= inmediate 
    if (bIE->ALUSrc==0){
        entradaAlu2=bIE->Readdata2;
    }
    if (bIE->ALUSrc==1){
        entradaAlu2=bIE->SignExtend;
    }
    //printf("entradaAlu1: %d\n", entradaAlu1);
    //printf("entradaAlu2: %d\n", entradaAlu2);

    //operacion ALU
    // 10 = + ; 01 = - ; 11 = * ; 00 = / ; 2 = nada ;
    // 3 = beq ; 5 = bgt; 4 = blt ;
    if (bIE->ALUOp==10){ 
        bEM->ALUresult=entradaAlu1+entradaAlu2;
    }
    if (bIE->ALUOp==11){
        bEM->ALUresult=entradaAlu1*entradaAlu2;
    }    
    if (bIE->ALUOp==00){
        bEM->ALUresult=entradaAlu1/entradaAlu2;
    }
    if (bIE->ALUOp==01 || bIE->ALUOp==03 || bIE->ALUOp==04 || bIE->ALUOp==5){
        bEM->ALUresult=entradaAlu1-entradaAlu2;
        printf("¿es branch?\n"); 
        if (bIE->ALUOp==03 && bEM->ALUresult==0){
            bEM->zero=1;
            printf("la operacion es beq?\n");
        }
        if (bIE->ALUOp==5 && bEM->ALUresult>0){
            bEM->zero=1;
            printf("la operacion es bgt?\n");
        }
        if (bIE->ALUOp==4 && bEM->ALUresult<0){
            bEM->zero=1;
            printf("la operacion es blt?\n");
        }

    }
    printf("ALUresult: %d\n", bEM->ALUresult);

    //asignar que valor va a guardarse en los registros(elegir entre rd y rt)
    if (bIE->RegDst==0){
        while(i<5){
            bEM->MuxRegDst[i]=bIE->Rt[i];
            i++;
        }
    }
    if (bIE->RegDst==1){
        while(i<5){
            bEM->MuxRegDst[i]=bIE->Rd[i];
            i++;
        }
    }
    //si se trata de un brach asigamos en addResult la poscion del PC donde tiene q saltar
    if (bIE->Branch==1){
        bEM->addResult=bIE->SignExtend;
    }

    return bEM;
}

bufferMEMWB* EtapaMEM(bufferIFID* bII, bufferIDEX* bIE, bufferEXMEM* bEM, bufferMEMWB* bMW, memoria* m, registros* r){

    //limpiamos buffer MEM-WB antes de utilizar
    bMW=memwbEnCero(bMW);
    int i = 0;
    //pasamos el nombre de la instruccion
    while(i<50){
    bMW->instruccion[i]=bEM->instruccion[i];
    i++;
    }
    i=0;
    //si es que se cumple el brach se salta al nuevo pc y las instrucciones anteriores son vaciadas.
    if ((bEM->zero==1)&&(bEM->Branch==1)){
        r->pc=bEM->addResult;
        printf("pc salto branch: %d\n", bEM->addResult);
        bII=ifidEnCero(bII);
        bIE=idexEnCero(bIE);
    }

    //si se trata de una instruccion lw busca en la memoria.
    if(bEM->MemRead == 1){
        bMW->Readdata=buscarMemoria(m, bEM->ALUresult);
        printf("dato sacado: %d\n",bMW->Readdata );
    }

    //si hay que escribir en la memoria.
    if(bEM->MemWrite == 1){
        m=agregarMemoria(m, bEM->ALUresult, bEM->Readdata2);
        printf("dato guardado: %d\n", bEM->Readdata2);
        printf("posicion: %d\n", bEM->ALUresult);

    }

    //pasar resto de elementos al buffer MEM-WB
    bMW->RegWrite=bEM->RegWrite;
    bMW->MemToReg=bEM->MemToReg;
    bMW->ALUresult=bEM->ALUresult;
    while(i<5){
        bMW->MuxRegDst[i]=bEM->MuxRegDst[i];
        i++;
    }



    return bMW;
}

bufferMEMWB* EtapaWB(bufferMEMWB* bMW, registros* r){
    int datoGuardar = 0;

    //vemos si el dato a guardar es resultado del ALU o de la memoria.
    if(bMW->MemToReg == 0){
        datoGuardar=bMW->ALUresult;
    }
    if(bMW->MemToReg == 1){
        datoGuardar=bMW->Readdata;
    }

    //decidir si escribir en los registros
    if (bMW->RegWrite == 1){
        r = editarRegistro(r, bMW->MuxRegDst, datoGuardar);
        printf("editar registros: %s valor: %d\n", bMW->MuxRegDst, datoGuardar);
    }

    return bMW;
}

int main(int argc, char const *argv[])
{
    char archivoRegistros[30];
    char archivoPrograma[30];
    char outRegistros[30];
    char outBuffers[30];

    // crear bufers y asignarles espacios de memoria
    bufferIFID* bFD = NULL;
    bufferIDEX* bIE = NULL;
    bufferEXMEM* bEM = NULL;
    bufferMEMWB* bMW = NULL;
    bFD = (bufferIFID *) malloc (sizeof(bufferIFID));
    bIE = (bufferIDEX *) malloc (sizeof(bufferIDEX));
    bEM = (bufferEXMEM *) malloc (sizeof(bufferEXMEM));
    bMW = (bufferMEMWB *) malloc (sizeof(bufferMEMWB));

    //ciclos del Procesador
    int ciclo = 1;
    int ultimoCiclo=0;
    int continuarCiclo=1;
    int esperaNop=0;

    //crear memoria principal
    memoria* listaMemoria = NULL;
    listaMemoria = agregarMemoria(listaMemoria, -1 , -1);
    
    //pedir programa
    printf(YEL "\n ----------------------------- \n" RESET);
    printf(YEL "Inicio Programa\n" RESET);
    printf(YEL "Escriba el nombre del archivo que contenga el Programa\n" RESET);
    printf(GRN "NOTA: EL PROGRAMA DEBE ESTAR EN LENGUAJE MIPS\n" RESET);
    scanf("%s", archivoPrograma);
    printf("El archivo elegido es: %s\n",archivoPrograma);
    // crear lista instrucciones
    instruccion* listaInstrucciones=NULL;
    int finInstruccion=0;
    listaInstrucciones=leerInstruccion(archivoPrograma, listaInstrucciones);
    finInstruccion=ultimaInstruccion(listaInstrucciones);
    //imprimirListaInstrucciones(listaInstrucciones);    


    //pedir registros
    printf(YEL "Escriba el nombre del archivo que contenga los valores de los registros\n" RESET);
    scanf("%s", archivoRegistros);
    printf("El archivo elegido es: %s\n",archivoRegistros);
    //crear Registros
    registros* listaRegistros = NULL;
    listaRegistros = iniciarRegistros(listaRegistros);
    listaRegistros = leerArchivoRegistros(archivoRegistros,listaRegistros); 
    //imprimir los registros
    //printf("Nuevos valores registros registros\n");
    //imprimirRegistros(listaRegistros);



    printf(YEL "Archivo de salida\n" RESET);
    printf(GRN "NOTA: Los ARCHIVOS DE SALIDA DEBEN TERMINAR EN .html\n" RESET);
    printf(YEL "Escriba el nombre del archivo donde quiere que se muestre los registros\n" RESET);
    scanf("%s", outRegistros);
    printf("El archivo es: %s\n",outRegistros);
    printf(YEL "Escriba el nombre del archivo donde quiere que se muestre los buffers a traves de los ciclos\n" RESET);
    scanf("%s", outBuffers);
    printf("El archivo es: %s\n",outBuffers);


    while(listaRegistros->pc<=(finInstruccion+16) && ultimoCiclo<5){

        if (ciclo==1){
            //dejar todos los buffers en 0 todo a 0
            bMW=memwbEnCero(bMW);
            bEM=exmenEnCero(bEM);
            bIE=idexEnCero(bIE);
            bFD=ifidEnCero(bFD);
        }

        esperaNop=espera(bIE, bEM );

        if(esperaNop==0){
            printf("\nEtapaWB\n");
            bMW = EtapaWB(bMW, listaRegistros);
            printf("\nEtapaMEM\n");
            bMW = EtapaMEM(bFD, bIE, bEM, bMW, listaMemoria, listaRegistros);
            printf("\nEtapaEX\n");
            bEM = EtapaEX(bIE, bEM);
            printf("\nEtapaID\n");
            bIE = EtapaID(bFD, bIE, listaInstrucciones, listaRegistros);

            if (listaRegistros->pc>finInstruccion){
                bFD=ifidEnCero(bFD);
                listaRegistros->pc=listaRegistros->pc+4;
                ultimoCiclo++;
            }

            if (listaRegistros->pc<=finInstruccion){
                printf("\nEtapaIF\n");
                bFD = EtapaIF(bFD, listaInstrucciones, listaRegistros);
            }

        }

            if(esperaNop==1){
            printf("\nEtapaWB\n");
            bMW = EtapaWB(bMW, listaRegistros);
            printf("\nEtapaMEM\n");
            bMW = EtapaMEM(bFD, bIE, bEM, bMW, listaMemoria, listaRegistros);
            printf("\nEtapaEX\n");
            bEM = exmenEnCero(bEM);

            esperaNop=0;


        }
            //detectamos si existe hazards de datos
            bIE=detectarHazard(bIE, bEM, bMW);


        //guardamos los valores de el ciclo
        ImprimirBuffers(outBuffers, ciclo, bFD, bIE, bEM, bMW );
        imprimirEnArchivo(outRegistros, listaRegistros, ciclo);    
        ciclo++;
    }
    
    //fin de archivos
    finImpresionBuffers;
    cierreArchivo;

    printf(YEL "\n ----------------------------- \n" RESET);
    printf(YEL "          FIN PROGRAMA         \n" RESET);
    printf(YEL " ----------------------------- \n" RESET);


    //printf("Imprimir registros\n");
    //imprimirRegistros(listaRegistros);

    //printf("Imprimir memoria\n");
    //imprimirMemoria(listaMemoria);



    return 0;
}