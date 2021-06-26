#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <time.h>
int lectura;
void leer_tecla();

int main()
{
    while (lectura != 27)
    {
        printf("%i", lectura);
        leer_tecla();
    }
}
void leer_tecla()
{
    int valido = 0;
    char letra;
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
}
