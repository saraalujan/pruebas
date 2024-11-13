#include "inicializacion.h"
#include "restaurant.h"
#include "utilidades.h"
#include <stdbool.h>
#include <stdlib.h>

void inicializar_mozo_linguini(juego_t *juego){
  coordenada_t posicion_mozo_linguini;
  bool esta_ocupada = true;
  while (esta_ocupada){
    posicion_mozo_linguini = generar_posicion_aleatoria();
    esta_ocupada = posicion_ocupada(juego, posicion_mozo_linguini);
  }
  juego->mozo.posicion = posicion_mozo_linguini;
  juego->mozo.cantidad_patines = CANT_PATINES_INICIAL;
  juego->mozo.cantidad_bandeja = CANT_BANDEJA_INICIAL;
  juego->mozo.cantidad_pedidos = CANT_PEDIDOS_INICIAL;
  juego->mozo.tiene_mopa = false;
  juego->mozo.patines_puestos = false;
}

void inicializar_mesas_individuales(juego_t *juego) {
  coordenada_t posicion_mesa_individual;
  for(int i = 0; i < CANT_MESAS_INDIVIDUALES; i++){
    bool esta_ocupada = true;
    while (esta_ocupada){
      posicion_mesa_individual = generar_posicion_aleatoria();
      if(espacio_alrededor_mesa_libre(juego, posicion_mesa_individual, 1, 1)){
        juego->mesas[juego->cantidad_mesas].posicion[0] = posicion_mesa_individual;
        juego->mesas[juego->cantidad_mesas].cantidad_lugares = CANT_LUGARES_INDIVIDUAL;
        juego->mesas[juego->cantidad_mesas].cantidad_comensales = CANT_COMENSALES_INICIAL;
        juego->mesas[juego->cantidad_mesas].paciencia = PACIENCIA_INICIAL;
        juego->mesas[juego->cantidad_mesas].pedido_tomado = false;
        juego->cantidad_mesas++;
        esta_ocupada = false;
      }
    }
  }
}

void inicializar_mesas_grupales(juego_t *juego){
  coordenada_t posicion_mesa_grupal;
  for(int i = 0; i < CANT_MESAS_GRUPALES; i++){
    bool esta_ocupada = true;
    while(esta_ocupada){
      posicion_mesa_grupal = generar_posicion_aleatoria();
      if(posicion_mesa_grupal.fil + 1 < MAX_FILAS && posicion_mesa_grupal.col + 1 < MAX_COLUMNAS && espacio_alrededor_mesa_libre(juego, posicion_mesa_grupal, 2, 2)){
        for (int j = 0; j < MAX_COMENSALES; j++) {
          juego->mesas[juego->cantidad_mesas].posicion[j] = (coordenada_t){posicion_mesa_grupal.fil + j / 2, posicion_mesa_grupal.col + j % 2};
        }
        juego->mesas[juego->cantidad_mesas].cantidad_lugares = MAX_COMENSALES;
        juego->mesas[juego->cantidad_mesas].cantidad_comensales = CANT_COMENSALES_INICIAL;
        juego->mesas[juego->cantidad_mesas].paciencia = PACIENCIA_INICIAL;
        juego->mesas[juego->cantidad_mesas].pedido_tomado = false;
        juego->cantidad_mesas++;
        esta_ocupada = false;
      }
    }
  }
}

void inicializar_cocina(juego_t *juego){
  coordenada_t posicion_cocina;
  bool esta_ocupada = true;
  while(esta_ocupada){
    posicion_cocina = generar_posicion_aleatoria();
    esta_ocupada = posicion_ocupada(juego, posicion_cocina);
  }
  juego->cocina.posicion = posicion_cocina;
  juego->cocina.platos_preparacion = NULL;
  juego->cocina.cantidad_preparacion = CANT_PEDIDOS_INICIAL;
  juego->cocina.platos_listos = NULL;
  juego->cocina.cantidad_listos = CANT_BANDEJA_INICIAL;
}

void inicializar_mopa(juego_t *juego){
  coordenada_t posicion_mopa;
  bool esta_ocupada = true;
  while(esta_ocupada){
    posicion_mopa = generar_posicion_aleatoria();
    esta_ocupada = posicion_ocupada(juego, posicion_mopa);
  }
  if(juego->cantidad_herramientas < MAX_HERRAMIENTAS){
    juego->herramientas[juego->cantidad_herramientas].posicion = posicion_mopa;
    juego->herramientas[juego->cantidad_herramientas].tipo = MOPA;
    juego->cantidad_herramientas++;
  }
}

void inicializar_monedas(juego_t *juego){
  coordenada_t posicion_monedas;
  for(int i = 0; i < CANT_MONEDAS; i++){
    bool esta_ocupada = true;
    while(esta_ocupada){
      posicion_monedas = generar_posicion_aleatoria();
      esta_ocupada = posicion_ocupada(juego, posicion_monedas);
    }
    if(juego->cantidad_herramientas < MAX_HERRAMIENTAS){
      juego->herramientas[juego->cantidad_herramientas].tipo = MONEDAS;
      juego->herramientas[juego->cantidad_herramientas].posicion = posicion_monedas;
      juego->cantidad_herramientas++;
    }
  }
}

void inicializar_patines(juego_t *juego){
  coordenada_t posicion_patines;
  for(int i = 0; i < CANT_PATINES; i++){
    bool esta_ocupada = true;
    while(esta_ocupada){
      posicion_patines = generar_posicion_aleatoria();
      esta_ocupada = posicion_ocupada(juego, posicion_patines);
    }
    if (juego->cantidad_herramientas < MAX_HERRAMIENTAS){
      juego->herramientas[juego->cantidad_herramientas].tipo = PATINES;
      juego->herramientas[juego->cantidad_herramientas].posicion = posicion_patines;
      juego->cantidad_herramientas++;
    }
  }
}

void inicializar_charcos(juego_t *juego){
  coordenada_t posicion_charcos;
  for(int i = 0; i < CANT_CHARCOS; i++){
    bool esta_ocupada = true;
    while(esta_ocupada){
      posicion_charcos = generar_posicion_aleatoria();
      esta_ocupada = posicion_ocupada(juego, posicion_charcos);
    }
    if(juego->cantidad_obstaculos < MAX_OBSTACULOS){
      juego->obstaculos[juego->cantidad_obstaculos].tipo = CHARCOS;
      juego->obstaculos[juego->cantidad_obstaculos].posicion = posicion_charcos;
      juego->cantidad_obstaculos++;
    }
  }
}

void inicializar_mesas(juego_t *juego){
  inicializar_mesas_individuales(juego);
  inicializar_mesas_grupales(juego);
}

void inicializar_herramientas(juego_t *juego){
  inicializar_mopa(juego);
  inicializar_monedas(juego);
  inicializar_patines(juego);
}

void inicializar_obstaculos(juego_t *juego){
  inicializar_charcos(juego);
}

void inicializar_terreno(char matriz_terreno[MAX_FILAS][MAX_COLUMNAS]){
  for(int i = 0; i < MAX_FILAS; i++){
    for(int j = 0; j < MAX_COLUMNAS; j++){
      matriz_terreno[i][j] = VACIO;
    }
  }
}