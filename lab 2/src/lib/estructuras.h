#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

//estructura con los registros 
typedef struct registros{
    long zero;
    long t0;
    long t1;
    long t2;
    long t3;
    long t4;
    long t5;
    long t6;
    long t7;
    long t8;
    long t9;
    long s0;
    long s1;
    long s2;
    long s3;
    long s4;
    long s5;
    long s6;
    long s7;
    long a0;
    long a1;
    long a2;
    long a3;
    long v0;
    long v1;
    long at;
    long k0;
    long k1;
    long ra;
    long gp;
    long fp;
    long pc;
    long sp;

}registros;

//struc instruccion
typedef struct instruccion{
    char nombreInstruccion[50]; //instruccion completa
    char nombreSeccion[50]; //branch:
    int posicionPC; //posicion en el program counter de la instruccion
    struct instruccion* siguiente;//siguiente instruccion

}instruccion;

//estructura memoria que se utilizara.
typedef struct memoria{
	int posicion;
	int elemento;
	struct memoria* siguiente;
}memoria;

//buffer que trabaran la informacion entre etapas
typedef struct bufferIFID{
	int addPc;
	char instruccion[50];
}bufferIFID;

typedef struct bufferIDEX{
	int addPc;
	int ALUSrc;//entrada ALU rt o imm 
	int ALUOp;
	int RegDst; //eligir si se escribira el registro rd o rt
	int Branch;
	int MemWrite;
	int MemRead;
	int RegWrite;
	int MemToReg;
	int Readdata1;//valor registro rs
	int Readdata2;//valor registr rt
	int SignExtend;//add-i inmeddiate instrucccion
	char Rs[5];
	char Rt[5];
	char Rd[5];
    //nombre solamente para que aparezca en el archivo de lineas de control y saber que instrucción es.
    char instruccion[50];

}bufferIDEX;

typedef struct bufferEXMEM{
	int Branch;
	int MemWrite;
	int MemRead;
	int RegWrite;
	int MemToReg;
	int zero;
	int ALUresult;
	int Readdata2;
	int addResult;//pc donde se tiene q saltar si se cumple BRACH
	char MuxRegDst[5];//registro que se escribira.

    //nombre solamente para que aparezca en el archivo de lineas de control y saber que instrucción es.
    char instruccion[50];

}bufferEXMEM;

typedef struct bufferMEMWB{
	int RegWrite;
	int MemToReg;
	int Readdata;
	int ALUresult;
	char MuxRegDst[5];//registro a escribir

    //nombre solamente para que aparezca en el archivo de lineas de control y saber que instrucción es.
    char instruccion[50];
    
}bufferMEMWB;

#endif
