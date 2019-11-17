
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo{
    int valor;
    struct nodo*ste;
}st_nodo;

typedef struct {
    st_nodo *frente;
    st_nodo *fin;
}st_cola;

void push(st_nodo ** pila, int valor){
    st_nodo* nodo=(st_nodo*)malloc(sizeof(st_nodo));
    nodo->valor=valor;
    nodo->ste=NULL;
    nodo->ste=*pila;
    *pila=nodo;  
}
int pop(st_nodo ** pila){
    int valor=(*pila)->valor;
    st_nodo *aux=*pila;
    *pila=(*pila)->ste;
    free(aux);
    return valor;
}

void add(st_cola *cola, int valor){
    st_nodo * nodo=(st_nodo*)malloc(sizeof(st_nodo));
     nodo->valor=valor;
     nodo->ste=NULL;
     if(cola->frente==NULL){
         cola->frente=nodo;
     }else{
         cola->fin->ste=nodo;
     }
     cola->fin=nodo;
}

int removes(st_cola * cola){
    st_nodo * aux=cola->frente;
    int valor=aux->valor;
    cola->frente=aux->ste;
    if(cola->frente==NULL){
        cola->fin=NULL;
    }
    free(aux);
    return valor;
}
bool isEmpty(st_cola* cola){
    return cola->fin==NULL && cola->frente==NULL;
}

void generarPila(st_cola * cola1,st_cola * cola2, st_nodo ** pila){
    st_nodo *pilaAux=NULL;
    
    while(!isEmpty(cola1)){ // LLENA
        push(&pilaAux,removes(cola1));
    }
    while(pilaAux!=NULL){
        push(pila,pop(&pilaAux));
    }
    while(!isEmpty(cola2)){
        push(pila,removes(cola2));
    }
    
}

int main(int argc, char** argv) {
    st_nodo * pila=NULL;
    st_cola colA;
    st_cola colB;
    colA.fin=NULL;
    colA.frente=NULL;
    colB.fin=NULL;
    colB.frente=NULL;
    
    for(int i=1;i<=5;i++){
        add(&colA,i);
    }
    for(int i=6;i<=10;i++){
        add(&colB,i);
    }
    
    generarPila(&colA,&colB,&pila);
    
    while(pila!=NULL){
        printf("%d\n",pop(&pila));
    }
    
    return (EXIT_SUCCESS);
}
