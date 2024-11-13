#include "utilidades.h"
#include <stdlib.h>
#include "restaurant.h"
#include "constantes.h"
#include <stdio.h>

coordenada_t generar_posicion_aleatoria(){
  coordenada_t posicion;
  posicion.fil = rand() % MAX_FILAS;
  posicion.col = rand() % MAX_COLUMNAS;
  return posicion;
}

bool posicion_ocupada(juego_t *juego, coordenada_t posicion){
  bool ocupado = false;
  if(posicion.fil == juego->mozo.posicion.fil && posicion.col == juego->mozo.posicion.col){
    ocupado = true;
  }
  if(posicion.fil == juego->cocina.posicion.fil && posicion.col == juego->cocina.posicion.col){
    ocupado = true;
  }
  for(int i = 0; i < juego->cantidad_herramientas; i++){
    if(posicion.fil == juego->herramientas[i].posicion.fil && posicion.col == juego->herramientas[i].posicion.col){
      ocupado = true;
      break;
    }
  }
  for(int i = 0; i < juego->cantidad_obstaculos; i++){
    if(posicion.fil == juego->obstaculos[i].posicion.fil && posicion.col == juego->obstaculos[i].posicion.col){
      ocupado = true;
      break;
    }
  }
  for(int i = 0; i < juego->cantidad_mesas; i++){
    for(int j = 0; j < juego->mesas[i].cantidad_lugares; j++){
      if(posicion.fil == juego->mesas[i].posicion[j].fil && posicion.col == juego->mesas[i].posicion[j].col){
        ocupado = true;
        break;
      }
    }
  }
  return ocupado;
}

bool es_accion_valida(char accion){
  return (accion == ARRIBA || accion == ABAJO || accion == DERECHA || accion == IZQUIERDA || accion == AGARRA_SUELTA_MOPA || accion == TOMAR_PEDIDO || accion == ACTIVAR_PATINES);
}

bool es_posicion_valida(juego_t *juego, coordenada_t nueva_posicion){
  bool es_valida = true;
  if(nueva_posicion.fil < 0 || nueva_posicion.fil >= MAX_FILAS || nueva_posicion.col < 0 || nueva_posicion.col >= MAX_COLUMNAS){
    es_valida = false;
  }
  else{
    for(int i = 0; i < juego->cantidad_mesas && es_valida; i++){
      for(int j = 0; j < juego->mesas[i].cantidad_lugares && es_valida; j++){
        if(nueva_posicion.fil == juego->mesas[i].posicion[j].fil && nueva_posicion.col == juego->mesas[i].posicion[j].col){
          es_valida = false;
        }
      }
    }
  }
  return es_valida;
}

bool espacio_alrededor_mesa_libre(juego_t *juego, coordenada_t posicion, int columna, int fila){
  bool espacio_libre = true;
  for(int i = posicion.fil - 1; i <= posicion.fil + fila && espacio_libre; i++){
    for(int j = posicion.col - 1; j <= posicion.col + columna && espacio_libre; j++){
      if(i < 0 || i >= MAX_FILAS || j < 0 || j >= MAX_COLUMNAS){
        espacio_libre = false;
      }
      else if(posicion_ocupada(juego, (coordenada_t){i, j})){
        espacio_libre = false;
      }
    }
  }
  return espacio_libre;
}

bool posicion_valida_para_mopa(juego_t *juego, coordenada_t posicion){
  bool es_valida = true;
  if(posicion.fil == juego->cocina.posicion.fil && posicion.col == juego->cocina.posicion.col){
    es_valida = false;
  }
  for(int i = 0; i < juego->cantidad_herramientas && es_valida; i++){
    if(juego->herramientas[i].posicion.fil == posicion.fil && juego->herramientas[i].posicion.col == posicion.col){
      es_valida = false;
    }
  }
  for(int i = 0; i < juego->cantidad_obstaculos && es_valida; i++){
    if(juego->obstaculos[i].posicion.fil == posicion.fil && juego->obstaculos[i].posicion.col == posicion.col){
      es_valida = false;
    }
  }
  return es_valida;
}

