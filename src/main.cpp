#include "Hundir.h"
#include "Tablero.h"
#include "Barco.h"
#include <vector>

#include <unistd.h>

int main() {
  Hundir* app;
  app = new Hundir();
  app->start();
  //app->generarPlayers();
  /*Tablero tab1;
  tab1.crearTablero(8,app->generarBarcos());
  usleep(1000000);//Para que no genere tableros iguales
  Tablero tab2;
  tab2.crearTablero(8,app->generarBarcos());*/

  //Ya tenemos dos tableros aleatorios y distintos, ahora a atacar

  delete(app);
  
  return 0;
}
