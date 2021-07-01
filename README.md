# PROYECTO: Soberano de La Embarrada - Grupo Default

decisiones personajes = [0][1]*[2]*[3]...
                        {0}{0}*{1}*{0}...

              eventos = [0][1]*[2]*[3] (igual largo que la cantidad de personajes)
                        {2}{2}*{0}*{1} (las casillas con "2" no tienen evento relacionado)
                                       (las casillas con "0" son eventos desbloqueados)
                                       (las casillas con "1" son eventos bloqueados)

Las casillas se desbloquean dependiendo de las interacciones con los personajes y tras cada interacción se lanza un
dado cuyo valor es igual al índice del arreglo "eventos". Se verifica el número en la casilla. A diferencia de lo que
ocurre en el dado que verifica las interacciones, esta vez no se tirará hasta tras la próxima interacción (siguiente iteración).

Máximo para cada factor : 20
Mínimo para cada factor : 0

Finales: 
- Economía en 0
- Religión en 0
- Religión en 20
- Defensa en 0
- Felicidad en 0
- Corrupción en 20
- Todas las interacciones completas
- Final para cada evento (si se elige la opción equivocada)

Requisitos:
Compilador MS-DOS(por la libreria conio.h)

Integrantes:

- Juan Araya Horta
- César Gacitúa de las Heras
- Kevin Meza Toro
- Cristian Suazo Jara