#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include "color.h"

typedef char cadena[100];
#define LARGE_LINEA 10000

typedef struct{
    int idArticulo;
    cadena descripcion;
    int categoria;
    int cantidad;
    float precio;
}Articulo;

typedef struct elemento{
    Articulo datos;
    struct elemento *sig;
}nodoArt;

typedef struct{
    int idCliente;
    cadena nombre;
    cadena apellido;
    cadena mail;
    int telefono;
}Cliente;

typedef struct elemento2{
    Cliente dato;
    struct elemento2 *sig;
}nodoCli;

typedef struct{
    int id;
    int dni;
    int idVendedor;
    cadena fecha;
    int numFac;
    float Tgng;
    float Iva;
    float Tgf;
}Factura;

typedef struct elemento3{
    Factura dato;
    struct elemento3 *sig;
}nodoFac;

typedef struct{
    int id;
    int idFac;
    int idArt;
    int cant;
    float preUni;
    float preLin;

}detFactura;

typedef struct elemento4{
    detFactura dato;
    struct elemento4 *sig;
}nodoDFac;


int leerRegistro(FILE* pArch, Articulo art[], int CANT_ARTICULOS);
void mostrar(FILE* bin);
nodoArt* ingresarDato(Articulo y);
void cargararchivo(FILE *bin, nodoArt *art);
void cargapila(nodoArt **a, Articulo art[], int z);
void apilar(nodoArt **a, nodoArt *q);
void mostrarRegistros(Articulo artLeido[], int cant);
nodoArt *buscarArt(nodoArt *a, int y);
int articuloBuscado(nodoArt *idArt, int num);


int leerRegistroCliente(FILE* pArch, Cliente cli[], int CANT_CLIENTE);
void mostrarCliente(FILE* bin);
nodoCli* ingresarDatoCli(Cliente y);
void cargararchivoCli(FILE *bin, nodoCli *cli);
void cargapilaCli(nodoCli **c, Cliente cli[], int z);
void apilarCli(nodoCli **c, nodoCli *q);
void mostrarRegistrosCliente(Cliente cliLeido[], int cant);
int contarRegistros(FILE* pArch);
nodoCli *buscarCli(nodoCli *c, int y);
void clienteBuscado(nodoCli *idCli);


int leerRegistroFactura(FILE* pArch, Cliente cli[], int CANT_FACTURA);
void mostrarFactura(FILE* bin);
nodoCli* ingresarDatoFac(Cliente y);
void cargararchivoFac(FILE *bin, nodoCli *cli);
void cargapilaFac(nodoCli **c, Cliente cli[], int z);
void apilarFac(nodoCli **c, nodoCli *q);
void mostrarRegistrosFactura(Cliente cliLeido[], int cant);
int contarRegistros(FILE* pArch);
nodoCli *buscarFac(nodoCli *c, int y);
void facturaBuscado(nodoCli *idCli);


void agregarCliente(FILE* cliBin);
void agregarArticulo(FILE* artBin);


void caratulaSistema(){//Caratula del sistema
    /*En esta fiuncion lo ideal es que se pase el archivo de texto o CSV a binario par amanipular el dato*/

    system("color 0F");

    printf(YELLOW"\n\n\t\t    ********************************************************************\n");
    printf("\n\t\t    *                           BIENVENIDOS                            *\n");
    printf("\n\t\t    *                                                                  *\n");
    printf("\n\t\t    *                          ALL MANAGEMENT                          *\n");
    printf("\n\t\t    *                                                                  *\n");
    printf("\n\t\t    *            SISTEMA DE GESTION Y ADMINISTRACION DE VENTAS         *\n");
    printf("\n\t\t    *                                                                  *\n");
    printf("\n\t\t    ********************************************************************\n\n");

    printf(BLUE"\n\n%cAllMANAGEMENT ", 169);
    printf(WHITE"Software de control y gestion de ventas v1.0 - Todos los derechos reservados - Buenos Aires - Argentina\n\n\n");
    printf(WHITE"        Trabajo Practico de Estructura y Base de Datos 2023 || VENTURA - NAVARRO SILVA - FELLER\n\n\n");

    system("pause");
}//fin de la funcion CARATULA.


