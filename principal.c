#include "utils/utils.h"
#include "utils/color.h"

/*
Recordatorio de lo que contiene cada archivo
arch0 = Archivo de empleados
arch1 = Archivo de clientes
arch2 = Archivo de articulos
arch3 = archivo de facturas

idem con los archivos binarios.
*/

int main(){

    FILE *archCsv0;
    FILE *archCsv1;
    FILE *archCsv2;
    FILE *archCsv3;
    FILE *archCsv4;

    FILE *archBin0;
    FILE *archBin1;
    FILE *archBin2;
    FILE *archBin3;
    FILE *archBin4;


    //apertura previa de archivos csv
    //abrirArchivo(&archCsv0, "empleados.csv", "r");
    //abrirArchivo(&archCsv1, "clientes.csv", "r");
    //abrirArchivo(&archCsv2, "articulos.csv", "r");

    caratulaSistema();

    loginDelSistema(archCsv0, archBin0, archCsv1, archBin1, archCsv2, archBin2, archCsv3, archBin3, archCsv4, archBin4);


    return 0;
}

