#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include "Map.h"

//Estructuras

//Tipo nación
typedef struct
{
    int economia;   //Factor 0
    int religion;   //Factor 1
    int defensa;    //Factor 2
    int felicidad;  //Factor 3
    int corrupcion; //Factor 4
} nacion;

//Tipo NPC
typedef struct
{
    int id; //Número identificador del personaje
    char nombre[30]; //Nombre del personaje
    char peticion[500]; //Petición del personaje
    char opcion_a[100]; //Opción A de la interacción
    char opcion_b[100]; //Opción B de la interacción
    int consecuencia_a[5]; //Consecuencia de la opción A
    int consecuencia_b[5]; //Consecuencia de la opción B
} NPC;

//Funciones principales

void leer_archivo(Map *);
void pasar_consecuencia(char *, NPC *, int);
void display_menu();
void juego(Map *, int *, int *, int, nacion *, int *);
int dado_personajes(Map *, int *, int);
int finales(nacion *);
int dado_evento(int *, int);
void finales_eventos(int);
void eventos(int*, int, int);

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
    nacion *reino;

    int cont; //Contador de interacciones que lleva el jugador
    int cantidad = 10; //Cantidad de personajes
    int array_personaje[cantidad]; //Arreglo para bloquear las interacciones ya ocurridas
    int array_eventos[cantidad]; //Arreglo para bloquear las interacciones ya ocurridas
    int llave_evento;
    leer_archivo(personajes);
    //mostrar_personajes(personajes);

    int lectura = 3;
    while (lectura != 27)
    {
        display_menu();
        lectura = leer_tecla();
        if (lectura == 1)
        {
            //Se inicializan las variables de juego para una nueva partida
            cont = 0;
            for (int i = 0; i < cantidad; i++)
            {
                array_personaje[i] = 0;
                array_eventos[i] = 0;
            }
            reino = (nacion *)malloc(sizeof(nacion));
            reino->religion = 10;
            reino->corrupcion = 10;
            reino->economia = 10;
            reino->felicidad = 10;
            reino->defensa = 10;

            printf("El anterior lord regente del reino de La Embarrada acaba de huir de sus labores.\n");
            printf("Cuando pasabas cerca del castillo, te entrega toda su autoridad...\n");
            printf("%cLarga vida al nuevo Soberano de La Embarrada!\n\n", 33);
            printf("(Presiona cualquier tecla para comenzar...)");
            limpiar_consola();

            //Iteración donde ocurre el juego
            while (cont < cantidad && lectura!=27 && lectura!=32)
            {
                //Mostrar cualidades nacion
                mostrar_nacion(reino);
                //Juego
                juego(personajes, array_personaje, array_eventos, cantidad, reino, &lectura);
                cont++;
                if (lectura == 32)
                {
                    printf("Asignas al primer pobre diablo que se te cruza como Soberano y huyes despavorido de tus labores.\n\n");
                    printf("(Presiona cualquier tecla para salir...)");
                    limpiar_consola();
                    break;
                }

                //En cada iteración se verifica el estado de los 5 factores. En el caso que corresponda, puede saltar el final malo
                if (finales(reino) == 1)
                {
                    printf("(Presiona cualquier tecla para salir...)");
                    limpiar_consola();
                    break;
                }
                
                llave_evento = dado_evento(array_eventos, cantidad);
                if (llave_evento != 0){
                    finales_eventos(llave_evento);
                    printf("(Presiona cualquier tecla para salir...)");
                    limpiar_consola();
                    break;
                }
            }
            //Si el usuario finaliza todas las interacciones, salta el final bueno
            if (cont == cantidad && llave_evento == 0)
            {
                printf("Tu juicio logra mantener el reino. La Embarrada prospera hasta el d%ca de tu muerte.\n\nFIN.\n\n", 161);
                printf("(Presiona cualquier tecla para volver al men%c principal...)", 163);
                limpiar_consola();
            }
        }
    }
    return 0;
}

//Función que lee el archivo "personajes.txt"
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

//Función que pasa la consecuencia de la lectura al arreglo de la estructura NPC
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

//Función que muestra el menu principal
void display_menu()
{
    printf("1.   Iniciar partida\n");
    printf("Esc. Salir del juego\n");
    printf("\n");
    printf("Escriba la opcion que desee: ");
}

//Función en la que se muestran las interacciones
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
    //Opcion Espacio Huir
    printf("(Presione espacio para huir de sus labores...)\n");
    *lectura = leer_tecla();
    modificar_nacion(iterador, *lectura, reino);
    //Modificar array de eventos
    eventos(array_eventos,*lectura, numero);
}

//Se desbloquean los eventos dependiendo de la opcion que el usuario escoja
void eventos(int *array_eventos, int lectura, int numero){
    if(numero == 6){
        if(lectura == 1){
            array_eventos[numero] = 1;
        }
    }
}
//Función que verifica los factores para determinar si se satisface la condición de un final malo
int finales(nacion *reino)
{
    if (reino->corrupcion > 19)
    {
        printf("El Senado envenena tu comida para hacerse con el poder de La Embarrada.\n\nFIN.\n\n");
        return 1;
    }
    if (reino->economia < 1)
    {
        printf("La pobre administracion del Tesoro sume a La Embarrada en una fatal hambruna.\n\nFIN.\n\n");
        return 1;
    }
    if (reino->religion > 19)
    {
        printf("La influencia del Culto eclipsa al poder de la Corona.\n\nFIN.\n\n");
        return 1;
    }
    if (reino->religion < 1)
    {
        printf("El Grande castiga a los herejes por su falta de fe inundando La Embarrada y destruy%endola completamente.\n\nFIN.\n\n", 130);
        return 1;
    }
    if (reino->defensa < 1)
    {
        printf("Al enterarse de la deficiente defensa de La Embarrada, el reino vecino invade tu territorio.\n\nFIN.\n\n");
        return 1;
    }
    if (reino->felicidad < 1)
    {
        printf("Una turba furiosa entra al castillo y te lincha.\n\nFIN.\n\n");
        return 1;
    }
    return 0;
}

//Función que retorna la clave relacionada a un evento. Si el evento existe, se retorna el índice relacionado a este, sino, retorna 0
int dado_evento(int *array_eventos, int cantidad){
    
    srand(time(NULL));
    int numero = rand() % cantidad;
    
    if (array_eventos[numero] == 1){
        if (numero == 6){
            return numero;
        }
    }
    return 0;
}

//Función que muestra el final del evento relacionado a la llave que le corresponda
void finales_eventos(int llave_evento){
    if (llave_evento == 6){
        printf("La poblaci%cn de La Embarrada muere ante la llegada de la peste negra.\n\nFIN.\n\n", 162);
        return;
    }
}

//Función que muestra el valor actual de los factores del reino
void mostrar_nacion(nacion *reino)
{
    printf("                           ESTADO DE LA EMBARRADA\n");
    printf("| Corrupcion: %i | Defensa: %i | Economia: %i | Felicidad: %i | Religion: %i |\n\n", reino->corrupcion, reino->defensa, reino->economia, reino->felicidad, reino->religion);
}

//Función que llama por ID a un personaje aleatorio con el que el jugador aún no ha interactuado
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

//Función debug para mostrar a los personajes leídos. Usar solo para verificar que "personajes.txt" ha sido leído correctamente.
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

//Función que muestra las consecuencias de cada opción por interacción
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

//Función que modifica los factores del reino según las consecuencias de la opción elegida por el usuario
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

//Función que lee la tecla ingresada por el usuario
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
                case 32: //Espacio
                lectura = 32;
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