int menuLogin(){

    //system("color E");
    cadena user;
    cadena pass;

    system("cls");
    //AGREGAR UN COMIENZO DE SISTEMA!!!!!!
    system("cls");
    printf(BLUE"\t\t\t\t _____________________________________\n\n");
    printf(WHITE"\t\t\t\t          TIENDA DE ELECTRONICOS      \n");
    printf("\t\t\t\t _____________________________________\n\n");

        fflush(stdin);
        leerCadena("\t\t\t\t\tUser ", user);
        fflush(stdin);
        leerCadena("\t\t\t\t\tPass ", pass);

    printf("\t\t\t\t______________________________________\n");

    int op = chequearUsuario(user, pass);

    return op;

}//fin de la funcion LOGIN.


void loginDelSistema(FILE* pArch, FILE* pArch1, FILE* pArch2, FILE* pArchB, FILE* pArchB1, FILE* pArchB2, FILE* pArch3, FILE* pArch4, FILE* pArchB3, FILE* pArchB4){
/*En esta funcion se chequea que exista el vendedor y la clave*/
    switch(menuLogin()){//la funcion menu principal va a devolver el valor que corresponde para vendedor o gerente

        case 1://caso para menu de vendedores, limitando sus credenciales
            system("cls");
            sistemaVentas(menuVendedor(), pArch, pArch1, pArch2, pArchB, pArchB1, pArchB2, pArch3, pArch4, pArchB3, pArchB4);//Menu para ventas
            system("pause");
        break;

        case 2://CASO para el gerente, con credenciales para realizar todas las funciones del vendedor y modificaciones en el stock
            system("cls");
            sistemaGerente(menuAdmin(), pArch, pArch1, pArch2, pArchB, pArchB1, pArchB2, pArch3, pArch4, pArchB3, pArchB4);
            //Aca el menu que corresponde a las actividades que correspoden al genrente que son las del vendedor mas modificaciones
            system("pause");
        break;
    }
}


