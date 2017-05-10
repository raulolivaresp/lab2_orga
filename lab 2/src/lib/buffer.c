#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "estructuras.h"


////////////////////////////////////////////////////////////////////////////
//////////////          Limpiar buffers, dejar variables en 0       ////////
////////////////////////////////////////////////////////////////////////////

bufferIFID* ifidEnCero(bufferIFID* bII){
    int i = 0;
    bII->addPc = 0;
    while(i<50){
        bII->instruccion[i]='\0';
        i++;
    }
    bII->instruccion[0]='n';
    bII->instruccion[1]='o';
    bII->instruccion[2]='p';

    return bII;
}

bufferIDEX* idexEnCero(bufferIDEX* bIE){
        int i = 0;
        bIE->addPc=0;
        bIE->ALUSrc=2;
        bIE->ALUOp=2;
        bIE->RegDst=2;
        bIE->Branch=2;
        bIE->MemWrite=2;
        bIE->MemRead=2;
        bIE->RegWrite=2;
        bIE->MemToReg=2;
        bIE->Readdata1=0;
        bIE->Readdata2=0;
        bIE->SignExtend=0;
        while(i<50){
            bIE->instruccion[i]='\0';
            if(i<5){
                bIE->Rs[i]='\0';
                bIE->Rt[i]='\0';
                bIE->Rd[i]='\0'; 
            }
            i++;
        }
        bIE->instruccion[0]='n';
        bIE->instruccion[1]='o';
        bIE->instruccion[2]='p';

        return bIE;
}

bufferEXMEM* exmenEnCero(bufferEXMEM* bEM){
    int i=0;
    bEM->Branch=2;
    bEM->MemWrite=2;
    bEM->MemRead=2;
    bEM->RegWrite=2;
    bEM->MemToReg=2;
    bEM->zero=0;
    bEM->ALUresult=0;
    bEM->Readdata2=0;
    bEM->addResult=0;
    while(i<50){
        bEM->instruccion[i]='\0';
        if (i<5){
            bEM->MuxRegDst[i]='\0';
        }
        i++;
    }   
    bEM->instruccion[0]='n';
    bEM->instruccion[1]='o';
    bEM->instruccion[2]='p';

    return bEM;
}

bufferMEMWB* memwbEnCero(bufferMEMWB* bMW){
        int i=0;
        bMW->RegWrite=2;
        bMW->MemToReg=2;
        bMW->Readdata=0;
        bMW->ALUresult=0;
        while(i<50){
        bMW->instruccion[i]='\0';  
            if (i<5){
                bMW->MuxRegDst[i]='\0';
            } 
            i++;
        }
        bMW->instruccion[0]='n';
        bMW->instruccion[1]='o';
        bMW->instruccion[2]='p';
    return bMW;
}

////////////////////////////////////////////////////////////////////////////
//////////////                detector de hazards           ////////////////
////////////////////////////////////////////////////////////////////////////

bufferIDEX* detectarHazard(bufferIDEX* bIE, bufferEXMEM* bEM, bufferMEMWB* bMW){

    int i = 1;
    int igualRs = 0;
    int igualRt = 0;
    int totalReg = 0;
    printf("INICIO PROGRAMA DETECTOR DE HAZARDS\n");
    //comparamos el buffer mem.wb con el buffer id.ex
    if (bMW->RegWrite==1){
        if (bMW->MuxRegDst[1]!='\0'){
            while(i<5){
                totalReg++;
                if (bMW->MuxRegDst[i]==bIE->Rs[i]){
                    igualRs++;
                }
                i++;
            }
            //si id.ex->rs == mem.wb->rd  
            if (igualRs==totalReg){
                printf("se descubrio un hazard en id.ex->rs == mem.wb->rd  \n");

                if (bMW->MemToReg==0){
                    bIE->Readdata1=bMW->ALUresult;
                }
                if (bMW->MemToReg==1){
                    bIE->Readdata1=bMW->Readdata;
                }
            }
            i=1;
            totalReg=0;
            igualRs=0;
            //vemos ahora con RT
            while(i<5){
                totalReg++;
                if (bMW->MuxRegDst[i]==bIE->Rt[i]){
                    igualRt++;
                }
                i++;
            }
            //si id.ex->rs == mem.wb->rd  
            if (igualRt==totalReg){
                printf("se descubrio un hazard en id.ex->rt == mem.wb->rd  \n");
                if (bMW->MemToReg==0){
                    bIE->Readdata2=bMW->ALUresult;
                }
                if (bMW->MemToReg==1){
                    bIE->Readdata2=bMW->Readdata;
                }
            }
            i=1;
            totalReg=0;
            igualRt=0;
        }   
    } 
    //comparamos el buffer ex.men con el buffer id.ex
    if (bEM->RegWrite==1){
        if (bEM->MuxRegDst[1]!='\0'){
            while(i<5){
                totalReg++;
                if (bEM->MuxRegDst[i]==bIE->Rs[i]){
                    igualRs++;
                }
                i++;
            }
            //si id.ex->rs == ex.mem->rd  
            if (igualRs==totalReg){
                printf("se descubrio un hazard en id.ex->rs == ex.mem->rd  \n");
                bIE->Readdata1=bEM->ALUresult;
            }
            i=1;
            totalReg=0;
            igualRs=0;
            //vemos ahora con RT
            while(i<5){
                totalReg++;
                if (bEM->MuxRegDst[i]==bIE->Rt[i]){
                    igualRt++;
                }
                i++;
            }
            //si id.ex->rt == ex.mem->rd  
            if (igualRt==totalReg){
                printf("se descubrio un hazard en id.ex->rt == ex.mem->rd  \n");
                bIE->Readdata2=bEM->ALUresult;
            }
            i=1;
            totalReg=0;
            igualRt=0;
        }   
    }   
   
    return bIE;
}

