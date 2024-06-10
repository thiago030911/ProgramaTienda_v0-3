#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include "color.h"

typedef char cadena[100];

/**************************************** FUNCIONES BASICAS *****************************************/
int leerEntero(cadena mensaje);
int leerEnteroEntre(cadena mensaje, int low, int high);
char leerCaracter(cadena mensaje);
float leerFloat(cadena mensaje);
float leerFloatEntre(cadena mensaje, float low, float high);
void leerCadena(char mensaje[], char cadena[]);
int confirmaUsuario(cadena mensaje);


/***************************************** M E N U S ****************************************************/

void caratulaSistema();
int menuLogin();
void loginDelSistema(FILE* pArch, FILE* pArch1, FILE* pArch2, FILE* pArchB, FILE* pArchB1, FILE* pArchB2, FILE* pArch3, FILE* pArch4, FILE* pArchB3, FILE* pArchB4);
int menuAdmin();
void sistemaGerente(int op, FILE* pArch, FILE* pArch1, FILE* pArch2, FILE* pArchB, FILE* pArchB1, FILE* pArchB2, FILE* pArch3, FILE* pArch4, FILE* pArchB3, FILE* pArchB4);
int menuVendedor();
void sistemaVentas(int op, FILE* pArch, FILE* pArch1, FILE* pArch2, FILE* pArchB, FILE* pArchB1, FILE* pArchB2, FILE* pArch3, FILE* pArch4, FILE* pArchB3, FILE* pArchB4);
int chequearUsuario(cadena user, cadena pass);
void abrirArchivo(FILE** ppArch, cadena path, cadena modo);
void cerrarArchivo(FILE* pArch, cadena path);
void agregarProducto(FILE* pBin);



#include "utils.c"
#include "menus.c"

#endif // UTILS_H_INCLUDED
