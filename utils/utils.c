#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include "color.h"

/********************* FUNCIONES BASICAS **********************/
int leerEntero(cadena mensaje){
    int num;
    fflush(stdin);
    printf("%s ", mensaje);
    fflush(stdin);
    scanf("%d", &num);

    return num;
}

int leerEnteroEntre(cadena mensaje, int low, int high){
    int num;

    printf("%s ", mensaje);
    scanf("%d", &num);
    while(num < low || num > high){
        printf("Error valor fuera de rango, %s\n", mensaje);
        scanf("%d", &num);
    }
    return num;
}

char leerCaracter(cadena mensaje){
    char x;

    printf("%s ", mensaje);
    fflush(stdin);
    scanf("%c", &x);

    return x;
}

float leerFloat(cadena mensaje){
    float num;

    printf("%s ", mensaje);
    fflush(stdin);
    scanf("%f", &num);

    return num;
}

float leerFloatEntre(cadena mensaje, float menor, float mayor){
    float num;

    printf("%s ", mensaje);
    scanf("%f", &num);
    while(num < menor || num > mayor){
        printf("Error valor fuera de rango, %s\n", mensaje);
        scanf("%f", &num);
    }

    return num;
}

void leerCadena(cadena mensaje, cadena cadena){
    printf(mensaje);
    fflush(stdin);
    gets(cadena);
}

int confirmaUsuario(cadena mensaje){

    char opc;

    printf("%s [S/N]: ", mensaje);
    fflush(stdin);
    scanf("%c", &opc);
    while (opc != 'S' && opc != 's' && opc != 'N' && opc != 'n') {
        printf("Error. Opcion invalida. %s [S/N]: ", mensaje);
        fflush(stdin);
        scanf("%c", &opc);
    }
    return opc;
}

/*********************************************** FUNCIONES DEL TP ***********************************************/



int chequearUsuario(cadena user, cadena pass){

    cadena user1 = "jperez";
    cadena pass1 = "abc123";

    cadena user2 = "ggonzalez";
    cadena pass2 = "abc456";

    int us = strcmp(user1, user);
    int pa = strcmp(pass1, pass);

    int us1 = strcmp(user2, user);
    int pa1 = strcmp(pass2, pass);


    if(us == 0 && pa == 0){
        return 1;
    }else if(us1 == 0 && pa1 == 0){
        return 2;
    }else{
        menuLogin();
    }

}

/************************************ FUNCIONES PARA APERTURA Y CIERRE DE ARCHIVOS *********************************/

void abrirArchivo(FILE **ppArch, cadena path, cadena modo){//Apertura de archivos donde se coloca el archivo, luego el nombre y el modo (lectura, escri, etc)
    *ppArch = fopen(path, modo);
    if (*ppArch != NULL) {
        printf("***TABLAS CARGADAS CORRECTAMENTE EN MODO %s ***\n", modo);
    }else {
        printf("***ERROR AL CARGAR LAS TABLAS***\n");
    }
}

void cerrarArchivo(FILE *pArch, cadena path){//Esta funcion es para cerrar los archivos despues de trabajarlos
    int result = fclose(pArch);
    if (result == 0) {
        printf("***TABLAS CERRADAS***\n");
    }else {
        printf("***ERROR, NO SE PUDO CERRAR LAS TABLAS***\n");
    }
}
