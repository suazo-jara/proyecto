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
   char texto[50];
   int preRequisitoEvento[2]; 
   int posicionEvento[2];

} Evento;

typedef struct
{
char  ecenario[16][16];
Pantalla* norte;
Pantalla* sur;
Pantalla* este;
Pantalla* oeste;
} Pantalla;

typedef struct
{
char Raza[10];
int Fuerza;       // mide la potencia física y capacidades deportivas.
int Destreza;     // mide la agilidad y los reflejos.
int Constitucion; // mide la resistencia y la salud.
int Inteligencia; // mide el razonamiento y la memoria.
int Sabiduria;    // mide la perspicacia e intuición.
int Carisma;      // mide la fuerza de personalidady la presencia
}Raza;
 
typedef struct
{
Raza estadisticas;
int karma;
//Se puede agregar mas
}Personaje;

//Variables Globales
//Para las elccion de Raza
Raza humano = {"Humano", 1,2,3,4,5} ;
Raza enano  = {"Enano",  1,2,3,4,5} ;
Raza Elfo   = {"Elfo",   1,2,3,4,5} ;
//Por si querremos que se mueva en un mapa
#define arriba 72;
#define izquierda 75;
#define derecha 77;
#define abajo 80;
#define exit 27;


//Pototipos Funciones
int dado();

//Main
int main(){
char letra;
letra=getchar();
int a;
a=(int)letra;

printf("%i",a);



}

//Funciones
int dado(){
   srand(time(NULL));
   int num=rand()%10;
}