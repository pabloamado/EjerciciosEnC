
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct nodo{
    char letra;
    struct nodo*ste;
}st_nodo;

void push(st_nodo ** head, char letra){
    st_nodo * nodo=(st_nodo*)malloc(sizeof(st_nodo));
    nodo->letra=letra;
    nodo->ste=NULL;
    nodo->ste=*head;
    *head=nodo; 
}  
char pop (st_nodo**pila){
    char letra=(*pila)->letra;
    st_nodo * aux=*pila;
    *pila=(*pila)->ste;
    return letra;
}
void lineaAPila(const char* linea,st_nodo **pila){
    
    while(*linea!='\0' &&*linea!='\n' && *linea!='\r'){
        push(pila,*linea);
        linea++;
    }
}
bool esPalindromo(st_nodo**pila, st_nodo** aux1){
    
    bool esPalindromo=true;
    st_nodo * aux2=NULL;
    while(*aux1!=NULL){
        push(&aux2,pop(aux1));
    }
    while(*pila!=NULL && esPalindromo==true){
         
         
        if(  pop(pila)!= pop(&aux2)){
            esPalindromo=false;
        }
    }
    return esPalindromo;
}

int main(int argc, char** argv) {
    st_nodo *pila1=NULL;
    st_nodo *pila2=NULL;
    FILE* archPalabras=NULL;
    FILE* archNoPalindromos=NULL;
    char *linea=(char*)malloc(sizeof(char)*15);
    memset(linea,'\0',15);
    archPalabras=fopen("palabras.txt","r");
    archNoPalindromos=fopen("noPalindromos.txt","r+");
    
    while(fgets(linea,16,archPalabras)!=NULL){
        lineaAPila(linea,&pila1);
        lineaAPila(linea,&pila2);
        
        if(esPalindromo(&pila1,&pila2)==false){
                fprintf(archNoPalindromos,"%s",linea);  
        }  
        while(pila1!=NULL){
            pop(&pila1);
        }
    }
    
    fclose(archNoPalindromos);
    fclose(archPalabras);
    
    return (EXIT_SUCCESS);
}

