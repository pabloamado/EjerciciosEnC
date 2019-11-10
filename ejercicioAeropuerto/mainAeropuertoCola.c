/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 80

typedef struct{
    int pasajeros;
    char modelo [12];
    char codigo [6];
    int posIng;
    int posEgreso;
}st_avion;

typedef struct nodo {
    st_avion avion;
    int pos;
    struct nodo * ste;
    
    
}st_nodo;
  ///////////////////////////////////////////////////
st_avion crearAvion(st_avion * avion){
   
    avion->pasajeros=0;
    avion->posIng=-1;
    avion->posEgreso=-1;
    memset(avion->codigo,'\0',6);
    memset(avion->modelo,'\0',12);
 
}
///////////////////////////////////////////////////////
void obtenerPalabra(const char *linea, char * const palabra, int * indice){
    int i=0;
    while(*linea  && *linea!='.' && *linea!=',' ){
        *(palabra+i)= *linea;
        linea++;
        i++;
        *indice=*indice+1;
    }
    *indice=*indice+1;
} 
////////////////////////////////////////////////
int isEmpty(st_nodo * pila){
    return pila==NULL;
}

st_avion pop(st_nodo ** pila){
    st_avion avion=(*pila)->avion;
     st_nodo * aux=*pila;
    *pila=(*pila)->ste;
    free(aux);
   // (*pila)->pos--;
    return avion;
    
}

void push(st_nodo ** pila, st_avion avion){
    
    st_nodo * nodo=(st_nodo*)malloc(sizeof(st_nodo));
    nodo->avion=avion;
    nodo->ste=NULL;
    
    nodo->ste=*pila;
    *pila=nodo;
    (*pila)->pos++;
}
//////////////////////////////////////////////////////////////////
void configurarAvion ( const char* linea,st_avion * avion){
    int i=0;
    int indice=0;
    char * palabra=(char*)malloc(sizeof(char)*MAX);
    
    while(*linea!='\0'){
        i++; 
        indice=0;
        memset(palabra,'\0',MAX);
        obtenerPalabra(linea,palabra,&indice);
        
        if(i==1){
            strcpy(avion->modelo,palabra);
        } else if(i==2){
            strcpy(avion->codigo,palabra);
        } else if(i==3){
            avion->pasajeros=atoi(palabra);
        }
        linea=linea+indice;
    }
  
}

void guardarEnBinario(st_avion * avion){
    
    FILE * archivoBin=NULL;
    archivoBin=fopen("despegues.bin","a+b");
    if(archivoBin==NULL){
       exit(EXIT_FAILURE);
    }
    
    fwrite(avion,sizeof(st_avion),1,archivoBin);
  
    fclose(archivoBin);
}

void posicionarAvion(st_nodo ** pila, st_avion *avion){
         int encontrado=0;
         st_avion avionAux;
         st_nodo * pilaAux=NULL;
        

 
         if(*pila==NULL){
             push(pila,*avion);
             
         } else{
              
            if(strcmp(avion->modelo,"rande")==0){
                while(!isEmpty(*pila)){
                   avionAux=pop(pila);
                 if( !encontrado && (strcmp(avionAux.modelo,"rande")==0) ){
                     push(&pilaAux,*avion);
                     push(&pilaAux,avionAux);     
                     encontrado=1;
                     } else{  
                        push(&pilaAux,avionAux);
                          }
                }    
            } else if( strcmp(avion->modelo,"pichitito")==0){
                 
                while(!isEmpty(*pila)){
                  avionAux=pop(pila);
                 if( !encontrado && ( strcmp(avionAux.modelo,"rande")==0 || strcmp(avionAux.modelo,"pichitito")==0  )  ){
                     push(&pilaAux,*avion);
                     push(&pilaAux,avionAux);     
                     encontrado=1;
                    } else{  
                        push(&pilaAux,avionAux);
                        }
                }   
                 
            } else{
            
            push(pila,*avion);
                    
            }
           
            while(!isEmpty(pilaAux)){
                
            push(pila,pop(&pilaAux)); 
            
            }
       }// FIN ELSE
 }   
////////////////////////////////////////////////////////////////////

void procesarArribos (FILE * arribos, st_nodo ** pila, st_avion* avion){
    int pos=0;
    arribos=fopen("arribos.txt","r");
    if(arribos==NULL){
        exit(EXIT_FAILURE);
    }
    
    char * linea=malloc(sizeof(char)*MAX);
    memset(linea,'\0',MAX);
    
    while(fgets(linea,MAX,arribos)!=NULL){
        
        configurarAvion(linea, avion);
        
        pos++;
        
        avion->posIng=pos;
        
        guardarEnBinario(avion);
        
        posicionarAvion(pila,avion);
                   
    }
       
}
void actualizarBinario(st_avion avion){
    FILE * despegues=NULL;
    despegues=fopen("despegues.bin","a+b");
            
    if(despegues==NULL){
        exit(EXIT_FAILURE);
    }
    fseek(despegues,sizeof(st_avion)*avion.posIng,SEEK_SET);
    fwrite(&avion,sizeof(st_avion),1,despegues);
    
    fclose(despegues);
}

///////////////////////////////////////////////////////
void realizarDespegues (st_nodo **pila){
    st_avion avion;
    st_nodo * pilaAux=NULL;
    pilaAux->pos=0;
    
    while(!isEmpty(*pila)){
        push(&pilaAux,pop(pila));
    }
    
    while(!isEmpty(pilaAux)){
      avion=pop(&pilaAux);
      avion.posEgreso=pilaAux->pos;
        actualizarBinario(avion);
    }
    
}
///////////////////////MAIN//////////////////////////////
int main(int argc, char** argv) {
    FILE * archivoA=NULL;
    FILE * archivoD=NULL;
    st_nodo * pilaAv=NULL;
   
    
    
    st_avion * avion;
    crearAvion(avion); 
    procesarArribos(archivoA,&pilaAv,avion);
    
    realizarDespegues(&pilaAv);
    
    
    st_avion aux;
    archivoD=fopen("despegues.bin","r+b");
    
    
    fread(&aux,sizeof(st_avion),1,archivoD);
    while(!feof(archivoD)){
        printf("modelo:%s\n",aux.modelo);
         printf("codigo %s\n",aux.codigo);
          printf("cnt pasajeros: %d\n", aux.pasajeros);
           printf("pos ing: %d\n",aux.posIng);
            printf("pos egreso:\n",aux.posEgreso);
       fread(&aux,sizeof(st_avion),1,archivoD);
    }
    
    

    return (EXIT_SUCCESS);
}

*/