//realizar una espera en el pipeline
int espera(bufferIDEX* bIE, bufferEXMEM* bEM){
    int stall = 0;  //si hay q realizar una espera toma el valor de 1
    int igualRs = 0;
    int igualRt = 0;
    int totalReg = 0;
    int i=1;

    if (bEM->MemRead==1){
        if (bEM->MuxRegDst[1]!='\0'){
            while(i<5){
                totalReg++;
                if (bEM->MuxRegDst[i]==bIE->Rs[i]){
                    igualRs++;
                }
                i++;
            }
            //si id.ex->rs == ex.mem->rd  
            if (igualRs==totalReg){
                stall=1;
            }
            i=1;
            totalReg=0;
            igualRs=0;
            //vemos ahora con RT
            while(i<5){
                totalReg++;
                if (bEM->MuxRegDst[i]==bIE->Rt[i]){
                    igualRt++;
                }
                i++;
            }
            //si id.ex->rs == mem.wb->rd  
            if (igualRt==totalReg){
                stall=1;       
            }
            i=1;
            totalReg=0;
            igualRt=0;
           
        }


    }
    return stall;
}


////////////////////////////////////////////////////////////////////////////
//////////////            Imprimir buffer por archivo       ////////////////
////////////////////////////////////////////////////////////////////////////

//inprimir buffers en un archivo .html
void ImprimirBuffers(char* archivo, int ciclo, bufferIFID* bII, bufferIDEX* bIE,bufferEXMEM* bEM ,bufferMEMWB* bMW){

    FILE *fp;
    
    char cadena[100] = "<h1>Tabla buffers.</h1>\n";
    char inicioTabla[20] ="<TABLE BORDER>";
    char finTabla[10] ="</TABLE>";
    char tablaCabezera[200] = "<TR><TH>Ciclo</TH> <TH>IF/ID</TH> <TH>ID/EX</TH><TH>EX/MEM</TH><TH>MEM/WB</TH>";
    char tablaCabezera2[100] = " </TR>"; 
   
   fp = fopen ( archivo, "a" );

    if (ciclo==1){
        fprintf(fp, "%s", cadena);
        fprintf(fp, "%s", inicioTabla);
        fprintf(fp, "%s", tablaCabezera);
        fprintf(fp, "%s", tablaCabezera2);

    }

    fprintf(fp, "<TR><TD>C%d</TD>", ciclo);
    //if.id bufffer
    fprintf(fp, "<TD><dl><dt>%s</dt></dl> <ul><li>addPc: %d</li><li>%s </li></ul></TD>",bII->instruccion, bII->addPc,bII->instruccion);
     //id.ex bufffer
    fprintf(fp, "<TD><dl><dt>%s</dt></dl><ul><li>addPc: %d</li><li>ALUSrc: %d</li><li>ALUOp: %d</li><li>RegDst: %d</li><li>Branch: %d</li><li>MemWrite: %d</li><li>MemRead: %d</li>",bIE->instruccion,bIE->addPc,bIE->ALUSrc,bIE->ALUOp,bIE->RegDst,bIE->Branch,bIE->MemWrite,bIE->MemRead);
    fprintf(fp, "<li>RegWrite: %d</li><li>MemToReg: %d</li><li>Readdata1: %d</li><li>Readdata2: %d</li><li>SignExtend: %d </li>",bIE->RegWrite,bIE->MemToReg,bIE->Readdata1,bIE->Readdata2,bIE->SignExtend);
    fprintf(fp, "<li>Rs: %s</li><li>Rt: %s </li><li>Rd: %s </li></ul></TD> ", bIE->Rs,  bIE->Rt, bIE->Rd);
    //ex.mem bufffer
    fprintf(fp, "<TD><dl><dt>%s</dt></dl><ul><li>Branch: %d</li><li>MemWrite: %d</li><li>MemRead: %d</li><li>RegWrite: %d</li><li>MemToReg: %d</li><li>zero: %d</li><li>ALUresult: %d</li>",bEM->instruccion,bEM->Branch,bEM->MemWrite,bEM->MemRead,bEM->RegWrite,bEM->MemToReg,bEM->zero,bEM->ALUresult);
    fprintf(fp, "<li>Readdata2: %d</li><li>addResult: %d</li><li>MuxRegDst: %s </li></ul></TD>",bEM->Readdata2,bEM->addResult,bEM->MuxRegDst);
    //mem.wb buffer
    fprintf(fp, "<TD><dl><dt>%s</dt></dl><ul><li>RegWrite: %d</li><li>MemToReg: %d</li><li>Readdata: %d</li><li>ALUresult: %d</li><li>MuxRegDst: %s</li></ul></TD>   </TR>",bMW->instruccion,bMW->RegWrite,bMW->MemToReg,bMW->Readdata,bMW->ALUresult,bMW->MuxRegDst);

    fclose ( fp );

}

//cerrar la </tabla> del archivo html
void finImpresionBuffers(char* archivo){
    FILE *fp;
    char finTabla[10] ="</TABLE>";
    fp = fopen ( archivo, "a" );
    fprintf(fp, "%s", finTabla);

    fclose ( fp );
}
