#ifndef __UTILIDADES_H__
#define __UTILIDADES_H__
#include "restaurant.h"

/*Pre:-
Post: Genera una posicion aleatoria y devuelve esa posicion
*/
coordenada_t generar_posicion_aleatoria();

/*Pre: La coordenada debe ser valida para evaluar
Post: Devuelve true si la posición está ocupada. Devuelve false si la posición está libre
*/
bool posicion_ocupada(juego_t *juego, coordenada_t posicion);

/*Pre: Tiene que ser un caracter valido (A/W/S/D/O)
Post: Devuelve true si la accion es valida. Y false por si no lo es.
*/
bool es_accion_valida(char accion);

/*Pre: Debe estar en los limites validos
Post: Devuelve true si la posicion es valida. Y false por si no lo es. 
*/
bool es_posicion_valida(juego_t *juego, coordenada_t nueva_posicion);

/*Pre: columna y fila representan el tamaño de la mesa que se va a colocar
Post: Devuelve true si las posiciones alrededor estan libres para colocar las mesas. Y false si no lo tienen.
*/
bool espacio_alrededor_mesa_libre(juego_t *juego, coordenada_t posicion, int columna, int fila);

/*Pre: La coordenada tiene que estar en los limites validos
Post: Devuelve true si la posicion es valida para soltar la mopa. Y false si no lo es
*/
bool posicion_valida_para_mopa(juego_t *juego, coordenada_t posicion);

/*Pre:Linguini tiene que estar sobre una posicion valida
Post: Verifica si Linguini esta sobre la mopa, y si sí, le pregunta si quiere tomarla
*/
void verificar_interaccion_mopa(juego_t *juego);

/*Pre: el puntero en accion tiene que estar inicializado
Post: Le pide al usuario que ingrese una accion valida que se guarda en la variable accion y valida que sea una accion valida para el juego
*/
void pedir_jugada(char *accion);

/*Pre: Las coordenadas tienen que ser validas.
Post: Retorna la distancia entre posicion 1 y posicion 2.
*/
int distancia_manhattan(coordenada_t posicion1, coordenada_t posicion2);

/*Pre: Se apunta a la estructura juego bien inicializada y al campo movimientos.
Post: Retorna true si el numero de movimientos es multiplo de 15 y distinto de 0, caso contrario retorna false.
*/
bool movimiento_multiplo_quince(juego_t *juego);

/*Pre: Se appunta a la estructura juego bien inicializada y al campo movimientos.
Post: Retorna true si el numero de movimientos es multiplo de 25 y distinto de 0, caso contrario retorna false.
*/
bool movimiento_multiplo_veinticinco(juego_t *juego);

/*Pre: -
Post: Retorna un numero aleatorio de comensales entre 1 y 4 (inclusive).
*/
int cantidad_aleatoria_comensales();

/*Pre: - 
Post: Retorna un numero aleatorio de paciencia entre 100 y 200 (inclusive).
*/
int cantidad_aleatoria_paciencia();

/*Pre: -
Post: Retorna un numero aleatorio de pedido entre 1 y 4 (inclusive).
*/
int numero_aleatorio_pedido();

/*Pre: El parametro numero_pedido tiene que ser un numero entre 1 y 4 (inclusive).
Post: Retorna el caracter del plato elegido.
*/
char obtener_plato(int numero_pedido);

/*Pre: El parametro plato tiene que ser un caracter de plato valido.
Post: Retorna el tiempo de preparacion de ese pedido.
*/
int obtener_tiempo_preparacion(char plato);

/*Pre: Compara las posiciones de las mesas con la de la cucaracha.
Post: Retorna true si esta a una distancia manhattan de 2, caso contrario retorna false. 
*/
bool cucaracha_cerca_mesa(juego_t *juego, mesa_t mesa);

/*Pre: Compara la posicion de Linguini con la de los charcos.
Post: Retorna el indice del charco donde esta parado Linguini.
*/
int linguini_sobre_charco(juego_t *juego);

/*Pre: Linguini esta sobre un charco con la mopa tomada.
Post: Linguini limpia el charco eliminandolo del vector y decrementandolo del array obstaculos.
*/
void linguini_limpia_charco(juego_t *juego);