void verificar_interaccion_mopa(juego_t *juego){
  if(!juego->mozo.tiene_mopa && !juego->mozo.patines_puestos){
    for(int i = 0; i < juego->cantidad_herramientas; i++){
      if(juego->herramientas[i].tipo == MOPA && juego->herramientas[i].posicion.fil == juego->mozo.posicion.fil && juego->herramientas[i].posicion.col == juego->mozo.posicion.col) {
        printf("¿Queres agarrar la mopa? (Presiona 'O' para agarrarla)\n");
      }
    }
  }
}

void pedir_jugada(char *accion){
  bool accion_valida = false;
  while (!accion_valida) {
    printf("Haz un movimiento 'A/W/S/D': \n");
    scanf(" %c", accion);
    if(es_accion_valida(*accion)){
      accion_valida = true;
    }
    else{
      printf("Por favor ingrese una accion valida.\n");
    }
  }
}

int distancia_manhattan(coordenada_t punto1, coordenada_t punto2){
  int distancia;
  distancia = abs(punto1.fil - punto2.fil) + abs(punto1.col - punto2.col);
  return distancia;
}

bool movimiento_multiplo_quince(juego_t *juego){
  return(juego->movimientos % 15 == 0 && juego->movimientos != 0);
}

bool movimiento_multiplo_veinticinco(juego_t *juego){
  return(juego->movimientos % 25 == 0 && juego->movimientos != 0);
}

int cantidad_aleatoria_comensales(){
  int numero_comensales = rand() % 4 + 1;
  return numero_comensales;
}

int cantidad_aleatoria_paciencia(){
  int numero_paciencia = rand() % 101 + 100;
  return numero_paciencia;
}

int numero_aleatorio_pedido(){
  int numero_pedido = rand() % 4 + 1;
  return numero_pedido;
}

char obtener_plato(int numero_pedido){
  switch (numero_pedido){
    case 1: return MILANESA_NAPOLITANA;
    case 2: return HAMBURGUESA;
    case 3: return PARRILLA;
    case 4: return RATATOUILLE;
    default: return ' ';
  }
}

int obtener_tiempo_preparacion(char plato){
  switch (plato){
    case MILANESA_NAPOLITANA: return TIEMPO_PREPARACION_NAPOLITANA;
    case HAMBURGUESA: return TIEMPO_PREPARACION_HAMBURGUESA;
    case PARRILLA: return TIEMPO_PREPARACION_PARRILLA;
    case RATATOUILLE: return TIEMPO_PREPARACION_RATATOUILLE;
    default: return 0;
  }
}

bool cucaracha_cerca_mesa(juego_t *juego, mesa_t mesa){
  bool cucaracha_cerca = false;
  for(int i = 0; i < mesa.cantidad_lugares; i++){
    coordenada_t posicion_lugar = mesa.posicion[i];
    for(int j = 0; j < juego->cantidad_obstaculos; j++){
      if(juego->obstaculos[j].tipo == CUCARACHAS){
        int distancia = distancia_manhattan(posicion_lugar, juego->obstaculos[j].posicion);
        if(distancia <= 2){
          cucaracha_cerca = true;
          break;         
        }
      }
    }
  }
  return cucaracha_cerca;
}

int linguini_sobre_charco(juego_t *juego){
  int indice_charco = NO_HAY_CHARCO;
  for(int i = 0; i < juego->cantidad_obstaculos; i++){
    if(juego->obstaculos[i].tipo == CHARCOS && juego->obstaculos[i].posicion.fil == juego->mozo.posicion.fil && juego->obstaculos[i].posicion.col == juego->mozo.posicion.col){
      indice_charco = i;
      break;
    }
  }
  return indice_charco;
}

void linguini_limpia_charco(juego_t *juego){
  int indice_charco = linguini_sobre_charco(juego);
  if(juego->mozo.tiene_mopa && indice_charco != NO_HAY_CHARCO){
    juego->obstaculos[indice_charco] = juego->obstaculos[juego->cantidad_obstaculos - 1];
    juego->cantidad_obstaculos--;
  }
}

