//Librerias
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "list.h"
#include "Map.h"

//Estructuras

//Tipo Nación
typedef struct{
   int economia; //0
   int religion; //1
   int defensa; //2
   int felicidad; //3
   int corrupcion; //4
}nacion;

//Tipo NPC
typedef struct{
   int id;
   char nombre[30];
   char peticion[500];
   char opcion_a[100];
   char opcion_b[100];
   int consecuencia_a[5];
   int consecuencia_b[5];
}NPC;

//Funciones principales
void leer_archivo(Map*);
void pasar_consecuencia(char *,NPC*, int);
void display_menu();

//Funciones auxiliares
void mostrar_personajes(Map *);
int is_equal_int(void *, void *);
int is_equal_float(void *, void *);
int lower_than_int(void *, void *);
int lower_than_float(void *, void *);

int main(){
   Map *personajes = createMap(is_equal_int);
   setSortFunction(personajes,lower_than_int);
   int lectura;

   leer_archivo(personajes);
   //mostrar_personajes(personajes);

   printf("\nEl anterior lord regente del reino de La Embarrada acaba de huir de sus labores.\n");
   printf("Cuando pasabas cerca del castillo, te entrega toda su autoridad.\n");
   printf("Te dispones a realizar tu labor como Soberano de La Embarrada.\n\n");
   
   do{
       display_menu();
       scanf("%d", &lectura);
       printf("\n");
       if (lectura == 1){
           
       }
    }while(lectura != 0);
   
   
   printf("Huyes despavorido de tus labores.\n\n");
   printf("(Presiona cualquier tecla para salir...)");
   //HACER ESO 
   return 0;
}

void leer_archivo(Map *personajes){
   int cont = 0;
   int cantidad = -1;//cantidad de personajes
   int id = 0;
   char *lectura = (char *)malloc(sizeof(char) * 1000);
   FILE *archivo = fopen("personajes.txt", "r");

   NPC *npc = (NPC*)malloc(sizeof(NPC));

   while(fscanf(archivo,"%[^%\n]s",lectura) != EOF){
      fgetc(archivo);

      while(cont<6){
         fscanf(archivo,"%[^%\n]s",lectura);
         lectura = (char *)malloc(sizeof(char) * 100);
         fgetc(archivo);
         cont++;
      }

      if(cantidad == 0){
          npc->id = atoi(lectura);
      }

      if(cantidad == 1){
          strcpy(npc->nombre,lectura);
      }

      if(cantidad == 2){
          strcpy(npc->peticion,lectura);
      }

      if(cantidad == 3){
          strcpy(npc->opcion_a,lectura);
      }

      if(cantidad == 4){
          strcpy(npc->opcion_b,lectura);
      }

      if(cantidad == 5){
          pasar_consecuencia(lectura,npc,cantidad);
      }
      if(cantidad == 6){
          pasar_consecuencia(lectura,npc,cantidad);
          insertMap(personajes,&npc->id,npc);
          npc = (NPC *)malloc(sizeof(NPC));
          cantidad = -1;
      }
      lectura = (char *)malloc(sizeof(char) * 5000);
      
      cantidad++;

   }   
}

void pasar_consecuencia(char *lectura,NPC *npc, int cantidad){
    int cont = 0;
    int numero;
    for(int i = 1;cont<6;i++){

        if(isdigit(lectura[i])){
            if(cantidad == 5){
                numero = lectura[i] - '0';
                if(lectura[i-1] == '-'){
                    npc->consecuencia_a[cont] = -numero;
                }else{
                    npc->consecuencia_a[cont] = numero;
                }
            }else{
                numero = lectura[i] - '0';
                if(lectura[i-1] == '-'){
                    npc->consecuencia_b[cont] = -numero;
                }else{
                    npc->consecuencia_b[cont] = numero;
                }
            }
            cont++;
        }
    }
}

void display_menu(){
    printf("1. Iniciar partida\n");
    printf("0. Salir del juego\n");
    printf("\n");
    printf("Escriba la opcion que desee: ");
}

void mostrar_personajes(Map *personajes){
    
    NPC *ayuda = firstMap(personajes);
    while (ayuda)
    {
        printf("ID: %i\n", ayuda->id);
        printf("Nombre: %s\n", ayuda->nombre);
        printf("Peticion:\n%s\n", ayuda->peticion);

        printf("Opcion A: %s\n", ayuda->opcion_a);
        printf("Consecuencias: ");
        for(int i = 0; i<5;i++){
            if(ayuda->consecuencia_a[i] != 0){
                if(i == 0) printf("Economia: ");
                if(i == 1) printf("Religion: ");
                if(i == 2) printf("Defensa: ");
                if(i == 3) printf("Felicidad: ");
                if(i == 4) printf("Corrupcion: ");
                if(ayuda->consecuencia_a[i] > 0) printf("+");
                printf("%i | ", ayuda->consecuencia_a[i]);
            }
        }

        printf("\n");
        printf("Opcion B: %s\n", ayuda->opcion_b);
        printf("Consecuencias: ");
        for(int i = 0; i<5;i++){
            if(ayuda->consecuencia_b[i] != 0){
                if(i == 0) printf("Economia: ");
                if(i == 1) printf("Religion: ");
                if(i == 2) printf("Defensa: ");
                if(i == 3) printf("Felicidad: ");
                if(i == 4) printf("Corrupcion: ");
                if(ayuda->consecuencia_b[i] > 0) printf("+");
                printf("%i / ", ayuda->consecuencia_b[i]);
            }
        }

        printf("\n");
        printf("\n");
        ayuda = nextMap(personajes);
    }
}

//Función para comparar claves de tipo int. Retorna 1 si son iguales
int is_equal_int(void *key1, void *key2)
{
    if (*(int *)key1 == *(int *)key2)
        return 1;
    return 0;
}

//Función para comparar claves de tipo float. Retorna 1 si son iguales
int is_equal_float(void *key1, void *key2)
{
    if (*(float *)key1 == *(float *)key2)
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

//Función para comparar claves de tipo float. Retorna 1 si key1 < key2
int lower_than_float(void *key1, void *key2)
{
    if (*(float *)key1 < *(float *)key2)
        return 1;
    return 0;
}
