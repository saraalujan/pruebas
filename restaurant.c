#include "restaurant.h"
#include "inicializacion.h"
#include "constantes.h"
#include "utilidades.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DINERO_PARA_GANAR 150000
#define MAX_MOVIMIENTOS_PARTIDA 200
#define HERRAMIENTAS_INICIALES 0
#define MESAS_INICIALES 0
#define OBSTACULOS_INICIALES 0
#define DINERO_INICIAL 0
#define MOVIMIENTOS_INICIALES 0
#define RATA "\U0001f400"

/*Pre: La matriz terreno tiene que estar inicializada previamente
Post: Se imprime el terreno para vista del jugador con la estructura que pide el trabajo
*/
void imprimir_terreno(char matriz_terreno[MAX_FILAS][MAX_COLUMNAS]){
  for(int i = 0; i < MAX_FILAS; i++){
    for(int j = 0; j < MAX_COLUMNAS; j++){
      printf("| %c ", matriz_terreno[i][j]);
    }
    printf("| \n");
  }
  printf("\n");
}

/*Pre: Las mesas tienen que estar inicializadas previamente
Post: Imprime las mesas al azar para vista del jugador con la letra T
*/
void imprimir_mesas(juego_t juego, char matriz_terreno[MAX_FILAS][MAX_COLUMNAS]){
  for(int i = 0; i < juego.cantidad_mesas; i++){
    int comensales_restantes = juego.mesas[i].cantidad_comensales;
    for(int j = 0; j < juego.mesas[i].cantidad_lugares; j++){
      coordenada_t posicion_mesa = juego.mesas[i].posicion[j];
      if(comensales_restantes > 0){
        matriz_terreno[posicion_mesa.fil][posicion_mesa.col] = COMENSALES;
        comensales_restantes--;
      }
      else{
        matriz_terreno[posicion_mesa.fil][posicion_mesa.col] = MESAS;
      }
    }
  }
}

/*Pre: La herramienta mopa tiene que estar inicializada previamente
Post: Imprime la mopa al azar para vista del jugador con la letra O
*/
void imprimir_mopa(juego_t juego, char matriz_terreno[MAX_FILAS][MAX_COLUMNAS]){
  for(int i = 0; i < juego.cantidad_herramientas; i++){
    if(juego.herramientas[i].tipo == MOPA){
      matriz_terreno[juego.herramientas[i].posicion.fil][juego.herramientas[i].posicion.col] = MOPA;
    }
  }
}

/*Pre: La herramienta moneda tiene que estar inicializada previamente
Post: Imprime las monedas al azar para vista del jugador con la letra M
*/
void imprimir_monedas(juego_t juego, char matriz_terreno[MAX_FILAS][MAX_COLUMNAS]){
  for(int i = 0; i < juego.cantidad_herramientas; i++){
    if(juego.herramientas[i].tipo == MONEDAS){
      matriz_terreno[juego.herramientas[i].posicion.fil][juego.herramientas[i].posicion.col] = MONEDAS;
    }
  }
}

/*Pre: La herramienta patin tiene que estar inicializada previamente
Post: Se imprimen los patines al azar para vista del jugador con la letra P
*/
void imprimir_patines(juego_t juego, char matriz_terreno[MAX_FILAS][MAX_COLUMNAS]){
  for(int i = 0; i < juego.cantidad_herramientas; i++){
    if(juego.herramientas[i].tipo == PATINES){
      matriz_terreno[juego.herramientas[i].posicion.fil][juego.herramientas[i].posicion.col] = PATINES;
    }
  }
}

/*Pre: Tienen que poder imprimirse las herramientas(monedas, patines y mopa)
Post: Se imprimen las herramientas al azar para vista del jugador con sus respectivas letras
*/
void imprimir_herramientas(juego_t juego, char matriz_terreno[MAX_FILAS][MAX_COLUMNAS]){
  imprimir_mopa(juego, matriz_terreno);
  imprimir_monedas(juego, matriz_terreno);
  imprimir_patines(juego, matriz_terreno);
}

