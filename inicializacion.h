#ifndef __INICIALIZACION_H__
#define __INICIALIZACION_H__
#include "restaurant.h"
#include "constantes.h"

/*Pre: -
Post: Inicializa el terreno con posiciones vacias del terreno
*/
void inicializar_terreno(char matriz_terreno[MAX_FILAS][MAX_COLUMNAS]);

/*Pre: El puntero detalla lo que se tiene que inicializar en Linguini
Post: Se inicializa Linguini en una posicion libre aleatoria. 
*/
void inicializar_mozo_linguini(juego_t *juego);

/*Pre: El puntero detalla lo que se tiene que inicializar en las mesas
Post: Se inicializan las mesas individuales en una posicion libre aleatoria.
*/
void inicializar_mesas_individuales(juego_t *juego);

/*Pre: El puntero detalla lo que se tiene que inicializar en las mesas
Post: Se inicializan las mesas grupales en posiciones de 2x2 libres aleatorias 
*/
void inicializar_mesas_grupo(juego_t *juego);

/*Pre: El puntero detalla lo que se tiene que inicializar en la cocina
Post: Se inicializa la cocina en una posicion libre aleatoria. La lista de platos en preparacion/listos se inicializa como NULL. Con CANT ambos inicial de 0.
*/
void inicializar_cocina(juego_t *juego);

/*Pre:El puntero detalla lo que se tiene que inicializar en la mopa (herraminta)
Post: Se inicializa la mopa en una posicion libre aleatoria
*/
void inicializar_mopa(juego_t *juego);

/*Pre: El puntero detalla lo que se tiene que inicializar en las monedas(herramienta)
Post: Se inicializan las 8 monedas en posiciones aleatorias libres
*/
void inicializar_monedas(juego_t *juego);

/*Pre: El puntero detalla lo que se tiene que inicializar en los patines(herramienta)
Post: Se inicializan 5 patines en posiciones aleatorias libres
*/
void inicializar_patines(juego_t *juego);

/*Pre: El puntero detalla lo que se tiene que inicializar en los charcos(obstaculos)
Post: Se inicializan 5 charcos en posiciones aleatorias libres
*/
void inicializar_charcos(juego_t *juego);

/*Pre: Se necesitan la inicializacion de las mesas individuales y grupales
Post: Se inicializan las mesas cumpliendo que no se superpongan y que tengan espacio libre
*/
void inicializar_mesas(juego_t *juego);

/*Pre: Se necesitan la inicializacion de la mopa, los patines y monedas
Post: Se inicializan las herramientas verificando que tengan espacio libre
*/
void inicializar_herramientas(juego_t *juego);

/*Pre: Se necesita la inicializacion de los charcos (no uso solo charcos porque despues están las cucarachas asi que va a ser util a futuro(creo))
Post: Se inicializan los obstaculos verificando que tengan espacio libre
*/
void inicializar_obstaculos(juego_t *juego);

#endif /* __INICIALIZACION_H__ */