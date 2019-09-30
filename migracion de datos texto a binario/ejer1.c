/*
Una empresa familiar decide informatizarse 
y desean migrar los datos que la empresa posee acerca de sus clientes; estos se hayan almacenados en un archivo de texto 
y deben migrarse a un archivo binario. Cada registro ocupa un renglón y se compone por el nombre, el apellido y el dni del cliente;
los campos están separados por coma. El archivo puede contener duplicados, es decir, varias ocurrencias para una misma combinación 
de campos. Implementar un algoritmo que grabe los datos al archivo binario considerando que los duplicados no deben 
 guardarse en el archivo binario (no debe sobreescribirse un registro existente, tampoco eliminarlo y volver a insertarlo) 
y que debe mostrarse en pantalla la cantidad de registros netos migrados, y cuáles fueron los registros duplicados y sus ocurrencias.
Usar punteros para identificar los campos... nada de strtok.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PALABRA 60

typedef struct{
    char nombre[20];
    char apellido[20];
    char dni[9];
}ST_CLIENTE;

 void copiarNombre(const char * linea, ST_CLIENTE * cliente ,int * pos){
     *pos=0;
     int i=0;
     while(*linea!=','){
         cliente->nombre[i]=*linea;
         *pos=*(pos)+1;
         linea++;
         i++;
     }
     *pos=*(pos)+1;
 }
   void copiarApellido(const char * linea, ST_CLIENTE * cliente ,int * pos){
       linea+=*pos;
       int i=0;
        while(*linea!=','){
         cliente->apellido[i]=*linea;
         *pos=*(pos)+1;
         linea++;
         i++;
     }
     *pos=*(pos)+1;
        
    }
  void  copiarDni(const char * linea,ST_CLIENTE * cliente, int * pos){
      linea+=*pos;
      int i=0;
     while(*linea!='\0'){
         cliente->dni[i]=*linea;
         *pos=*(pos)+1;
         linea++;
         i++;
     }
     *pos=*(pos)+1;
        
    }


void inicializarCliente( ST_CLIENTE *cliente){
    
    for(int i=0;i<20;i++){
     cliente->nombre[i]='\0';
     cliente->apellido[i]='\0';
    }
    
    for(int i=0;i<9;i++){
        cliente->dni[i]='\0';
    }
}


void guardarDatosEnEstructura(const char * linea,ST_CLIENTE * cliente){
    int pos=0;
    
    copiarNombre(linea, cliente,&pos); //pos =6
    
    copiarApellido(linea,cliente,&pos); // pos= 12
    
    copiarDni(linea, cliente,&pos); // pos va  a caer sobre el digito del dni
        
    
}
void inicializarBinario(ST_CLIENTE* cliente, FILE* archivoBinario){
    
    for(int i=0;i<40;i++){
        fwrite(cliente,sizeof(ST_CLIENTE),1,archivoBinario);
    }
    
    fseek(archivoBinario,0,SEEK_SET);
}
void imprimirArchivosBinarios(FILE * archivoBin){
    ST_CLIENTE client;
    fseek(archivoBin,0,SEEK_SET);
    fread(&client,sizeof(ST_CLIENTE),1,archivoBin);
    while(!feof(archivoBin)){
        
        printf(" %s ",client.nombre);
        printf(" %s ",client.apellido);
        printf(" %s \n",client.dni);
        fread(&client,sizeof(ST_CLIENTE),1,archivoBin);
    }
    
}

int main(int argc, char** argv) {
    int duplicado=0;
    int cantDuplicados=0;
    int regMigrados=0;
    ST_CLIENTE cliente;
    ST_CLIENTE aux;
    inicializarCliente(&cliente);
    inicializarCliente(&aux);
   
    FILE * archivoTexto=NULL;
    
    FILE * archivoBinario=NULL;
    
    FILE * archivoDuplicados=NULL;
    
    char * linea=(char*)malloc(sizeof(char)* PALABRA); //creamos la cadena que levanta el reglon
    memset(linea,'\0',sizeof(char)*PALABRA);
    
    archivoTexto=fopen("clientesDatos.txt","r");
    
    archivoBinario=fopen("datosC.bin","r+b");
    if(archivoBinario==NULL){
        printf("error al abrir archivo\n");
        exit(EXIT_FAILURE);
    }
    archivoDuplicados=fopen("duplicados.bin","r+b");
    
     inicializarBinario(&cliente,archivoBinario);
     inicializarBinario(&cliente,archivoDuplicados);
       fgets(linea,25,archivoTexto);   
    while(!feof(archivoTexto)){ // LEO CADA LINEA HASTA EL FIN DEL ARCHIVO TEXTO
        duplicado=0;  // LO SETEO EN FALSO NUEVAMENTE
        guardarDatosEnEstructura(linea,&cliente); //GUARDO LOS DATOS EN STRUCT CLIENTE
        
        fread(&aux,sizeof(ST_CLIENTE),1,archivoBinario); // AHORA DEPOSITO DATOS EN AUX DEL ARCHIVO BIN
        
        while(!feof(archivoBinario) && duplicado==0){ 
                      // RECORRO EL ARCHIVO BIN PREG SI STRUCT CLIENTE YA ESTA ESCRITO
            if( cliente.dni==aux.dni){
                duplicado=1;
                cantDuplicados++;
                fwrite(&cliente,sizeof(ST_CLIENTE),1,archivoDuplicados); //SI ES DUPLICADO LO GUARDO EN ARCHIVO DUPLICADOS
            }  
                
            fread(&aux,sizeof(ST_CLIENTE),1,archivoBinario); 
        }
         
        if(duplicado==0){//SIGNIFICA QUE NO ESTA DUPLICADO Y LO ESCRIBE
            
            fwrite(&cliente,sizeof(ST_CLIENTE),1,archivoBinario); 
            regMigrados++;
        }
        
        fseek(archivoBinario,0,SEEK_SET); // FINALMENTE VUELVO AL INICIO DEL ARCHIVO BIN PARA  RECORRERLO DE NUEVO
      fgets(linea,25,archivoTexto);
    }
    
     printf("registros de clientes:\n");
   
   imprimirArchivosBinarios(archivoBinario);
   
   printf("registros duplicados:\n");
   
   imprimirArchivosBinarios(archivoDuplicados);
   
   fclose(archivoBinario);
   
   fclose(archivoDuplicados);
   
   fclose(archivoTexto);
   
    return (EXIT_SUCCESS);
    
    
}