/*Pre: El obstaculo tiene que estar inicializado previamente
Post: Se imprime el obstaculo al azar para vista del jugador con la letra H 
*/
void imprimir_charcos(juego_t juego, char matriz_terreno[MAX_FILAS][MAX_COLUMNAS]){
  for(int i = 0; i < juego.cantidad_obstaculos; i++){
    if(juego.obstaculos[i].tipo == CHARCOS){
      matriz_terreno[juego.obstaculos[i].posicion.fil][juego.obstaculos[i].posicion.col] = CHARCOS;
    }
  }
}

/*Pre: Se generan cada 15 movimientos validos.
Post: Se imprime el obstaculo al azar para vista del jugador con la letra U
*/
void imprimir_cucarachas(juego_t juego, char matriz_terreno[MAX_FILAS][MAX_COLUMNAS]){
  for(int i = 0; i < juego.cantidad_obstaculos; i++){
    if(juego.obstaculos[i].tipo == CUCARACHAS){
      matriz_terreno[juego.obstaculos[i].posicion.fil][juego.obstaculos[i].posicion.col] = CUCARACHAS;
    }
  }
}

/*Pre: Tienen que poder imprimirse los obstaculos(charcos por ahora)
Post: Se imprimen los obstaculos al azar para vista del jugador con sus respectivas letras
*/
void imprimir_obstaculos(juego_t juego, char matriz_terreno[MAX_FILAS][MAX_COLUMNAS]){
  imprimir_charcos(juego, matriz_terreno);
  imprimir_cucarachas(juego, matriz_terreno);
}

/*Pre: Se pide un movimiento valido (A/W/S/D)
Post: Si es valida se imprime el movimiento de Linguini.
*/
void mover_linguini(juego_t *juego, char accion){
  coordenada_t nueva_posicion = juego->mozo.posicion;
  if(accion == ARRIBA){
    nueva_posicion.fil--;
  }
  else if(accion == ABAJO){
    nueva_posicion.fil++;
  }
  else if(accion == DERECHA){
    nueva_posicion.col++;
  }
  else if(accion == IZQUIERDA){
    nueva_posicion.col--;
  }
  if(es_posicion_valida(juego, nueva_posicion)){
    juego->mozo.posicion = nueva_posicion;
    juego->movimientos++;
    actualizar_paciencia_mesas(juego);
  }
}

/*Pre: Linguini tiene que estar sobre la mopa
Post: La mopa es agarrada por Linguini, y se elimina de la matriz
*/
void agarrar_mopa(juego_t *juego){
  for(int i = 0; i < juego->cantidad_herramientas; i++){
    if(juego->herramientas[i].tipo == MOPA && juego->herramientas[i].posicion.fil == juego->mozo.posicion.fil && juego->herramientas[i].posicion.col == juego->mozo.posicion.col){
      juego->mozo.tiene_mopa = true;
      juego->herramientas[i] = juego->herramientas[juego->cantidad_herramientas - 1];
      juego->cantidad_herramientas--;
      return;
    }
  }
}

/*Pre: Linguini puede estar en cualquier posicion libre
Post: Linguini suelta la mopa y se agrega a la matriz
*/
void soltar_mopa(juego_t *juego){
  if(posicion_valida_para_mopa(juego, juego->mozo.posicion)){
    juego->herramientas[juego->cantidad_herramientas].tipo = MOPA;
    juego->herramientas[juego->cantidad_herramientas].posicion = juego->mozo.posicion;
    juego->cantidad_herramientas++;
    juego->mozo.tiene_mopa = false;
  }
  else{
    printf("Posicion Invalida. Pruebe en una libre. Toque enter e intente de nuevo.\n");
    getchar();
    getchar();
  }
}

/*Pre: Estando sobre la mopa o estando en una posicion libre se pregunta si quiere agarrar/soltar la mopa
Post: Si Linguini tiene la mopa, se intenta soltar
Si no tiene la mopa, se intenta agarrar
*/
void interaccion_mopa(juego_t *juego){
  if(juego->mozo.tiene_mopa){
    soltar_mopa(juego);
  }
  else{
    agarrar_mopa(juego);
  }
}

