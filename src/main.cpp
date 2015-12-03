#include "Hundir.h"
#include "Tablero.h"
#include "Barco.h"
#include <vector>

#include <unistd.h>

int main() {
  Hundir* app;
  app = new Hundir();
  app->start();
  
  delete(app);
  return 0;
}
