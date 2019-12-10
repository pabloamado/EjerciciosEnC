
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodoP{
    char letra;
    struct nodoP *ste;
}st_pilaLista;



void push (st_pilaLista ** pila, char letra){
    st_pilaLista * nodo=(st_pilaLista*)malloc(sizeof(st_pilaLista));
    nodo->letra=letra;
    nodo->ste=NULL;
    nodo->ste=*pila;
    *pila=nodo;
}

char pop (st_pilaLista ** pila){
    char letra=(*pila)->letra;
    st_pilaLista * aux=*pila;
    *pila=(*pila)->ste;
    free(aux);
    return letra;
}

bool esPalindromo (st_pilaLista ** p1, st_pilaLista** p2){
    st_pilaLista * pilaAux=NULL;
    bool esPalindromo=true;
    
    while(*p1!=NULL){
        push(&pilaAux,pop(p1));
    }
    
    while(pilaAux!=NULL && *p2!=NULL){
        
        if(pop(p2)!=pop(&pilaAux)){
            esPalindromo=false;
        }
    }
    
    while(pilaAux!=NULL){
        pop(&pilaAux);
    }
    while(*p2!=NULL){
        pop(p2);
    }
    
    return esPalindromo;
    
}
st_pilaLista * insertAlFinal (st_pilaLista ** list, char letra){
    st_pilaLista * nodo=(st_pilaLista*)malloc(sizeof(st_pilaLista));
    nodo->letra=letra;
    nodo->ste=NULL;
    
    st_pilaLista * listA=*list;
   
    while(listA!=NULL && listA->ste!=NULL){
        listA=listA->ste;
        
    }
    if(listA==NULL){
        *list=nodo;
    } else{
        listA->ste=nodo;
    }
    return nodo;
}

void inicializarListas(st_pilaLista ** vector){
    
    for(int i=0;i<10;i++){
        vector[i]=NULL;
    }
}
void insertarPalabraEnLista(st_pilaLista ** list, const char * linea){
    
    while(*linea!='\0'){
        insertAlFinal(list,*linea);
        linea++;
    }
}
void cargarPalabras(st_pilaLista ** vector){
    char * linea=(char*)malloc(sizeof(char)*50);
    int i=0;
    
    while(i<10){
     memset(linea,'\0',50);   
     printf("ingrese una palabra\n");   
     gets(linea);
        
     insertarPalabraEnLista(&vector[i],linea);   
     i++;   
    }
    free(linea);
}
int main(int argc, char** argv) {
    
    st_pilaLista * pila1=NULL;
    st_pilaLista * pila2=NULL;
    st_pilaLista * listAux;
    st_pilaLista * vector[10]; //  YA CARGADAS LAS LISTAS
    inicializarListas(vector);
    cargarPalabras(vector);
    for(int i=0;i<10;i++){
     
        listAux=vector[i];
        
        while(listAux!=NULL){
            
            push(&pila1,listAux->letra);
            push(&pila2,listAux->letra);  
            listAux=listAux->ste; 
        }
         
        if(esPalindromo(&pila1,&pila2)){
            
            printf("la palabra almacenda en la posicion %d del vector es palindromo\n",i);
        }
   
    }
    
    
    return (EXIT_SUCCESS);
}

