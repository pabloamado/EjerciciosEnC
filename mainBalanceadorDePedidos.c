
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct {
    int id;
    int cantCiclos;
    char tipo[4];
}st_pedido;

typedef struct nodo {
    st_pedido pedido;
    struct nodo *ste;
    
}st_nodo;

typedef struct cola{
    st_nodo * fin;
    st_nodo * frente;
    int cantP;
}st_cola;

typedef struct listP {
    st_cola cola;
    struct listP *ste;
}st_listP;

void add(st_cola * cola, st_pedido pedido){
    st_nodo * nodo=(st_nodo*)malloc(sizeof(st_nodo));
    nodo->pedido=pedido;
    nodo->ste=NULL;
    
    if(cola->frente==NULL){
        cola->frente=nodo;
    }else{
          cola->fin->ste=nodo;
    }
    cola->fin=nodo;
}

st_pedido removes (st_cola * cola){
    st_nodo * aux=cola->frente;
    st_pedido pedido=aux->pedido;
    cola->frente=aux->ste;
    
    if(cola->frente==NULL){
        cola->fin=NULL;
    }
    free(aux);
    return pedido;
}

void leerPedido(st_pedido * pedido){
    printf("leeremos su pedido:\n");
    scanf("%d",&pedido->id);
    scanf("%d",&pedido->cantCiclos);
    scanf("%s",pedido->tipo);
    
}

st_listP * buscarNodoConMenosPedidos(st_listP * listP){
    st_listP * nodoBuscado=listP;
    st_listP * nodoMenor=NULL;
    nodoMenor=nodoBuscado;
    while(nodoBuscado!=NULL){
        
        if(nodoMenor->cola.cantP>nodoBuscado->cola.cantP){
            nodoMenor=nodoBuscado;
        }
        nodoBuscado=nodoBuscado->ste;
    }
    if(nodoMenor->cola.cantP==30){
        return NULL;
    } else{
        return nodoMenor;
    }
}

st_listP * insertNuevoServer(st_listP ** list){
    st_listP * nodo=(st_listP*)malloc(sizeof(st_listP));
    nodo->cola.fin=NULL;
    nodo->cola.frente=NULL;
    
    st_listP * listAux=*list;
    
    while(listAux!=NULL && listAux->ste!=NULL){
        listAux=listAux->ste;
    }
    if(listAux==NULL){
        *list=nodo;
    } else{
        listAux->ste=nodo;
    }
    return nodo;
}

void asignarPedido(st_listP ** listP, st_pedido pedido){
    
   st_listP * nodo=buscarNodoConMenosPedidos(*listP);
   if(nodo==NULL){
    nodo=insertNuevoServer(listP);
    add(&nodo->cola,pedido);
   }else{
     add(&nodo->cola,pedido);
   }
}

bool isEmpty(st_cola * cola){
    return cola->fin==NULL && cola->frente==NULL;
}
void despacharPedidos(st_cola * cola, int * cantCPU, int * mayorCantES){
    st_pedido pedido;
    int cantPES=0;
    int total=0;
    int ciclosES=0;
    while(!isEmpty(cola)){
        pedido=removes(cola);
             
        if(strcmp(pedido.tipo,"CPU")==0){
            *cantCPU=*cantCPU+1;
          
        }else{
            cantPES++;
             ciclosES=pedido.cantCiclos;
             if(*mayorCantES<ciclosES){
                 *mayorCantES=ciclosES;
             }
        }
        total=*cantCPU+cantPES;
        printf(" porc de procesos CPU: %d\n",(*cantCPU*100)/total);
        printf(" porc de procesos E/S: %d\n",(cantPES*100)/total);
    }
}
void procesarServidores(st_listP * lista, st_listP ** nodoCPU, st_listP ** nodoES){
    st_listP * listA=lista;
    int mayorCantCPU=0;
    int cantCPU=0;
    int mayorPESNodo=0;
    int mayorESTotal=0;
    *nodoCPU=listA;
    *nodoES=listA;
    while(listA!=NULL){
        
         despacharPedidos(&listA->cola,&cantCPU,&mayorPESNodo); //DESPACHO LA COLA DEL PRIMER NODO SERVER
         
         if(cantCPU>mayorCantCPU){
             mayorCantCPU=cantCPU;
             *nodoCPU=listA;
         }
         if(mayorPESNodo>mayorESTotal){
             mayorESTotal=mayorPESNodo;
             *nodoES=listA;
         }
        
     listA=listA->ste;   
    }
      
            
}
int main(int argc, char** argv) {
    st_pedido pedido;
    st_listP * listP=NULL;
    listP->cola.fin=NULL;
    listP->cola.fin=NULL;
    st_listP * nodoMayorCPU=NULL;
    st_listP * nodoMayorES=NULL;
    int option=-1;
    // LLENAR ACA EL LISTADO CON AL MENOS 3 SERVIDORES
    printf("Ingrese sus pedidos:\n");
    printf("Ingrese un num distinto de 0 para que leamos sus pedidos. Ingrese 0 para terminar\n");
    scanf("%d",&option);
    while(option!=0){
   
        leerPedido(&pedido);
    
        asignarPedido(&listP,pedido);
        printf("ingrese nuevamente un num\n");
        scanf("%d",&option);
    }
    
    procesarServidores(listP,&nodoMayorCPU, &nodoMayorES);
    
    
    
    return (EXIT_SUCCESS);
}