/*Pre: Cada 15 movimientos se va a dar una cantidad aleatoria de comensales.
Post: Se van a asignar a las mesas libres la cantidad que se haya dado si la cantidad de comensales es compatible con la de la mesa.
*/
void llegada_de_comensales(juego_t *juego){
  if(!movimiento_multiplo_quince(juego)){
    return;
  }
  int comensales = cantidad_aleatoria_comensales();
  for(int i = 0;i < juego->cantidad_mesas; i++){
    if(juego->mesas[i].cantidad_comensales == 0){
      if(juego->mesas[i].cantidad_lugares == 1 && comensales == 1){
        juego->mesas[i].cantidad_comensales = comensales;
        juego->mesas[i].paciencia = cantidad_aleatoria_paciencia();
        break;
      }
      else if(juego->mesas[i].cantidad_lugares == 4 && comensales <= 4){
        juego->mesas[i].cantidad_comensales = comensales;
        juego->mesas[i].paciencia = cantidad_aleatoria_paciencia();
        break;
      }
    }
  }
}

/*Pre: Se recorren las herramientas para comparar si el tipo de herramienta y su posicion coinciden con la de Linguini.
Post: Linguini recolecta la moneda incrementando el dinero actual que tiene y elimina del vector a la moneda.
*/
void recolectar_moneda(juego_t *juego){
  for(int i = 0; i < juego->cantidad_herramientas; i++){
    if(juego->herramientas[i].tipo == MONEDAS && juego->herramientas[i].posicion.fil == juego->mozo.posicion.fil && juego->herramientas[i].posicion.col == juego->mozo.posicion.col){
      juego->dinero += DINERO_MONEDA_EXTRA;
      juego->herramientas[i] = juego->herramientas[juego->cantidad_herramientas -1];
      juego->cantidad_herramientas--;
      i--;
    }
  }
}

/*Pre: Cada 25 movimientos se genera una posicion aleatoria para las cucarachas y se generan si hay espacio en el arreglo de obstaculos.
Post: Se ubica la cucaracha en un lugar disponible y se actualiza el numero de obstaculos. 
*/
void generar_cucaracha(juego_t *juego){
  if(movimiento_multiplo_veinticinco(juego) && juego->cantidad_obstaculos < MAX_OBSTACULOS){
    coordenada_t posicion_cucaracha; 
    bool esta_ocupada = true;
    while(esta_ocupada){
      posicion_cucaracha = generar_posicion_aleatoria();
      esta_ocupada = posicion_ocupada(juego, posicion_cucaracha);
    }
    juego->obstaculos[juego->cantidad_obstaculos].posicion = posicion_cucaracha;
    juego->obstaculos[juego->cantidad_obstaculos].tipo = CUCARACHAS;
    juego->cantidad_obstaculos++;
  }
}

/*Pre: Se recorren la cantidad de obstaculos para comparar si el tipo de obstaculo y la posicion deee Linguini es la misma.
Post: Linguini aplasta la cucaracha haciendola desaparecer del vector y tambien del arreglo obstaculo
*/
void aplastar_cucaracha(juego_t *juego){
  for(int i = 0; i < juego->cantidad_obstaculos; i++){
    if(juego->obstaculos[i].tipo == CUCARACHAS && juego->obstaculos[i].posicion.fil == juego->mozo.posicion.fil && juego->obstaculos[i].posicion.col == juego->mozo.posicion.col){
      juego->obstaculos[i] = juego->obstaculos[juego->cantidad_obstaculos -1];
      juego->cantidad_obstaculos--;
      i--;
    }
  }
}

/*Pre: Se verifica si Linguini esta a distancia 1 Manhattan de una mesa con comensales y sin pedido tomado.
Post: Toma el pedido de la mesa si toca "T" e incrementa mozo.cantidad_pedidos, pone el pedido de la mesa en true haciendo que sea una mesa con pedido tomado. 
*/
void linguini_toma_pedido(juego_t *juego){
  if(juego->mozo.tiene_mopa){
    return;
  }
  for(int i = 0; i < juego->cantidad_mesas; i++){
    if(linguini_cerca_mesa(juego->mozo.posicion, juego->mesas[i]) && juego->mesas[i].cantidad_comensales > 0 && !juego->mesas[i].pedido_tomado){
      int tiempo_maximo_preparacion = 0;
      for(int j = 0; j < juego->mesas[i].cantidad_comensales; j++){
        int numero_pedido = numero_aleatorio_pedido();
        char plato = obtener_plato(numero_pedido);
        int tiempo_preparacion = obtener_tiempo_preparacion(plato);
        juego->mozo.pedidos[juego->mozo.cantidad_pedidos].platos[j] = plato;
        if(tiempo_preparacion > tiempo_maximo_preparacion){
          tiempo_maximo_preparacion = tiempo_preparacion;
        }
      }
      juego->mozo.pedidos[juego->mozo.cantidad_pedidos].id_mesa = i;
      juego->mozo.pedidos[juego->mozo.cantidad_pedidos].tiempo_preparacion = tiempo_maximo_preparacion;
      juego->mozo.cantidad_pedidos++;
      juego->mesas[i].pedido_tomado = true;
    }
  }
}

