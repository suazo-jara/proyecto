//Librerias
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
//#include <list.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

//Estructura

typedef struct
{
   char Raza[10];
   int Fuerza;       // mide la potencia física y capacidades deportivas.
   int Destreza;     // mide la agilidad y los reflejos.
   int Constitucion; // mide la resistencia y la salud.
   int Inteligencia; // mide el razonamiento y la memoria.
   int Sabiduria;    // mide la perspicacia e intuición.
   int Carisma;      // mide la fuerza de personalidady la presencia
} Raza;

typedef struct
{
   char nombre[30];
   Raza estadisticas;
   int karma;
   //Se puede agregar mas
} Personaje;

typedef struct
{
    char nombre[50];
    char tipo[50];
    char objetivo[50];
    int estado;
} Mision;

typedef struct
{
    char nombre[30];
    char tipo[30];
    int daño;
    int vitalidad;
} Objetos;

typedef struct
{
    char nombre[30];
    char localidad[50];
    char dialogo1[1000];
    char dialogo2[1000];  
}NPC;

//Variables Globales
//Para las elccion de Raza
Raza humano = {"Humano", 1, 2, 3, 4, 5};
Raza enano = {"Enano", 1, 2, 3, 4, 5};
Raza Elfo = {"Elfo", 1, 2, 3, 4, 5};
//Por si querremos que navegue con las flechas
#define arriba 72;
#define izquierda 75;
#define derecha 77;
#define abajo 80;
#define exit 27;

//Pototipos Funciones
Personaje crearPersonaje();
int dado();

//Main
int main()
{
   printf("Bienvenido al juego de rol mas impresionante del mundo\n");
   
   Personaje jugador = crearPersonaje();
}

//Funciones
int dado()
{
   srand(time(NULL));
   int num = rand() % 10;
}

Personaje crearPersonaje()
{
   Personaje usuario;
   printf("Cual es tu nombre?\n");
   scanf("%[^\n]s", usuario.nombre);
   getchar();
   system("cls");
   int opcion = 0;
   while (opcion == 0)
   {
      printf("Elije tu Raza\n");
      printf("Humano(1)  Elfo(2)  Enano(3)\n");
      scanf("%i", &opcion);
      system("cls");
      switch (opcion)
      {
      case 1:
         printf("Descripcion Humano\n");
         printf("Cancelar(0)/Siguiente(1)\n");
         scanf("%i", &opcion);
         system("cls");
         if (opcion == 1)
         {
            usuario.estadisticas = humano;
         }
         else
         {
            if (opcion != 0)
            {
               printf("ingrese una opcion valida");
               opcion = 0;
            }
         }
         break;
      case 2:
         printf("Descripcion Elfo\n");
         printf("Cancelar(0)/Siguiente(1)\n");
         scanf("%i", &opcion);
         system("cls");
         if (opcion == 1)
         {
            usuario.estadisticas = Elfo;
         }
         else
         {
            if (opcion != 0)
            {
               printf("ingrese una opcion valida");
               opcion = 0;
            }
         }
         break;
      case 3:
         printf("Descripcion Enano\n");
         printf("Cancelar(0)/Siguiente(1)\n");
         scanf("%i", &opcion);
         system("cls");
         if (opcion == 1)
         {
            usuario.estadisticas = enano;
         }
         else
         {
            if (opcion != 0)
            {
               printf("ingrese una opcion valida");
               opcion = 0;
            }
         }
         break;

      default:
         opcion = 0;
         break;
         system("cls");
      }
   }
   FILE *archivo = fopen("personaje.csv", "w");

   fprintf(archivo, "%s,%s,%i,%i,%i,%i,%i,%i", usuario.nombre, usuario.estadisticas.Raza, usuario.estadisticas.Fuerza, usuario.estadisticas.Destreza,
           usuario.estadisticas.Constitucion, usuario.estadisticas.Inteligencia, usuario.estadisticas.Sabiduria, usuario.estadisticas.Carisma, usuario.karma);
   fclose(archivo);
   return usuario;
}