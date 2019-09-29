/*
 un satelite envia perdiodicamente una secuencia de 250 numeros a un estacion terrena para que esta pueda procesar el flujo y 
 * emplearlo para anaalizar el cambio climatico.
 * las ondas llegan a la antena y la transmiten hast un equipo informatico en el que se encuentra corriendo un aplicacion,
 * la aplicacion controla la integridad de la cadena e invoca a la funcion justdolt() que recibe como parametro el puntero
 * a la secuencia de 250 numeros. la funcion se encarga de gurdar en un archivo de texto los datos que se encuentran
 * encapsulados en las distintas tramas que componen la secuencia
 * trama 1
 * encabezado:9
 * largo : 03 (2 digitos siguientes al 9)
 * mensaje:123 
 * control de redundancia: 2 digitos desp del msj(debe dr igual que la suma del msj)
 * guardar los datos separados por coma y si redundancia no coincide con la suma escribir error en<numero de trama>
 */
/*
#include <stdio.h>
#include <stdlib.h>

void initWord(char * linea){
   for(int i=0;i<34;i++){ //aca se  le deberia pasar la long de la cadena
       *(linea+i)='\0';
       //linea++; // si es char * const no funciona
   } 
    
}
void funcionLargo ( const char * linea, int * largoMsj, int * posiciones){
    char longitud[2];
    *posiciones=0;
    for(int i=0;i<2;i++){
    longitud[i]=*(linea + i);
   *posiciones=*(posiciones)+1;
    }
    *(largoMsj)=atoi(longitud);
}
int obtenerMensaje( const char * linea, int largo){
    
    char mensaje[largo];
    for(int i=0;i<largo;i++){
        mensaje[i]=*linea;
           linea++;  
           
    }
    
  return atoi(mensaje); 
}
 void leerRed( const char * linea, int * redundanciaDada, int *posiciones){
    *(posiciones)=0;
    char numero[2];
    for(int i=0;i<2;i++){
      numero[i]=*(linea+i);
      *(posiciones)=*(posiciones)+1;  
    } // la posicion devuelta me posiciona sobre el prox 9
    *(redundanciaDada)=atoi(numero);
    
}
void calRed( const char * linea, int largoMsj, int * redundancia){
    int i=0;
    char letra='0';
    while(i<largoMsj){
        letra=*linea;
         *(redundancia)+=atoi(&letra);   
        linea++;
        i++;
    } 
    
}
void guardarTramas (const char * linea){
    int mensaje=0;
    int trama=0;
    int largoMsj=0;
    int redundanciaCalculada=0;
    int redundanciaDada=0;
    int posiciones=0;
     FILE * textoDestino=fopen("destino.txt","r+");
     if(textoDestino==NULL){
         printf("error al abrir archivo de texto");
         exit(EXIT_FAILURE);
     }
    while(*linea!='\0'){
        posiciones=0;
        redundanciaCalculada=0;
        
        if(*linea=='9'){ //PRIMER POSICION
           trama++; 
           linea++;
           funcionLargo(linea,&largoMsj,&posiciones); // AVANZO HASTA POSICIONARME EN 1 POS DEL MSJ obtengo el largo del msj
           
           linea+=posiciones;// estoy parado sobre la primer pos del msj // avanzo 2 posiciones
           
           mensaje=obtenerMensaje(linea,largoMsj);
           
           calRed(linea,largoMsj,&redundanciaCalculada);//RECORRO X largo del msj para l redundancia
           
           posiciones=largoMsj; // posiciones = cnt de pos  de info
           
           linea+=posiciones; // estoy parado sobre el 1er digito de la redundancia
           
           leerRed(linea,&redundanciaDada,&posiciones);
           
           linea+=posiciones; // estoy paarado sobre el prox 9
            
                if(redundanciaCalculada!=redundanciaDada){
                    fprintf(textoDestino,"error en trama<%d>",trama); 
               
                  } else{
                            fprintf(textoDestino,"trama:%d,9,%d,%d,%d",trama,largoMsj,mensaje,redundanciaCalculada); 
                           
                        }
        }
    }
     fclose(textoDestino);
}

int main(int argc, char** argv) {

    FILE * textoOrigen=fopen("cadNum.txt","r");
   if (textoOrigen==NULL){
       printf("error en archivo fuente");
       exit(EXIT_FAILURE);
   }
    char *linea=(char*)malloc(sizeof(char)*34);
    
    initWord(linea);
   
    fgets(linea,35,textoOrigen);
    
    printf("%s\n",linea);
    
    guardarTramas(linea);
    
    fclose(textoOrigen);
    
    return (EXIT_SUCCESS);
}

/*