/*Pre: Se verifica que la posicion de Linguini y de la cocina sean la misma, y que Linguini tenga pedido/s con el. 
Post: Linguini deja el pedido/s en la cocina y este arranca a ser preparado por la cocina. Linguini vacia su cantidad de pedidos a 0.
*/
void linguini_deja_pedido_cocina(juego_t *juego){
  if(juego->mozo.tiene_mopa){
      return;
  }
  if(juego->mozo.posicion.fil == juego->cocina.posicion.fil && juego->mozo.posicion.col == juego->cocina.posicion.col){
    if(juego->mozo.cantidad_pedidos > 0){
      int nueva_cantidad = juego->cocina.cantidad_preparacion + juego->mozo.cantidad_pedidos;
      pedido_t *nueva_preparacion = realloc(juego->cocina.platos_preparacion, (size_t)nueva_cantidad * sizeof(pedido_t));
      if(nueva_preparacion == NULL){
        return; 
      }
      juego->cocina.platos_preparacion = nueva_preparacion;
      for(int i = 0; i < juego->mozo.cantidad_pedidos; i++){
        juego->cocina.platos_preparacion[juego->cocina.cantidad_preparacion + i] = juego->mozo.pedidos[i];
        juego->cocina.platos_preparacion[juego->cocina.cantidad_preparacion + i].tiempo_preparacion = juego->mozo.pedidos[i].tiempo_preparacion;
      }
      juego->cocina.cantidad_preparacion = nueva_cantidad;
      juego->mozo.cantidad_pedidos = 0;
    }
  }
}

/*Pre: Se toma en cuenta que hay platos en preparacion y que la posicion de Linguini este afuera de la cocina. 
Post: Cambia el estado de preparado a listo despues de cumplir con el tiempo de preparacion necesario y se elimina de los platos en preparacion, Se incrementa en cantidad listos y decreenta en cantidad preparacion.
*/
void actualizar_platos_cocina(juego_t *juego) {
    bool fallo_de_memoria = false;
    bool linguini_fuera_de_cocina = juego->mozo.posicion.fil != juego->cocina.posicion.fil || juego->mozo.posicion.col != juego->cocina.posicion.col;

    if (linguini_fuera_de_cocina) {
        for (int i = 0; i < juego->cocina.cantidad_preparacion && !fallo_de_memoria; i++) {
            if (juego->cocina.platos_preparacion[i].tiempo_preparacion > 0) {
                juego->cocina.platos_preparacion[i].tiempo_preparacion--;
            }

            if (juego->cocina.platos_preparacion[i].tiempo_preparacion == 0) {
                // Reservamos memoria para los platos listos
                pedido_t *nueva_lista = realloc(juego->cocina.platos_listos, ((size_t)juego->cocina.cantidad_listos + 1) * sizeof(pedido_t));
                if (nueva_lista == NULL) {
                    fallo_de_memoria = true;
                    break;
                }

                // Mover el plato de preparación a los platos listos
                juego->cocina.platos_listos = nueva_lista;
                juego->cocina.platos_listos[juego->cocina.cantidad_listos] = juego->cocina.platos_preparacion[i];
                juego->cocina.cantidad_listos++;

                // Liberar el plato en preparación
                free(&juego->cocina.platos_preparacion[i]);

                // Desplazar los platos en preparación
                for (int j = i; j < juego->cocina.cantidad_preparacion - 1; j++) {
                    juego->cocina.platos_preparacion[j] = juego->cocina.platos_preparacion[j + 1];
                }

                juego->cocina.cantidad_preparacion--;

                // Reajustar el tamaño de los platos en preparación
                juego->cocina.platos_preparacion = realloc(juego->cocina.platos_preparacion, (size_t)juego->cocina.cantidad_preparacion * sizeof(pedido_t));
                if (juego->cocina.cantidad_preparacion > 0 && juego->cocina.platos_preparacion == NULL) {
                    fallo_de_memoria = true;
                    break;
                }

                i--;  // Para no saltarse un plato después del desplazamiento
            }
        }
    }
}


