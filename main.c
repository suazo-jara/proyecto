#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include "list.h"
#include "Map.h"

//Estructuras

//Tipo Nación
typedef struct
{
    int economia;   //0
    int religion;   //1
    int defensa;    //2
    int felicidad;  //3
    int corrupcion; //4
} nacion;

//Tipo NPC
typedef struct
{
    int id;
    char nombre[30];
    char peticion[500];
    char opcion_a[100];
    char opcion_b[100];
    int consecuencia_a[5];
    int consecuencia_b[5];
} NPC;

//Funciones principales
void leer_archivo(Map *);
void pasar_consecuencia(char *, NPC *, int);
void display_menu();
void juego(Map *, int *, int *, int, nacion *, int *);
int dado_personajes(Map *, int *, int);
int finales(nacion *);

//Funciones auxiliares
void limpiar_consola();
void mostrar_nacion(nacion *);
void mostrar_consecuencias(NPC *, int);
void modificar_nacion(NPC *, int, nacion *);
int leer_tecla();
void mostrar_personajes(Map *);
int is_equal_int(void *, void *);
int lower_than_int(void *, void *);

int main()
{
    Map *personajes = createMap(is_equal_int);
    setSortFunction(personajes, lower_than_int);
    nacion *reino = (nacion *)malloc(sizeof(nacion));
    reino->religion = 10;
    reino->corrupcion = 10;
    reino->economia = 10;
    reino->felicidad = 10;
    reino->defensa = 10;

    int cont = 0;
    int cantidad = 2;
    int array_personaje[2] = {};
    int array_eventos[2] = {};

    leer_archivo(personajes);
    //mostrar_personajes(personajes);

    int lectura = 3;
    while (lectura != 27)
    {
        display_menu();
        lectura = leer_tecla();
        if (lectura == 1)
        {
            printf("El anterior lord regente del reino de La Embarrada acaba de huir de sus labores.\n");
            printf("Cuando pasabas cerca del castillo, te entrega toda su autoridad...\n");
            printf("%cLarga vida al nuevo Soberano de La Embarrada!\n\n", 33);
            printf("(Presiona cualquier tecla para comenzar...)");

            limpiar_consola();
            while (cont < cantidad && lectura != 27)
            {
                //Mostrar cualidades nacion
                mostrar_nacion(reino);
                //Juego
                juego(personajes, array_personaje, array_eventos, cantidad, reino, &lectura);
                cont++;

                if (finales(reino) == 1)
                {
                    limpiar_consola();
                    break;
                }
            }
            if (cont == cantidad)
            {
                printf("Tu juicio logra mantener el reino. La Embarrada prospera hasta el d%ca de tu muerte.\nFIN.\n\n", 161);
                printf("(Presiona cualquier tecla para volver al men%c principal...)", 163);
                limpiar_consola();
            }
        }
        if (lectura == 0)
        {
            printf("Huyes despavorido de tus labores.\n\n");
            printf("(Presiona cualquier tecla para salir...)");
            limpiar_consola();
        }
    }
    return 0;
}

void leer_archivo(Map *personajes)
{
    int cont = 0;
    int cantidad = -1; //cantidad de personajes
    int id = 0;
    char *lectura = (char *)malloc(sizeof(char) * 1000);
    FILE *archivo = fopen("personajes.txt", "r");

    NPC *npc = (NPC *)malloc(sizeof(NPC));

    while (fscanf(archivo, "%[^%\n]s", lectura) != EOF)
    {
        fgetc(archivo);

        while (cont < 6)
        {
            fscanf(archivo, "%[^%\n]s", lectura);
            lectura = (char *)malloc(sizeof(char) * 100);
            fgetc(archivo);
            cont++;
        }

        if (cantidad == 0)
        {
            npc->id = atoi(lectura);
        }

        if (cantidad == 1)
        {
            strcpy(npc->nombre, lectura);
        }

        if (cantidad == 2)
        {
            strcpy(npc->peticion, lectura);
        }

        if (cantidad == 3)
        {
            strcpy(npc->opcion_a, lectura);
        }

        if (cantidad == 4)
        {
            strcpy(npc->opcion_b, lectura);
        }

        if (cantidad == 5)
        {
            pasar_consecuencia(lectura, npc, cantidad);
        }
        if (cantidad == 6)
        {
            pasar_consecuencia(lectura, npc, cantidad);
            insertMap(personajes, &npc->id, npc);
            npc = (NPC *)malloc(sizeof(NPC));
            cantidad = -1;
        }
        lectura = (char *)malloc(sizeof(char) * 5000);

        cantidad++;
    }
}

