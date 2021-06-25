//Librerías
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#include "Map.h"

//Estructuras

//Tipo nación
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
   int consecuencia_a[5];

   char opcion_b[30];
   int consecuencia_b[5];
}NPC;

//Funciones principales
Map *cargar_personajes();

//Funciones auxiliares
int is_equal_int(void *, void *);

//Función main
int main(){
   
   int entrada;
   Map* personajes = cargar_personajes();
   
   do{
   }while(entrada != 0);

   printf("Abandonas tu cargo como rey de La Embarrada");
}

//Función que carga los personajes desde el archivo "personajes.txt"
/*

Map *cargar_personajes(){
   Map *mapa = createMap(is_equal_int); //Mapa que guarda cada personaje por su ID
   NPC *personaje;
   FILE *file = fopen("personajes.txt", "r");
   char lectura[20];
   int cont = 0; //Contador para leer los datos de cada personaje (7 datos en total x personaje)
   while (fscanf(file, "%[^,\n]s", lectura) != EOF){
      fgetc(file);
      printf("%s\n\n", lectura);

      if (cont == 0) //Lee ID del personaje
      {
         personaje = (NPC*) malloc (sizeof(NPC));
         personaje->id = atoi(lectura);
         cont++;
         continue;
      }

      if (cont == 1){ //Lee nombre del personaje
         strcpy(personaje->nombre, lectura);
         cont++;
         continue;
      }
      
      if (cont == 2){ //Lee la petición del personaje 
         strcpy(personaje->peticion, lectura);
         cont++;
         continue;
      }
      
      if (cont == 3){ //Lee la opción A de la petición
         strcpy(personaje->opcion_a, lectura);
         cont++;
         continue;
      }
      
      if (cont == 4){ //Lee la opción B de la petición
         strcpy(personaje->opcion_b, lectura);
         cont++;
         continue;
      }
      
      if (cont == 5){ //Lee las consecuencias de la opción A
         strcpy(personaje->consecuencia_a, lectura);
         cont++;
         continue;
      }

      if (cont == 6){ //Lee las consecuencias de la opción B
         strcpy(personaje->consecuencia_b, lectura);
         cont++;
      }
      
      if (cont == 7)
      {
         cont = 0;
         insertMap(mapa, &personaje->id, personaje);
      }
   }
   fclose(file);
   return mapa;
}

*/

//Función para comparar claves de tipo int. Retorna 1 si son iguales
int is_equal_int(void *key1, void *key2)
{
    if (*(int *)key1 == *(int *)key2)
        return 1;
    return 0;
}