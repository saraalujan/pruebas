#include "restaurant.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constantes.h"
#include "utilidades.h"

int main() {
  srand((unsigned)time(NULL));
  juego_t juego;
  char accion;

  inicializar_juego(&juego);
  while(estado_juego(juego) == SIGUE_JUGANDO){
    mostrar_juego(juego);
    verificar_comensales_y_paciencia_mesas(&juego);
    verificar_linguini_pedidos(&juego);
    verificar_pedido_cocina(&juego);
    verificar_plato_cocina(&juego);
    pedir_jugada(&accion);    
    realizar_jugada(&juego, accion);
  }
  destruir_juego(&juego);
  return 0;
}
