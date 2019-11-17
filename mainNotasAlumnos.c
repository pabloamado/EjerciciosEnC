

#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int leg;
    int nota;
}st_aprobado;

typedef struct {
    int leg;
    int fecha;
    int presencia;
}st_asistencias;

typedef struct nodoLA{
    int presente;
    int fecha;
    struct nodoLA *ste;
}st_listAsist;

typedef struct nodoL{
    int leg;
    int prom;
    st_listAsist * asistencias;
    struct nodoL * ste;
}st_listProm;

int calcularPorcAsist(st_listAsist *lista){// ME DARIA LA CANT DE ASISTENCIAS DE LA LISTA DE CADA ALUMNO
    int cantClases=0;
    int asistencias=0;
    while(lista!=NULL){
        cantClases++;
        if(lista->presente==1){
            asistencias++;
        }
        cantClases++;
   }
   return asistencias;
}

st_listAsist *insertOrdenadoAsist(st_listAsist ** lista, st_asistencias asistAlum){
    st_listAsist * nodo=(st_listProm*)malloc(sizeof(st_listProm));
    nodo->presente=asistAlum.presencia;
    nodo->fecha=asistAlum.fecha;
    nodo->ste=NULL;
    st_listAsist *listAux=*lista;
    st_listAsist * nodoAnt=NULL;
    while(listAux!=NULL && listAux->fecha>asistAlum.fecha){
        nodoAnt=listAux;
        listAux=nodoAnt->ste;
    }
    if(nodoAnt==NULL){
        *lista=nodo;
    }else{
        nodoAnt->ste=nodo;
    }
    nodo->ste=listAux; 
    
    return nodo;
}
st_listProm * search(){
    
}
int main(int argc, char** argv) {
    int leg=0;
    st_asistencias asistencia;
    st_aprobado aprobado;
    st_listProm *listaPromocionados=NULL;
    st_listProm *aux=NULL;
    listaPromocionados->asistencias=NULL;
    FILE * asistencias=NULL;
    FILE * notasAprob=NULL;
    FILE * promocionados=NULL;
   asistencias=fopen("asistencias.bin","rb");
   notasAprob=fopen("notasAprob.bin","rb");
   promocionados=fopen("promocionados.bin","r+b");
   
  st_listProm * listAux=aprobado;
  
   fread(&asistencia,sizeof(st_asistencias),1,asistencias);
   
   while(!feof(asistencias)){// ARCHIVO ORDENADO POR LEGAJO POR LO TANTO PUEDO HACER UN CORTE DE CONTROL
       leg=asistencia.leg;
       listAux->leg=leg;
       while(!feof(asistencias) && leg==asistencia.leg){// MIENTRAS SEA EL MISMO LEGAJO LLENO LAS ASISTENCIAS DEL ALUMNO
             insertOrdenadoAsist(listAux->asistencias,asistencia);
              
             fread(&asistencia,sizeof(st_asistencias),1,asistencias);
       }
       
      listAux=listAux->ste;  
   }
  
   
   fread(&aprobado,sizeof(st_aprobado),1,notasAprob);
   
   while(!feof(notasAprob)){
    aux=insertSinDuplicados(&listaPromocionados,aprobado);
     
    aux->prom=aux->prom+ aprobado.nota;
    
    fread(&aprobado,sizeof(st_aprobado),1,notasAprob);   
   }
  
  
    
    return (EXIT_SUCCESS);
}

