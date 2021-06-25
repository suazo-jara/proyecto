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
   char opcion_a[30];
   char opcion_b[30];
   int consecuencia_a[5];
   int consecuencia_b[5];
}NPC;

//Funciones
void leer_archivo(Map*);
void pasar_consecuencia(char *,NPC*, int);
int is_equal_int(void *, void *);
int is_equal_float(void *, void *);
int lower_than_int(void *, void *);
int lower_than_float(void *, void *);

int main(){
   Map *personajes = createMap(is_equal_int);
   setSortFunction(personajes,lower_than_int);

   leer_archivo(personajes);
   //MOSTRAR PERSONAJES
   /*
   NPC *ayuda = firstMap(personajes);
   while (ayuda)
   {
       printf("id:%i  nombre:%s peticion:%s opcion_a:%s opcion_b:%s \n", ayuda->id, ayuda->nombre, ayuda->peticion,ayuda->opcion_a,ayuda->opcion_b);
       printf("consecuencia_a:");
       for(int i = 0; i<5;i++){
           printf("%i ", ayuda->consecuencia_a[i]);
       }
       printf("consecuencia_b:");
       for(int i = 0; i<5;i++){
           printf("%i ", ayuda->consecuencia_b[i]);
       }
       printf("\n");
       printf("\n");

       ayuda = nextMap(personajes);
   }
   */
   
   printf("fin");
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
