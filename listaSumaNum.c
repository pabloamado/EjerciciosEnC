
/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct nodoL{
    int valor;
    struct nodoL *ste;
}st_nodoL;

st_nodoL * crearNodo(int valor){
    st_nodoL *nodo=(st_nodoL*)malloc(sizeof(st_nodoL));
    nodo->valor=valor;
    nodo->ste=NULL;
    return nodo;
}///////////////////////////////////////////////////////
int deleteFirst (st_nodoL ** lista){
    int valor=(*lista)->valor;
    st_nodoL *aux=*lista;
    *lista=(*lista)->ste;
    free(aux);
            
   return valor; 
}
st_nodoL *insertEnFrente(st_nodoL **lista,int valor){
    st_nodoL *nodo=crearNodo(valor);
    nodo->ste=*lista;
    *lista=nodo;
    return nodo;
}
void imprimirLista(st_nodoL *lista){
    while(lista!=NULL){
        printf("cifra:%d\n",lista->valor);
        lista=lista->ste;
    }
}
int calcularLongitud(st_nodoL *lista){
    int longitud=-1;
    while(lista!=NULL){
        lista=lista->ste;
        longitud++;
    }
    return longitud;
}
int calcularNum(st_nodoL*lista,int * potencia){
    *potencia=0;
    int result=0;
    while(lista!=NULL){
        result=result+(lista->valor * pow(10,(*potencia) ));
        *potencia=*potencia+1;
        lista=lista->ste;    
    }
    *potencia=*potencia-1;
    printf("result dentro de funcion:%d\n",result);
    return result;
}

void insertarSumaEnLista(st_nodoL ** lista,int potenciaMax,int numero){
    int resultado=0;
    int residuo=-1;
   
   
    while(potenciaMax>=0 && residuo!=0){
                      // POR LO QUE VOY A DIVIDIR
        residuo= numero %(int)pow(10,potenciaMax); //CHEQUEO SIEMPRE QUE NO SEA 0
        
        resultado= numero/(int)pow(10,potenciaMax);
        numero=numero-(pow(10,potenciaMax)*resultado);
       
        insertEnFrente(lista,resultado);
        potenciaMax--;
    }
}
int main(int argc, char** argv) {
    int longitud=0;
    int num1=0;
    int num2=0;
    int suma=0;
    int longMayor=0;
    st_nodoL *lista1=NULL;
    st_nodoL *lista2=NULL;
    st_nodoL *listaR=NULL;
    insertEnFrente(&lista1,2);
    insertEnFrente(&lista1,5);
    insertEnFrente(&lista1,6);
    
    insertEnFrente(&lista2,4);
    insertEnFrente(&lista2,6);
    insertEnFrente(&lista2,8);
    
    num1=calcularNum(lista1,&longitud);
    
    longMayor=longitud;

    num2=calcularNum(lista2,&longitud);
    
    if(longitud>longMayor){
        longMayor=longitud;
    }
    suma=num1+num2;
    printf("suma de los 2 num:%d\n",suma);
    
    insertarSumaEnLista(&listaR,longMayor,suma);
    
    imprimirLista(listaR);

    return (EXIT_SUCCESS);
}

*/