void pasar_consecuencia(char *lectura, NPC *npc, int cantidad)
{
    int cont = 0;
    int numero;
    for (int i = 1; cont < 6; i++)
    {

        if (isdigit(lectura[i]))
        {
            if (cantidad == 5)
            {
                numero = lectura[i] - '0';
                if (lectura[i - 1] == '-')
                {
                    npc->consecuencia_a[cont] = -numero;
                }
                else
                {
                    npc->consecuencia_a[cont] = numero;
                }
            }
            else
            {
                numero = lectura[i] - '0';
                if (lectura[i - 1] == '-')
                {
                    npc->consecuencia_b[cont] = -numero;
                }
                else
                {
                    npc->consecuencia_b[cont] = numero;
                }
            }
            cont++;
        }
    }
}

void display_menu()
{
    printf("1. Iniciar partida\n");
    printf("0. Salir del juego\n");
    printf("\n");
    printf("Escriba la opcion que desee: ");
}

void juego(Map *personajes, int *array_personajes, int *array_eventos, int cantidad, nacion *reino, int *lectura)
{

    NPC *iterador;
    int numero;
    int cont = 0;
    int opcion = 0;

    //Lanzar dado para seleccionar personaje
    numero = dado_personajes(personajes, array_personajes, cantidad);
    //Buscar personaje
    iterador = searchMap(personajes, &numero);

    //Mostrar personaje
    printf("%s:\n", iterador->nombre);
    printf("%s\n\n", iterador->peticion);
    //Opcion 0
    printf("0. %s \n", iterador->opcion_a);
    mostrar_consecuencias(iterador, opcion);
    //Opcion 1
    opcion = 1;
    printf("1. %s \n", iterador->opcion_b);
    mostrar_consecuencias(iterador, opcion);

    //Seleccionar opcion
    printf("%cQu%c desea la voluntad de Su Alteza?\n\n", 168, 130);
    *lectura = leer_tecla();
    modificar_nacion(iterador, *lectura, reino);
}

int finales(nacion *reino)
{ //Hay que ver los eventos

    if (reino->corrupcion > 19)
    {
        printf("\nEl Senado envenena tu comida para hacerse con el poder de La Embarrada.");
        return 1;
    }
    if (reino->economia < 1)
    {
        printf("\nLa pobre administración del Tesoro sume a La Embarrada en una fatal hambruna.");
        return 1;
    }
    if (reino->religion > 19)
    {
        printf("\nLa influencia del Culto eclipsa al poder de la Corona.");
        return 1;
    }
    if (reino->religion < 1)
    {
        printf("\nEl Grande castiga a los herejes por su falta de fe inundando La Embarrada y destruy%endola completamente.", 130);
        return 1;
    }
    if (reino->defensa < 1)
    {
        printf("\nAl enterarse de la deficiente defensa de La Embarrada, el reino vecino invade tu territorio.");
        return 1;
    }
    if (reino->felicidad < 1)
    {
        printf("\nUna turba furiosa entra al castillo y te lincha.");
        return 1;
    }
    return 0;
}

void mostrar_nacion(nacion *reino)
{
    printf("                           ESTADO DE LA EMBARRADA\n");
    printf("| Corrupcion: %i | Defensa: %i | Economia: %i | Felicidad: %i | Religion: %i |\n\n", reino->corrupcion, reino->defensa, reino->economia, reino->felicidad, reino->religion);
}

int dado_personajes(Map *personajes, int *array_personajes, int cantidad)
{
    srand(time(NULL));
    int verificar = 0;
    int numero;
    while (verificar == 0)
    {
        numero = rand() % cantidad;
        if (array_personajes[numero] == 0)
        {
            array_personajes[numero] = 1;
            verificar = 1;
            return numero;
        }
    }
}

void mostrar_personajes(Map *personajes)
{

    NPC *ayuda = firstMap(personajes);
    while (ayuda)
    {
        printf("ID: %i\n", ayuda->id);
        printf("Nombre: %s\n", ayuda->nombre);
        printf("Peticion:\n%s\n", ayuda->peticion);

        printf("Opcion A: %s\n", ayuda->opcion_a);
        printf("Consecuencias: | ");
        for (int i = 0; i < 5; i++)
        {
            if (ayuda->consecuencia_a[i] != 0)
            {
                if (i == 0)
                    printf("Economia: ");
                if (i == 1)
                    printf("Religion: ");
                if (i == 2)
                    printf("Defensa: ");
                if (i == 3)
                    printf("Felicidad: ");
                if (i == 4)
                    printf("Corrupcion: ");
                if (ayuda->consecuencia_a[i] > 0)
                    printf("+");
                printf("%i | ", ayuda->consecuencia_a[i]);
            }
        }

        printf("\n");
        printf("Opcion B: %s\n", ayuda->opcion_b);
        printf("Consecuencias: | ");
        for (int i = 0; i < 5; i++)
        {
            if (ayuda->consecuencia_b[i] != 0)
            {
                if (i == 0)
                    printf("Economia: ");
                if (i == 1)
                    printf("Religion: ");
                if (i == 2)
                    printf("Defensa: ");
                if (i == 3)
                    printf("Felicidad: ");
                if (i == 4)
                    printf("Corrupcion: ");
                if (ayuda->consecuencia_b[i] > 0)
                    printf("+");
                printf("%i | ", ayuda->consecuencia_b[i]);
            }
        }

        printf("\n");
        printf("\n");
        ayuda = nextMap(personajes);
    }
}