/*El generete es el que puede realizar todas las tareas, alta y modificacion del stock, baja, alta y modificacion de empleados
facturacion general, facturacion por vendedor, */
void sistemaGerente(int op, FILE* pArch, FILE* pArch1, FILE* pArch2, FILE* pArchB, FILE* pArchB1, FILE* pArchB2, FILE* pArch3, FILE* pArch4, FILE* pArchB3, FILE* pArchB4){

//es mas comodo con un array de archivos, por cuestiones de tiempo lo dejo asi

    system("cls");

    abrirArchivo(&pArch2, "articulos.csv", "r");
    int cantRegArt = contarRegistros(pArch2);

    abrirArchivo(&pArch1, "clientes.csv", "r");
    int cantRegCli = contarRegistros(pArch1);

    Articulo artLeido[cantRegArt];//Array del struct
    Articulo a;//Declaro la variable del struct
    nodoArt *cabeza = NULL;
    nodoArt *aux = NULL;

    Cliente cliLeido[cantRegCli];//Array del struct
    Cliente c;//Declaro la variable del struct
    nodoCli *cabezaCli = NULL;
    nodoCli *auxCli = NULL;

    int ingresar;
    int opcli;
    int opart;
    int cant;
    int num;

    system("cls");
    fflush(stdin);

    do{

        switch(op){

            case 1:
                printf("****************  Generar Factura  ****************\n");

                abrirArchivo(&pArchB2, "artBinario.dat", "rb");
                rewind(pArch2);
                rewind(pArchB2);

                int cantA = leerRegistro(pArch2, artLeido, cantRegArt);
                //mostrarRegistros(artLeido, cant);
                cargapila(&cabeza, artLeido, cantA);
                cargararchivo(pArchB2, cabeza);

                int id = articuloBuscado(cabeza,num);//esta funcion devuelve un valor (devuelve la cantidad de stock)

                if(id < 1 || id == 0){
                    printf("\n******  PRODUCTO SIN STOCK  ******\n\n");
                }else{

                    printf("\nGenerando Facura \n");
                }

                fclose(pArch2);
                fclose(pArchB2);

                system("pause");
                sistemaGerente(menuAdmin(), pArch, pArch1, pArch2, pArchB, pArchB1, pArchB2, pArch3, pArch4, pArchB3, pArchB4);

            break;

            case 2:
                printf(BLUE"\t\t ****** Ver Stock. ******\n");
                //aca ademas de ver el stock, se tiene que desplegar un menu para dar de baja, alta o modificar.
                //mostrar el archivo del stock, (El archivo tiene que estar en binario).

                printf("\t\t\t\t1.- Ver Listado.\n"
                       "\t\t\t\t2.- Agegar Articulo al stock.\n"
                       "\t\t\t\t0.- Salir.\n");
                printf("\t\t\t\tOpcion: ");
                scanf("%d", &opart);
                do{
                    switch(opart){
                    case 1:

                        abrirArchivo(&pArchB2, "artBinario.dat", "rb");
                        //rewind(pArch2);
                        //rewind(pArchB2);

                        int cant = leerRegistro(pArch2, artLeido, cantRegArt);
                        //mostrarRegistros(artLeido, cant);

                        cargapila(&cabeza, artLeido, cant);
                        cargararchivo(pArchB2, cabeza);
                        mostrar(pArchB2);
                        break;
                    case 2:
                            agregarArticulo(pArchB2);
                        break;
                    }//fin del switch
                }while(opart < 0 || opart > 2);

                    fclose(pArch2);
                    fclose(pArchB2);

                system("pause");
                sistemaGerente(menuAdmin(), pArch, pArch1, pArch2, pArchB, pArchB1, pArchB2, pArch3, pArch4, pArchB3, pArchB4);
            break;

            case 3:
                printf(YELLOW"\t\t ****** Ver Listado de facturacion. ******\n");

                //funcion que muestra la facturacion general del local, es la suma de todas las ventas
                //todavia no esta hecha la funcion.


                system("pause");
                sistemaGerente(menuAdmin(), pArch, pArch1, pArch2, pArchB, pArchB1, pArchB2, pArch3, pArch4, pArchB3, pArchB4);
            break;

            case 4:
                printf(RED"\t\t ****** Ver listado - Agregar Cliente. ******\n\n");

                printf("\t\t\t\t1.- Ver Listado.\n"
                       "\t\t\t\t2.- Agegar Cliente.\n"
                       "\t\t\t\t0.- Salir.\n");
                printf("\t\t\t\tOpcion: ");
                scanf("%d", &opcli);
                do{
                    switch(opcli){
                    case 1:
                        //abrirArchivo(&pArch1, "clientes.csv", "r");
                        abrirArchivo(&pArchB1, "cliBinario.dat", "rb");
                        //rewind(pArch1);
                        //rewind(pArchB1);

                        int cant1 = leerRegistroCliente(pArch1, cliLeido, cantRegCli);
                       //mostrarRegistrosCliente(cliLeido, cant1);

                        cargapilaCli(&cabezaCli, cliLeido, cant1);
                        cargararchivoCli(pArchB1, cabezaCli);
                        mostrarCliente(pArchB1);

                        break;
                    case 2:
                            agregarCliente(pArch1);
                        break;
                    }//fin del switch
                }while(opcli < 0 || opcli > 2);

                        fclose(pArch1);
                        fclose(pArchB1);

                        system("pause");
                //funcion para agregar a las tablas un nuevo vendedor o modificar uno que ya existe.
                //Misma funcion para mostrar el listado de los clientes existentes.
                //con un while para elegir si ver el listado o agregar cliente nuevo.

                sistemaGerente(menuAdmin(), pArch, pArch1, pArch2, pArchB, pArchB1, pArchB2, pArch3, pArch4, pArchB3, pArchB4);

            break;

            case 5:
                printf(WHITE"\t\t\t\tCerrando Secion.\n");
                loginDelSistema(pArch, pArch1, pArch2, pArchB, pArchB1, pArchB2, pArch3, pArch4, pArchB3, pArchB4);
            break;

            case 6:
                printf("\t\t\t\tCERRARNDO EL SISTEMA.....\n");
            break;
            }//fin de switch
        }while(op < 1 || op > 6);

}