void linguini_pierde_plato_charco(juego_t *juego){
  int indice_charco = linguini_sobre_charco(juego);
  if(indice_charco != NO_HAY_CHARCO && !juego->mozo.tiene_mopa && juego->mozo.cantidad_bandeja > 0){
    for(int i = 0; i < juego->mozo.cantidad_bandeja; i++){
      int id_mesa = juego->mozo.bandeja[i].id_mesa; 

      if(juego->mesas[id_mesa].cantidad_comensales > 0){
        juego->mesas[id_mesa].cantidad_comensales = 0;  
        juego->mesas[id_mesa].paciencia = 0;            
        juego->mesas[id_mesa].pedido_tomado = false;
      }
    }
    juego->mozo.cantidad_bandeja = 0; 
  }
}

bool linguini_cerca_mesa(coordenada_t posicion_linguini, mesa_t mesa){
  bool esta_cerca = false;
  for(int i = 0; i < mesa.cantidad_lugares; i++){
    if(distancia_manhattan(posicion_linguini, mesa.posicion[i]) == 1){
      esta_cerca = true;
      break;
    }
  }
  return esta_cerca;
}

void verificar_comensales_y_paciencia_mesas(juego_t *juego){
  for (int i = 0; i < juego->cantidad_mesas; i++){
    if (juego->mesas[i].cantidad_comensales > 0){
      int fila_mesa = juego->mesas[i].posicion[0].fil;
      int columna_mesa = juego->mesas[i].posicion[0].col;
      if(juego->mesas[i].paciencia <= 20){
        printf("ADVERTENCIA! Mesa %d en (%d, %d) con %d comensales tiene poca paciencia %d. Pierde el pedido/comensales si llega a 0. \n", i + 1, fila_mesa, columna_mesa, juego->mesas[i].cantidad_comensales, juego->mesas[i].paciencia);
      }
      else{
        printf("Mesa %d en (%d, %d) tiene %d comensales, la paciencia es: %d\n", i + 1, fila_mesa, columna_mesa, juego->mesas[i].cantidad_comensales, juego->mesas[i].paciencia);   
      }
    }
    if(juego->mesas[i].paciencia <= 0){
      juego->mesas[i].cantidad_comensales = 0;
      juego->mesas[i].paciencia = 0;
    }
  }
}

void verificar_interaccion_patines(juego_t *juego){
  if (juego->mozo.patines_puestos == true){
    printf("Tenes un par de patines, para activarlos toca 'P'. \n");
  }
}

void verificar_linguini_pedidos(juego_t *juego){
  if(juego->mozo.cantidad_pedidos > 0){
    for(int i = 0;  i < juego->mozo.cantidad_pedidos; i++){
      printf("Linguini tiene el pedido de la mesa %d. Pedidos: %s. Tiempo de preparacion %d movimientos. \n", juego->mozo.pedidos[i].id_mesa + 1, juego->mozo.pedidos[i].platos, juego->mozo.pedidos[i].tiempo_preparacion);
    }
  }
  else{
    printf("Linguini no tiene pedidos\n");
  }
  for(int i = 0; i < juego->cantidad_mesas; i++){
    if(linguini_cerca_mesa(juego->mozo.posicion, juego->mesas[i]) && juego->mesas[i].cantidad_comensales > 0 && !juego->mesas[i].pedido_tomado){
      printf("Para tomar el pedido de la mesa %d presiona 'T' \n", i + 1);
    }
  } 
}

void verificar_pedido_cocina(juego_t *juego){
  if(juego->cocina.cantidad_preparacion > 0){
    for(int i = 0; i < juego->cocina.cantidad_preparacion; i++){
      pedido_t pedido_actual = juego->cocina.platos_preparacion[i];
      if(pedido_actual.tiempo_preparacion > 0){
        printf("La cocina está preparando el pedido de la mesa %d. Faltan %d movimientos para que esté listo.\n", pedido_actual.id_mesa + 1, pedido_actual.tiempo_preparacion);
      }
    }
  }
  else{
    printf("No hay pedidos en preparación en la cocina.\n");
  }
  if(juego->cocina.cantidad_listos > 0){
    for(int i = 0; i < juego->cocina.cantidad_listos; i++){
      printf("El pedido de la mesa %d está listo en la cocina.\n", juego->cocina.platos_listos[i].id_mesa + 1);
    }
  }
}