/*Pre: Se comparan las posiciones de Linguini y la cocina. Se verifica que la bandeja de Linguini no este llena.
Post: Si hay platos listos en la cocina Linguini los retira decrementando la cantidad de listos en la cocina e incrementando la cantidad de bandejas de Linguini. La memoria de platos_listos se reajusta con los restantes en la cocina.
*/
void linguini_recoge_platos(juego_t *juego){
  if(juego->mozo.tiene_mopa){
    return;
  }
  if(juego->mozo.posicion.fil == juego->cocina.posicion.fil && juego->mozo.posicion.col == juego->cocina.posicion.col){
    while(juego->cocina.cantidad_listos > 0 && juego->mozo.cantidad_bandeja < MAX_BANDEJA){
      juego->mozo.bandeja[juego->mozo.cantidad_bandeja] = juego->cocina.platos_listos[0];
      juego->mozo.cantidad_bandeja++;
      for(int i = 1; i < juego->cocina.cantidad_listos; i++){
        juego->cocina.platos_listos[i - 1] = juego->cocina.platos_listos[i];
      }
      juego->cocina.cantidad_listos--;
      juego->cocina.platos_listos = realloc(juego->cocina.platos_listos, (size_t)juego->cocina.cantidad_listos * sizeof(pedido_t));
      if(juego->cocina.cantidad_listos > 0 && juego->cocina.platos_listos == NULL){
        return;
      }
    }
  }
}

/*Pre: Linguini tiene que estas a distancia 1 manhattan de las mesas. Se recorre las bandejas de Linguini y se compara el id de las mesas.
Post: Entrega el plato a la mesa correspondiente y despues de hacerlo vacia la mesa y el pedido_tomado vuelve a ser false. Se incrementa el dinero dependiendo de si la mesa es grupal o individual.
*/
void linguini_entrega_plato_a_mesa(juego_t *juego, int indice_mesa){
  if(linguini_cerca_mesa(juego->mozo.posicion, juego->mesas[indice_mesa]) && juego->mozo.cantidad_bandeja > 0){
    for(int i = 0; i < juego->mozo.cantidad_bandeja; i++){
      if(juego->mozo.bandeja[i].id_mesa == indice_mesa){
        juego->mesas[indice_mesa].cantidad_comensales = 0;
        juego->mesas[indice_mesa].pedido_tomado = false;
        for(int j = i; j < juego->mozo.cantidad_bandeja - 1; j++){
          juego->mozo.bandeja[j] = juego->mozo.bandeja[j + 1];
        }
        juego->mozo.cantidad_bandeja--;

        if(juego->mesas[indice_mesa].cantidad_lugares == 4){
          juego->dinero += MESA_GRUPAL_PAGA;
        }
        else if(juego->mesas[indice_mesa].cantidad_lugares == 1){
          juego->dinero += MESA_INDIVIDUAL_PAGA;
        }
        break;
      }
    }
  }
}


/*Pre: Se compara si la posicion de Linguini es igual a la posicion de un charco.
Post: Si tiene la mopa lo limpia, si no tiene la mopa y tiene platos listos los pierde, si no hay charco no pasa nada.
*/
void linguini_interaccion_charco(juego_t *juego){
  int indice_charco = linguini_sobre_charco(juego);
  if(indice_charco == NO_HAY_CHARCO){
    return;
  }
  if(juego->mozo.tiene_mopa){
    linguini_limpia_charco(juego);
  }
  else if(juego->mozo.cantidad_bandeja > 0){
    linguini_pierde_plato_charco(juego);
  }
}