int menuAdmin(){

    //system("color 0F");
    int num;

    do{
        system("cls");
        printf(WHITE"\t\t\t\t _____________________________________\n\n");
        printf(GREEN"\t\t\t\t                  MENU             \n");
        printf("\t\t\t\t             ADMINISTRADOR              \n");
        printf(WHITE"\t\t\t\t _____________________________________\n\n"

               "\t\t\t\t      1. Generar venta.\n"
               "\t\t\t\t      2. Ver Stock.\n"
               "\t\t\t\t      3. Ver listado de facturacion.\n"
               "\t\t\t\t      4. Agregar Cliente - Ver Listado de clientes.\n"
               "\t\t\t\t      5. Cambiar Usuario.\n"
               "\t\t\t\t      6. Cerrar Sistema.\n");
        printf("\n\t\t\t\t ______________________________________\n");

        num = leerEntero("\n\t\t\t\t    Ingrese la opcion deseada:");

    }while(num < 1 || num > 6);

    system("cls");
    return num;
}//fin del MENU_ADMIN

int menuVendedor(){

    system("color 06");
    int num;

    do{
        system("cls");
        printf("\t\t\t\t _____________________________________\n\n");
        printf("\t\t\t\t                 MENU                   \n");
        printf("\t\t\t\t                VENTAS                  \n");
        printf("\t\t\t\t _____________________________________\n\n"

               "\t\t\t\t          1. Generar venta.\n"
               "\t\t\t\t          2. Cargar Cliente.\n"
               "\t\t\t\t          3. Ver Stock.\n"
               "\t\t\t\t          4. Ver Factura.\n"
               "\t\t\t\t          5. Cerrar Secion.\n"
               "\t\t\t\t ______________________________________\n");

        num = leerEntero("\n\t\t\t\t    Ingrese la opcion deseada:");
        fflush(stdin);
    }while(num < 1 || num > 5);

    return num;
}//Fin del MENU_VENTAS



