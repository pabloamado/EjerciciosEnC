

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LONG_FRASE 80

typedef struct {
    int hora;
    float humMin;
    float humMax;
    float humProm;
    float humAcum;
    float cant;
} st_Medicion;

void obtenerHoraHumedad(char *linea, int *hora, float *humedad) {
    char marca = ';';
    int cont = 0;
    char *horario;
    const char *token;

    token = strtok(linea, &marca);

    while (token != NULL) {
        cont++;
        if (cont == 3) {
            strncpy(horario, token, 2);
            *hora = atoi(horario);
        }
        if (cont == 5) {
            *humedad = atof(token);
        }

        token = strtok(NULL, &marca);

    }

}

void inicializarBinario(FILE * binario) {
    st_Medicion medicion;
    medicion.hora = -1;
    medicion.humMax = -1;
    medicion.humMin = 100;
    medicion.humProm = 0;
    medicion.humAcum = 0;
    medicion.cant = 0;
    for (int i = 0; i < 24; i++) {
        fwrite(&medicion, sizeof (st_Medicion), 1, binario);
    }
}

void calcularHumedadProm(FILE * binario) {
    fseek(binario, 0, SEEK_SET);
    st_Medicion medicion;
    for (int i = 0; i < 24; i++) {
        fread(&medicion, sizeof (st_Medicion), 1, binario);
        medicion.humProm = medicion.humAcum / medicion.cant;
        fseek(binario, sizeof (st_Medicion) * i, SEEK_SET);
        fwrite(&medicion, sizeof (st_Medicion), 1, binario);
    }
}

void actualizarMedicion(st_Medicion *medicion, int hora, float humedad) {
    if (medicion->hora == -1) {
        medicion->hora = hora;
    }
    if (humedad > medicion->humMax) {
        medicion->humMax = humedad;
    }
    if (humedad < medicion->humMin) {
        medicion->humMin = humedad;
    }
    medicion->cant++;
    medicion->humAcum += humedad;
}
 
void imprimirBinario(FILE * binario){
    st_Medicion medFinal;
    binario=fopen("binario.bin", "rb");
    if(binario==NULL){
        printf("Error al intentar abrir de nuevo el archivo binario");     
    }
    for (int i = 0; i < 24; i++) {
        fread(&medFinal,sizeof(st_Medicion),1,binario);
        
        printf("hora: %d \n",medFinal.hora);
        printf("humedad maxima %.6f \n",medFinal.humMax);
        printf("humedad min;%.6f \n", medFinal.humMin );
        printf("humedad prom: %.6f \n", medFinal.humProm);
        
    }
}


int main(int argc, char** argv) {
    int hora = 0;
    float humedad = 0;
    char linea [LONG_FRASE];
    st_Medicion med;

    memset(linea, '\0', LONG_FRASE);
    FILE *archivoBin = NULL;
    FILE *archivoTxt = NULL;
    archivoBin = fopen("binario.bin", "w+b"); // ABRO CON EL + PORQUE SINO TIRA ERROR
    archivoTxt = fopen("texto.txt", "r+");
    if (archivoTxt == NULL) {
        printf("Error al abrir archivo texto");
        exit(EXIT_FAILURE);
    }
    if ( archivoBin == NULL) {
        printf("Error al abrir archivo binario");
        exit(EXIT_FAILURE);
    }
    inicializarBinario(archivoBin);

    fgets(linea, 50, archivoTxt);
    while (!feof(archivoTxt)) {

        obtenerHoraHumedad(linea, &hora, &humedad);

        fseek(archivoBin, sizeof (st_Medicion) * hora, SEEK_SET);

        fread(&med, sizeof (st_Medicion), 1, archivoBin);

        actualizarMedicion(&med, hora, humedad);

        fseek(archivoBin, sizeof (st_Medicion) * hora, SEEK_SET);

        fwrite(&med, sizeof (st_Medicion), 1, archivoBin);

        fgets(linea, 50, archivoTxt);
    } //TERMINA DE LEER EL ARCHIVO DE TEXTO.

    //AHORA RECORRO EL ARCHIVO BIN PARA ACTUALIZAR EL PROMEDIO DE HUMEDADES;
    calcularHumedadProm(archivoBin);
    
    fclose(archivoTxt);
    fclose(archivoBin);
    
    imprimirBinario(archivoBin);

    fclose(archivoBin);



    

    return (EXIT_SUCCESS);

}