/*Pre: Linguini tiene platos en su bandeja y no tenia la mopa tomada.
Post: Linguini pierde el plato al pasar por el charco sin la mopa, los comensales de la mesa de este plato se van, y su pedido_tomado vuelve a ser false. 
*/
void linguini_pierde_plato_charco(juego_t *juego);

/*Pre: Se reciben dos parametros, la posicion de Linguini y el tipo de dato mesa_t mesa.
Post: Retorna true si Linguini esta a distancia manhattan 1 de las mesas.
*/
bool linguini_cerca_mesa(coordenada_t posicion_linguini, mesa_t mesa);

/*Pre: Recorre las mesas y su cantidad de comensales.
Post: Si la paciencia es menor a 20 muestra un mensaje de advertencia diciendo que se pueden ir si no le dan su plato hasta ese entonces. Y sino, muestra un mensaje con la informacion de la mesa.
*/
void verificar_comensales_y_paciencia_mesas(juego_t *juego);

/*Pre: Revisa si el mozo tiene patines recolectados.
Post: Muestra un mensaje preguntando si quiere activar los patines con la tecla "P".
*/
void verificar_interaccion_patines(juego_t *juego);

/*Pre: Recorre los pedidos de Linguini y tambien reocrre las mesas. 
Post: Muestra mensajes de los pedidos que Linguini tiene, si no tiene, y si quiere tomar el pedido a una mesa estando a distancia manhattan de 1.
*/
void verificar_linguini_pedidos(juego_t *juego);

/*Pre: Verifica si en la cocina hay platos en preparacion con tiempo de preparacion > 0.
Post: Muestra un mensaje diciendo que la cocina esta preparando pedidos, caso contrario que no tenga, muestra un mensaje diciendo que no tiene pedidos para preparar.
*/
void verificar_pedido_cocina(juego_t *juego);

/*Pre: Verifica si en la cocina hay platos listos para poder retirarlos.
Post: Muestra un mensaje de los platos de las mesas que tiene Linguini en su bandeja, en caso de no tener, muestra un mensaje diciendo que no tiene platos en su bandeja.
*/
void verificar_plato_cocina(juego_t *juego);

/*Pre: La mesa dejo de tener comensales en la mesa.
Post: Elimina los datos del pedido decrementando en uno de su array de la mesa en la que los comensales se fueron (id_mesa).
*/
void eliminar_pedido_si_comensales_se_van(juego_t *juego, int id_mesa);

/*Pre: La mesa dejo de tener comensales en la mesa.
Post: Elimina los datos del plato decrementando en uno de su array de la mesa en la que los comensales se fueron (id_mesa).
*/
void eliminar_bandejas_si_comensales_se_van(juego_t *juego, int id_mesa);

/*Pre: La mesa dejo de tener comensales en la mesa.
Post: Elimina el plato en preparacion de la cocina decrementando en uno de su array de la mesa en la que los comensales se fueron (id_mesa).
*/
void eliminar_plato_preparacion_comensales_se_van(juego_t *juego, int id_mesa);

/*Pre: La mesa dejo de tener comensales en la mesa.
Post: Elimina el plato listo de la cocina decrementando en uno de su array de la mesa en la que los comensales se fueorn (id_mesa).
*/
void eliminar_platos_listos_comensales_se_van(juego_t *juego, int id_mesa);

/*Pre: La paciencia llego a 0 o a menos.
Post: Los comensales se van y dependiendo de si tomaron o no su pedido, esta preparandose o no, se elimina todos los datos relacionados a esa mesa.
*/
void comensales_se_van(juego_t *juego, int id_mesa);

/*Pre: Se recorre las mesas si tienen comensales en ellas.
Post: Por cada movimiento valido de Linguini decrementa de a uno la paciencia, si se genera una cucaracha a distancia manhattan 2 de las mesas decrementa de a 2 la paciencia hasta que se mate. Si llega a 0 los comensales se van.
*/
void actualizar_paciencia_mesas(juego_t *juego);

#endif /* _UTILIDADES_H__ */
