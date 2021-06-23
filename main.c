//Librerias
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

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
   int consecuencia_a[5];

   char opcion_b[30];
   int consecuencia_b[5];
}NPC;

int main(){
   printf("");
   return 0;
}