void verificar_plato_cocina(juego_t *juego){
  if(juego->mozo.cantidad_bandeja > 0){
    printf("Linguini tiene los platos de las mesas: ");
    for (int i = 0; i < juego->mozo.cantidad_bandeja; i++){
      printf("%d", juego->mozo.bandeja[i].id_mesa + 1);
      if (i < juego->mozo.cantidad_bandeja - 1){
        printf(", ");
      }
    }
    printf(".\n");
  }
  else{
    printf("Linguini no tiene platos en su bandeja.\n");
  }
}

void elimina_pedidos_si_comensales_se_van(juego_t *juego, int id_mesa){
  for(int i = 0; i < juego->mozo.cantidad_pedidos; i++){
    if(juego->mozo.pedidos[i].id_mesa == id_mesa){
      for(int j = i; j < juego->mozo.cantidad_pedidos - 1; j++){
        juego->mozo.pedidos[j] = juego->mozo.pedidos[j + 1];
      }
      juego->mozo.cantidad_pedidos--;
      i--;
    }
  }
}

void elimina_bandejas_si_comensales_se_van(juego_t *juego, int id_mesa){
  for(int i = 0; i < juego->mozo.cantidad_bandeja; i++){
    if(juego->mozo.bandeja[i].id_mesa == id_mesa){
      for(int j = i; j < juego->mozo.cantidad_bandeja - 1; j++){
        juego->mozo.bandeja[j] = juego->mozo.bandeja[j + 1];
      }
      juego->mozo.cantidad_bandeja--;
      i--;
    }
  }
}

void elimina_platos_preparacion_comensales_se_van(juego_t *juego, int id_mesa){
  for(int i = 0; i < juego->cocina.cantidad_preparacion; i++){
    if(juego->cocina.platos_preparacion[i].id_mesa == id_mesa){
      for(int j = i; j < juego->cocina.cantidad_preparacion - 1; j++){
        juego->cocina.platos_preparacion[j] = juego->cocina.platos_preparacion[j + 1];
      }
      juego->cocina.cantidad_preparacion--;
      i--;
    }
  }
}

void elimina_platos_listos_comensales_se_van(juego_t *juego, int id_mesa){
  for(int i = 0; i < juego->cocina.cantidad_listos; i++){
    if(juego->cocina.platos_listos[i].id_mesa == id_mesa){
      for(int j = i; j < juego->cocina.cantidad_listos - 1; j++){
        juego->cocina.platos_listos[j] = juego->cocina.platos_listos[j + 1];
      }
      juego->cocina.cantidad_listos--;
      i--;
    }
  }
}

void comensales_se_van(juego_t *juego, int id_mesa){
  elimina_pedidos_si_comensales_se_van(juego, id_mesa);
  elimina_bandejas_si_comensales_se_van(juego, id_mesa);
  elimina_platos_preparacion_comensales_se_van(juego, id_mesa);
  elimina_platos_listos_comensales_se_van(juego, id_mesa);
}

void actualizar_paciencia_mesas(juego_t *juego){
  for(int i = 0; i < juego->cantidad_mesas; i++){
    if(juego->mesas[i].cantidad_comensales > 0){
      juego->mesas[i].paciencia--;
    }
    if(cucaracha_cerca_mesa(juego, juego->mesas[i])){
      juego->mesas[i].paciencia -= 1; 
    }
    if(juego->mesas[i].paciencia <= 0){
      comensales_se_van(juego, i);
      juego->mesas[i].cantidad_comensales = 0;
      juego->mesas[i].paciencia = 0;
    }
  }
}