/*Pre: Se compara la posicion de Linguini con la de los patines, si ya tiene patines recoletados, y si tiene la mopa. 
Post: Linguini recolecta los patines, los borra del vector herramientas y se modifica patines_puestos de Linguini.
*/
void recolectar_patines(juego_t *juego){
  if(juego->mozo.patines_puestos || juego->mozo.tiene_mopa){
    return;   
  }
  for(int i = 0; i < juego->cantidad_herramientas; i++){
    if(juego->herramientas[i].tipo == PATINES && juego->herramientas[i].posicion.fil == juego->mozo.posicion.fil && juego->herramientas[i].posicion.col == juego->mozo.posicion.col){
      if(!juego->mozo.tiene_mopa){
        juego->mozo.patines_puestos = true;
      }
      juego->mozo.patines_puestos=true;
      juego->herramientas[i] = juego->herramientas[juego->cantidad_herramientas - 1];
      juego->cantidad_herramientas--;
      break;
    }
  }
}

/*Pre: Se verifica si Linguini esta sobre la mopa y tambien si es que tiene patines recolectados. Tambien si no esta sobre la mopa pide direccion de patines.
Post: Si esta encima de la mopa, le da la opcion de tomarla o de ignorarla y continuar con su movimiento. O, si no esta encima de la mopa, elige la direccion donde se va a mover Linguini con los patines.
*/
char pedir_direccion_mozo_patines(juego_t *juego){
  char direccion;
  bool direccion_valida = false;
  for(int i = 0; i < juego->cantidad_herramientas; i++){
    if(juego->herramientas[i].tipo == MOPA && juego->mozo.posicion.fil == juego->herramientas[i].posicion.fil && juego->mozo.posicion.col == juego->herramientas[i].posicion.col){
      char respuesta;
      printf("Estas sobre la mopa. ¿Queres Activarla con los patines puestos? Toca 'O' para agarrarla o 'N' para ignorarla.\n");
      scanf(" %c", &respuesta);
      if(respuesta == AGARRA_SUELTA_MOPA){
        agarrar_mopa(juego);
      }
      else if(respuesta == NO_AGARRA_MOPA_CON_PATINES){
        break;
      }
      break;
    }
  }
  while(!direccion_valida){
    printf("Elige una dirección para moverte con los patines (A/W/S/D): ");
    scanf(" %c", &direccion);
    if(direccion == ARRIBA || direccion == ABAJO || direccion == IZQUIERDA || direccion == DERECHA){
      direccion_valida = true;
    }
    else{
      printf("Direccion no valida. Por favor elige W/A/S/D:\n");
    }
  }
  return direccion;
}

/*Pre: Recibe coordenadas de fila y columna y verifica si alguna de las mesas ocupa esa posicion.
Post: Retorna true si choca y no avanza mas. Retorna false si no choca y sigue avanzando.
*/
bool hay_mesa_para_chocar(juego_t *juego, int fila, int columna){
  bool hay_mesa_choque = false;
  for(int i = 0; i < juego->cantidad_mesas; i ++){
    for(int j = 0; j < juego->mesas[i].cantidad_lugares; j++){
      if(juego->mesas[i].posicion[j].fil == fila && juego->mesas[i].posicion[j].col == columna){
        hay_mesa_choque = true;
        break;
      }
    }
    if(hay_mesa_choque){
      break;
    }
  }
  return hay_mesa_choque;
}

/*Pre: Se verifica si Linguini pasa los limites del terreno o si hay mesa para chocar.
Post: Si choca o pasa limites retorna true y se detiene el movimiento de Linguini con patines, caso contrario retorna false y sigue el movimiento.
*/
bool linguini_patines_choca(juego_t *juego, int proxima_fil, int proxima_col){
  bool linguini_choque;
  if(proxima_fil < 0 || proxima_fil >= MAX_FILAS || proxima_col < 0 || proxima_col >= MAX_COLUMNAS){
    linguini_choque = true;
  }
  else if(hay_mesa_para_chocar(juego, proxima_fil, proxima_col)){
    linguini_choque = true;
  }
  else{
    linguini_choque = false;
  }
  return linguini_choque;
}