void sistemaVentas(int op, FILE* pArch, FILE* pArch1, FILE* pArch2, FILE* pArchB, FILE* pArchB1, FILE* pArchB2, FILE* pArch3, FILE* pArch4, FILE* pArchB3, FILE* pArchB4){//a esta funcion hay que pasar el archivo binario del stock, clientes,

    system("cls");

    abrirArchivo(&pArch2, "articulos.csv", "r");
    int cantRegArt = contarRegistros(pArch2);

    abrirArchivo(&pArch1, "clientes.csv", "r");
    int cantRegCli = contarRegistros(pArch1);

    abrirArchivo(&pArch3, "facturacion.csv", "r");
    int cantRegFac = contarRegistros(pArch3);

    abrirArchivo(&pArch4, "detallefactura.csv", "r");
    int cantRegDetFac = contarRegistros(pArch4);

    Articulo artLeido[cantRegArt];//Array del struct
    Articulo a;//Declaro la variable del struct
    nodoArt *cabeza = NULL;
    nodoArt *aux = NULL;

    Cliente cliLeido[cantRegCli];//Array del struct
    Cliente c;//Declaro la variable del struct
    nodoCli *cabezaCli = NULL;
    nodoCli *auxCli = NULL;

    Factura facLeido[cantRegFac];//Array del struct
    Factura f;//Declaro la variable del struct
    nodoFac *cabezaFac = NULL;
    nodoFac *auxFac = NULL;

    detFactura detFacLeido[cantRegDetFac];//Array del struct
    detFactura df;//Declaro la variable del struct
    nodoDFac *cabezaDFac = NULL;
    nodoDFac *auxDFac = NULL;

    int ingresar;
    int opcli;
    int num;

    system("cls");
    fflush(stdin);

    do{
        switch(op){

            case 1:
                printf(GREEN"\t\t\t\tGeneracion de Venta\n");

                abrirArchivo(&pArchB2, "artBinario.dat", "rb");
                rewind(pArch2);
                rewind(pArchB2);

                int cantA = leerRegistro(pArch2, artLeido, cantRegArt);
                //mostrarRegistros(artLeido, cant);
                cargapila(&cabeza, artLeido, cantA);
                cargararchivo(pArchB2, cabeza);

                int id = articuloBuscado(cabeza,num);//esta funcion devuelve un valor (devuelve la cantidad de stock)

                if(id < 1 || id == 0){
                    printf("\n******  PRODUCTO SIN STOCK  ******\n\n");
                }else{

                    printf("\nGenerando Facura \n");


                }

                fclose(pArch2);
                fclose(pArchB2);

                system("pause");
                sistemaVentas(menuVendedor(), pArch, pArch1, pArch2, pArchB, pArchB1, pArchB2, pArch3, pArch4, pArchB3, pArchB4);
                break;

            case 2:
                printf(GREEN"\t\t\t\tListado de Cliente\n");
                printf("\t\t\t\t1.- Ver Listado.\n"
                       "\t\t\t\t2.- Agegar Cliente.\n"
                       "\t\t\t\t0.- Salir.\n");
                printf("\t\t\t\tOpcion: ");
                scanf("%d", &opcli);
                do{
                    switch(opcli){
                    case 1:
                        //abrirArchivo(&pArch1, "clientes.csv", "r");
                        abrirArchivo(&pArchB1, "cliBinario.dat", "rb");
                        rewind(pArch1);
                        rewind(pArchB1);

                        int cant1 = leerRegistroCliente(pArch1, cliLeido, cantRegCli);
                       //mostrarRegistrosCliente(cliLeido, cant1);

                        cargapilaCli(&cabezaCli, cliLeido, cant1);
                        cargararchivoCli(pArchB1, cabezaCli);
                        mostrarCliente(pArchB1);

                        break;
                    case 2:
                            agregarCliente(pArch1);
                        break;
                    }//fin del switch
                }while(opcli < 0 || opcli > 2);

                        fclose(pArch1);
                        fclose(pArchB1);

                        system("pause");
                sistemaVentas(menuVendedor(), pArch, pArch1, pArch2, pArchB, pArchB1, pArchB2, pArch3, pArch4, pArchB3, pArchB4);
            break;

            case 3:
                printf(BLUE"\t\t\t\tVer Stock\n");

                abrirArchivo(&pArch2, "articulos.csv", "r");
                abrirArchivo(&pArchB2, "artBinario.dat", "rb");
                rewind(pArch2);
                rewind(pArchB2);

                int cant = leerRegistro(pArch2, artLeido, cantRegArt);
                //mostrarRegistros(artLeido, cant);

                cargapila(&cabeza, artLeido, cant);
                cargararchivo(pArchB2, cabeza);

                mostrar(pArchB2);

                fclose(pArch2);
                fclose(pArchB2);

                system("pause");
                sistemaVentas(menuVendedor(), pArch, pArch1, pArch2, pArchB, pArchB1, pArchB2, pArch3, pArch4, pArchB3, pArchB4);
            break;

            case 4:
                printf(YELLOW"\t\t\t\tVer factura\n");
                //funcion para ver la factura de compra generada
                //si alcanza el tiempo, poner una funcion que pasando el numero de cliente muestre las facturas de compra que realizo.
                system("pause");
                sistemaVentas(menuVendedor(), pArch, pArch1, pArch2, pArchB, pArchB1, pArchB2, pArch3, pArch4, pArchB3, pArchB4);
            break;

            case 5:
                printf(RED"\t\t\t Cerrando Secion.....\n");
                system("pause");
                loginDelSistema(pArch, pArch1, pArch2, pArchB, pArchB1, pArchB2, pArch3, pArch4, pArchB3, pArchB4);
                break;

        }//fin del switch
    }while(op < 1 || op > 5);
}

//******************************** GENERACION DE FACTURA  *******************************************************

//******************************** AGREGAR CLIENTE Y ARTICULOS  *************************************************
void agregarArticulo(FILE* artBin){

    Articulo art;

    int cod;
    cadena descrip;
    int categoria;
    int cantidad;
    float precio;


    artBin = fopen("artBinario.dat", "ab+");

    if(artBin != NULL){

        cod = leerEntero("Ingrese el codigo del producto,  -1 para salir: ");

        while(cod != -1){
            leerCadena("Ingrese la descripcion del producto: ", descrip);
            categoria = leerEntero("Ingrese la categoria: ");
            cantidad = leerEntero("Ingrese la cantidad: ");
            precio = leerFloat("Ingrese valor del producto: ");

            art.idArticulo = cod;
            strcpy(art.descripcion, descrip);
            art.cantidad = cantidad;
            art.precio = precio;
            fseek(artBin, 0L, SEEK_END);
            fwrite(&art, sizeof(Articulo), 1, artBin);
            cod = leerEntero("Ingrese el codigo de producto (-1) para salir: ");
        }
    }else{
        printf("Error, No se puede abrir el archivo!!");
    }
    fclose(artBin);
}