void mostrar_consecuencias(NPC *iterador, int opcion)
{

    if (opcion == 0)
    {
        printf("CONSECUENCIAS: | ");
        for (int i = 0; i < 5; i++)
        {
            if (iterador->consecuencia_a[i] != 0)
            {
                if (i == 0)
                    printf("Economia: ");
                if (i == 1)
                    printf("Religion: ");
                if (i == 2)
                    printf("Defensa: ");
                if (i == 3)
                    printf("Felicidad: ");
                if (i == 4)
                    printf("Corrupcion: ");
                if (iterador->consecuencia_a[i] > 0)
                    printf("+");
                printf("%i | ", iterador->consecuencia_a[i]);
            }
        }
        printf("\n");
        printf("\n");
    }
    if (opcion == 1)
    {
        printf("CONSECUENCIAS: | ");
        for (int i = 0; i < 5; i++)
        {
            if (iterador->consecuencia_b[i] != 0)
            {
                if (i == 0)
                    printf("Economia: ");
                if (i == 1)
                    printf("Religion: ");
                if (i == 2)
                    printf("Defensa: ");
                if (i == 3)
                    printf("Felicidad: ");
                if (i == 4)
                    printf("Corrupcion: ");
                if (iterador->consecuencia_b[i] > 0)
                    printf("+");
                printf("%i | ", iterador->consecuencia_b[i]);
            }
        }
        printf("\n");
        printf("\n");
    }
}

void modificar_nacion(NPC *iterador, int lectura, nacion *reino)
{
    int cambio;

    if (lectura == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            if (iterador->consecuencia_a[i] != 0)
            {
                cambio = iterador->consecuencia_a[i];
                if (i == 0)
                    reino->economia += cambio;
                if (i == 1)
                    reino->religion += cambio;
                if (i == 2)
                    reino->defensa += cambio;
                if (i == 3)
                    reino->felicidad += cambio;
                if (i == 4)
                    reino->corrupcion += cambio;
            }
        }
    }
    if (lectura == 1)
    {
        for (int i = 0; i < 5; i++)
        {
            if (iterador->consecuencia_b[i] != 0)
            {
                cambio = iterador->consecuencia_b[i];
                if (i == 0)
                    reino->economia += cambio;
                if (i == 1)
                    reino->religion += cambio;
                if (i == 2)
                    reino->defensa += cambio;
                if (i == 3)
                    reino->felicidad += cambio;
                if (i == 4)
                    reino->corrupcion += cambio;
            }
        }
    }
}

int leer_tecla()
{
    int valido = 0;
    char letra;
    int lectura;
    while (valido == 0)
    {
        if (kbhit())
        {
            letra = getch();
            switch (letra)
            {
            case 27: //escape
                lectura = 27;
                valido++;
                break;
            case 48: //0
                lectura = 0;
                valido++;
                break;
            case 65: //A
                lectura = 0;
                valido++;
                break;
            case 97: //a
                lectura = 0;
                valido++;
                break;
            case 75: //flecha de izquierda
                lectura = 0;
                valido++;
                break;
            case 49: //1
                lectura = 1;
                valido++;
                break;
            case 66: //B
                lectura = 1;
                valido++;
            case 98: //b
                lectura = 1;
                valido++;
                break;
            case 77: //flecha derecha
                lectura = 1;
                valido++;
                break;

            default:
                break;
            }
        }
    }
    system("cls");
    return lectura;
}
//Función que limpia la consola cuando se presione una tecla
void limpiar_consola()
{
    while (!kbhit())
    { //loop infinito sin hacer nada hasta que se precione una tecla
    }
    system("cls");
}
//Función para comparar claves de tipo int. Retorna 1 si son iguales
int is_equal_int(void *key1, void *key2)
{
    if (*(int *)key1 == *(int *)key2)
        return 1;
    return 0;
}

//Función para comparar claves de tipo int. Retorna 1 si key1 < key2
int lower_than_int(void *key1, void *key2)
{
    if (*(int *)key1 < *(int *)key2)
        return 1;
    return 0;
}