/*Pre: Linguini tiene que tener los patines activos.
Post: Si pasa sin la mopa puede aplastar cucarachas y recolectar monedas, pero si pasa con la mopa solo puede limpiar charcos.
*/
void mozo_patines_interactua_elementos(juego_t *juego){
  if(juego->mozo.tiene_mopa){
    linguini_limpia_charco(juego);
  }
  else{
    for(int i = 0; i < juego->cantidad_obstaculos; i++){
      if(juego->obstaculos[i].posicion.fil == juego->mozo.posicion.fil && juego->obstaculos[i].posicion.col == juego->mozo.posicion.col){
        if(juego->obstaculos[i].tipo == CHARCOS && juego->mozo.cantidad_bandeja > 0){
          juego->mozo.cantidad_bandeja = 0;
        }
        else if(juego->obstaculos[i].tipo == CUCARACHAS){
          aplastar_cucaracha(juego);
        }
      }
    }
    for(int i = 0; i < juego->cantidad_herramientas; i++){
      if(juego->herramientas[i].posicion.fil == juego->mozo.posicion.fil && juego->herramientas[i].posicion.col == juego->mozo.posicion.col){
        if(juego->herramientas[i].tipo == MONEDAS){
          recolectar_moneda(juego);
        }
      }
    }
  }
}

/*Pre: Los patines se activaron para pedir una direccion.
Post: Se elige una direccion para el movimiento y Linguini se mueve en esa direccion hasta que choque y mientras tanto interactua con los elementos a disposicion (dependiendo sus condiciones de interaccion).
*/
void movimiento_linguini_con_patines(juego_t *juego, char direccion_patines){
  int direccion_fila = 0;
  int direccion_columna = 0;
  if(direccion_patines == ARRIBA){
    direccion_fila = -1;
  }
  else if(direccion_patines == ABAJO){
    direccion_fila = 1;
  }
  else if(direccion_patines == IZQUIERDA){
    direccion_columna = -1;
  }
  else if(direccion_patines == DERECHA){
    direccion_columna = 1;
  }

  while(!linguini_patines_choca(juego, juego->mozo.posicion.fil + direccion_fila, juego->mozo.posicion.col + direccion_columna)){
    juego->mozo.posicion.fil += direccion_fila;
    juego->mozo.posicion.col += direccion_columna;
    mozo_patines_interactua_elementos(juego);
  }
}

/*Pre: Linguini tiene que haber recolectado patines.
Post: Si toca la tecla "P" activa los patines para poder usarlos. Luego de usarlos se desactoca los patines_puestos.
*/
void activar_patines_linguini(juego_t *juego, char direccion){
  if(juego->mozo.patines_puestos){
    movimiento_linguini_con_patines(juego, direccion);
    juego->mozo.patines_puestos = false;
  }
}

/*Pre: -
Post: Las acciones de las funciones se realizan despues de verificar las condiciones necesarias. 
*/
void realizar_acciones(juego_t *juego){
  if(juego->mozo.tiene_mopa){
      linguini_interaccion_charco(juego);
  }
  else{
    recolectar_moneda(juego);
    aplastar_cucaracha(juego);
  }
  if(juego->mozo.posicion.fil == juego->cocina.posicion.fil && juego->mozo.posicion.col == juego->cocina.posicion.col){
    linguini_deja_pedido_cocina(juego);
    linguini_recoge_platos(juego);
  }

  for(int i = 0; i < juego->cantidad_mesas; i++) {
    if(linguini_cerca_mesa(juego->mozo.posicion, juego->mesas[i]) && juego->mesas[i].cantidad_comensales > 0){
      linguini_entrega_plato_a_mesa(juego, i);
    }
  } 
}

/*Pre: -
Post: Inicializará el juego , cargando toda la información inicial de Linguini , las mesas , las herramientas y los obstáculos.
*/
void inicializar_juego(juego_t *juego){
  juego->cantidad_herramientas = HERRAMIENTAS_INICIALES;
  juego->cantidad_obstaculos = OBSTACULOS_INICIALES;
  juego->cantidad_mesas = MESAS_INICIALES;
  juego->dinero = DINERO_INICIAL;
  juego->movimientos = MOVIMIENTOS_INICIALES;

  inicializar_mesas(juego);
  inicializar_cocina(juego);
  inicializar_mozo_linguini(juego);
  inicializar_herramientas(juego);
  inicializar_obstaculos(juego);
}