void agregarCliente(FILE* cliBin){

    Cliente cli;

    int cod;
    cadena nombre;
    cadena apellido;
    cadena mail;
    int telefono;

    cliBin = fopen("cliBinario.dat", "ab+");

    if(cliBin != NULL){

        cod = leerEntero("Ingrese el ID del cliente,  -1 para salir: ");

        while(cod != -1){
            leerCadena("Ingrese Nombre: ", nombre);
            leerCadena("Ingrese Apellido: ", apellido);
            leerCadena("Ingrese E-Mail: ", mail);
            telefono = leerEntero("Ingrese Telefono: ");

            cli.idCliente = cod;
            strcpy(cli.nombre, nombre);
            strcpy(cli.apellido, apellido);
            strcpy(cli.mail, mail);
            cli.telefono = telefono;
            fseek(cliBin, 0L, SEEK_END);
            fwrite(&cli, sizeof(Cliente), 1, cliBin);
            cod = leerEntero("Ingrese el ID del cliente (-1) para salir: ");
        }
    }else{
        printf("Error, No se puede abrir el archivo!!");
    }
    fclose(cliBin);
}

//********************************** FUNCIONES PARA ARTICULOS ****************************************************


nodoArt *buscarArt(nodoArt *a, int y){
    if (!a){
        return (NULL);
    }else if (y == a->datos.idArticulo){
        return (a);
        buscarArt(a->sig, y);
    }else{
        buscarArt(a->sig, y);
        //return (buscar(x->sig, y));//Si dejo esto solo retorna uno solo
    }
}

int articuloBuscado(nodoArt *idArt, int num){
    nodoArt *aux;
    Articulo a;
    int cantArticulo;

    if (idArt){
        printf("\n\n Ingrese el codigo del articulo: ");
        scanf("%d", &num);

        aux = buscarArt(idArt, num);

        if(aux == NULL){
            return 0;
        }else{
            return cantArticulo = aux->datos.cantidad;
            //printf("\n%3d\t\t%3s\t\t%3d\t\t",aux->datos.idArticulo, aux->datos.descripcion, aux->datos.cantidad);
            //solo muestra un dato, me quede corto de tiempo.
        }
    }

}

void cargararchivo(FILE *bin, nodoArt *art){

    while(art != NULL){
        Articulo datos = art->datos;
        fwrite(&datos, sizeof(Articulo), 1, bin);
        art = art->sig;
    }
}

nodoArt* ingresarDato(Articulo y){
    nodoArt *q = (nodoArt*)malloc(sizeof(nodoArt));
    q->datos = y;
    q->sig = NULL;
    return q;
}

void cargapila(nodoArt **a, Articulo art[], int z){

    int i;
    nodoArt *q;

    for(i = 0; i < z; i++){
        q = ingresarDato(art[i]);
        apilar(&(*a), q);
    }
}

void apilar(nodoArt **a, nodoArt *q){
    q->sig = *a;
    *a = q;
}

void mostrar(FILE* bin){//muestra el archivo binario de articulos.

    Articulo a;
    rewind(bin);
    printf("\n IDARTICULO\t\t DESCRIPCION\t\t\t\t\t\t\tCATEGORIA  CANT  PRECIO");

    while(!feof(bin)) {
        fread(&a,sizeof(a),1,bin);
        printf("\n%7d\t\t%-70s\t%5d\t%5d\t%5.2f",a.idArticulo ,a.descripcion, a.categoria, a.cantidad, a.precio);
    }
    printf("\n");
}

int leerRegistro(FILE* pArch, Articulo artLeido[], int CANT_ARTICULOS){

    Articulo a;
    char cadena[LARGE_LINEA];
    int i = 0;

    while(i < CANT_ARTICULOS && feof(pArch) == 0){

        fgets(cadena, LARGE_LINEA, pArch);

        char delim[] = ";";
        char *token;

        token = strtok(cadena, delim);
        a.idArticulo = atoi(token);

        token = strtok(NULL, delim);
        strcpy(a.descripcion, token);

        token = strtok(NULL, delim);
        a.categoria = atoi(token);

        token = strtok(NULL, delim);
        a.cantidad = atoi(token);

        token = strtok(NULL, delim);
        a.precio = atoi(token);

        artLeido[i] = a;
        i++;
    }

    return i;
}

void mostrarRegistros(Articulo artLeido[], int cant){//muestra el registro en memoria

    printf("\n IDARTICULO\t\t DESCRIPCION\t\t\t\t\t\t\t     CATEGORIA  CANTIDAD  PRECIO");

    for (int i = 0; i < cant; i++){
        Articulo a = artLeido[i];
        printf("\n%7d\t\t%-75s\t%5d\t%5d\t%7.2f", a.idArticulo, a.descripcion, a.categoria, a.cantidad, a.precio);
    }
    printf("\n");
}

//***************************************** Funciones para el struct clientes ******************************************
nodoCli *buscarCli(nodoCli *c, int y){
    if (!c){
        return (NULL);
    }else if (y == c->dato.idCliente){
        return (c);
        buscarCli(c->sig, y);
    }else{
        buscarCli(c->sig, y);
        //return (buscar(x->sig, y));//Si dejo esto solo retorna uno solo
    }
}

void clienteBuscado(nodoCli *idCli){
    int num;
    nodoCli *aux;
    Cliente c;

    if (idCli){
        printf("\n\n Ingrese el codigo del articulo: ");
        scanf("%d", &num);

        aux = buscarCli(idCli, num);

        if(aux == NULL){
            printf("\n******  CLIENTE NO ENCONTRADO  ******\n");
        }else{
            //return clienteEncontrado = aux->dato.idCliente;
            printf("\n%d\t%s\t%s\t%s\t%d\n",aux->dato.idCliente, aux->dato.nombre, aux->dato.apellido, aux->dato.mail, aux->dato.telefono);
        }
    }

}

void cargararchivoCli(FILE *bin, nodoCli *cli){

    while(cli != NULL){
        Cliente dato = cli->dato;
        fwrite(&dato, sizeof(Cliente), 1, bin);
        cli = cli->sig;
    }
}

nodoCli* ingresarDatoCli(Cliente y){
    nodoCli *q = (nodoCli*)malloc(sizeof(nodoCli));
    q->dato = y;
    q->sig = NULL;
    return q;
}

void cargapilaCli(nodoCli **c, Cliente cli[], int z){

    int i;
    nodoCli *q;

    for(i = 0; i < z; i++){
        q = ingresarDatoCli(cli[i]);
        apilarCli(&(*c), q);
    }
}

void apilarCli(nodoCli **c, nodoCli *q){
    q->sig = *c;
    *c = q;
}


void mostrarCliente(FILE* binC){//muestra el archivo binario de articulos.

    Cliente c;
    rewind(binC);
    printf("\nIDCLIENTE\tNOMBRE\t\tAPELLIDO \t\tMAIL\t          TELEFONO\n");

    while(!feof(binC)){
        fread(&c,sizeof(c),1,binC);
        printf("\n%5d  %15s %15s  %30s  %7d", c.idCliente, c.nombre, c.apellido, c.mail, c.telefono);
    }
    printf("\n");
}

int leerRegistroCliente(FILE* pArch, Cliente cliLeido[], int CANT_CLIENTE){

    Cliente c;
    char cadena[LARGE_LINEA];
    int i = 0;

    while(i < CANT_CLIENTE && feof(pArch) == 0){

        fgets(cadena, LARGE_LINEA, pArch);

        char delim[] = ";";
        char *token;

        token = strtok(cadena, delim);
        c.idCliente = atoi(token);

        token = strtok(NULL, delim);
        strcpy(c.nombre, token);

        token = strtok(NULL, delim);
        strcpy(c.apellido, token);

        token = strtok(NULL, delim);
        strcpy(c.mail, token);

        token = strtok(NULL, delim);
        c.telefono = atoi(token);

        cliLeido[i] = c;
        i++;
    }

    return i;
}

void mostrarRegistrosCliente(Cliente cliLeido[], int cant){//muestra el registro en memoria

    printf("\nIDCliente - Nombre - Apellido - Mail - Telefono\n");

    for (int i = 0; i < cant; i++){
        Cliente c = cliLeido[i];
        printf("\n %d  -  %s  -  %s  -  %s  -  %d", c.idCliente, c.nombre, c.apellido, c.mail, c.telefono);
    }
    printf("\n");
}

int contarRegistros(FILE* pArch){

    int contador = 0;
    char caracter;

    while (!feof(pArch)){
        caracter = fgetc(pArch);
        if(caracter == '\n'){
            contador++;
        }
    }

    return contador;
}