/*Pre: El juego debe estar inicializado previamente con 'inicializar_juego' y la accion debe ser valida.
Post: Realizara la accion recibida por parametro.
*/
void realizar_jugada(juego_t *juego, char accion){
  if(accion == ARRIBA || accion == ABAJO || accion == IZQUIERDA ||accion == DERECHA){
    mover_linguini(juego, accion);
    verificar_interaccion_mopa(juego);
    llegada_de_comensales(juego);
    generar_cucaracha(juego);
    linguini_interaccion_charco(juego);
    realizar_acciones(juego);
    recolectar_patines(juego);
    actualizar_platos_cocina(juego);
  }
  else if(accion == AGARRA_SUELTA_MOPA){
    interaccion_mopa(juego);
    if(juego->mozo.tiene_mopa){
      linguini_interaccion_charco(juego);
    }
  }
  else if(accion == TOMAR_PEDIDO){
    linguini_toma_pedido(juego);
  }
  else if(accion == ACTIVAR_PATINES){
    if(juego->mozo.patines_puestos){
      char direccion_patines = pedir_direccion_mozo_patines(juego);
      activar_patines_linguini(juego, direccion_patines);
    }
  }
}

/*Pre: -
Post: Imprime los datos necesarios para el jugador.
*/
void imprimir_datos(juego_t *juego){
  printf("Bienvenido al juego Ratatouille Rush %s!\n", RATA);
  printf("Dinero acumulado: %d\n", juego->dinero);
  printf("Cantidad de pedidos: %d\n", juego->mozo.cantidad_pedidos);
  printf("Cantidad de bandejas: %d\n", juego->mozo.cantidad_bandeja);
  verificar_interaccion_mopa(juego);
  verificar_interaccion_patines(juego);
  if(juego->mozo.tiene_mopa){
    printf(
        "Linguini tiene la mopa. Toca 'O' en un lugar libre para soltarla.\n");
  }
  printf("Movimientos restantes: %d\n", MAX_MOVIMIENTOS_PARTIDA - juego->movimientos);
}

/*Pre: El juego debe estar inicializado previamente con `inicializar_juego `.
Post: Imprime el juego por pantalla.
*/
void mostrar_juego(juego_t juego){
  system("clear");
  char matriz_terreno[MAX_FILAS][MAX_COLUMNAS];
  inicializar_terreno(matriz_terreno);
  imprimir_mesas(juego, matriz_terreno);
  imprimir_herramientas(juego, matriz_terreno);
  imprimir_obstaculos(juego, matriz_terreno);
  matriz_terreno[juego.cocina.posicion.fil][juego.cocina.posicion.col] = COCINA;
  matriz_terreno[juego.mozo.posicion.fil][juego.mozo.posicion.col] = LINGUINI;
  imprimir_terreno(matriz_terreno);
  imprimir_datos(&juego);
}

/*Pre: El juego deberá estar inicializado previamente con `inicializar_juego `
 Post: Devuelve:
 --> 1 si es ganado
 --> -1 si es perdido
 --> 0 si se sigue jugando
 El juego se dará por ganado cuando se termina el día y se consiguieron las monedas necesarias. Se dará por perdido si se termina el día y no se llegó al monto.
 */
int estado_juego(juego_t juego){
  if(juego.movimientos >= MAX_MOVIMIENTOS_PARTIDA){
    if(juego.dinero >= DINERO_PARA_GANAR){
      printf("¡Ganaste! Dinero mínimo recolectado. Dinero acumulado: $%d\n", juego.dinero);
      return GANADO;
    }
    else {
      printf("¡Perdiste! Se acabó el día y no recolectaste lo suficiente. Dinero acumulado: $%d\n", juego.dinero);
      return PERDIDO;
    }
  }
  else{
    return SIGUE_JUGANDO;
  }
}

/*Pre: Los campos `platos_preparacion` y `platos_listos` del campo `cocina` del juego deben estar inicializados.
Post: Libera la memoria dinámica reservada para el juego.
*/
void destruir_juego(juego_t *juego) {
    // Liberar memoria de los platos en preparación
    if (juego->cocina.platos_preparacion != NULL) {
        free(juego->cocina.platos_preparacion);
    }

    // Liberar memoria de los platos listos
    if (juego->cocina.platos_listos != NULL) {
        free(juego->cocina.platos_listos);
    }

    // Aquí puedes liberar otros recursos dinámicos si es necesario
    // Como los platos de la bandeja del mozo, etc.
}
