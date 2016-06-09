#include <iostream>
#include <fstream>
#include "campo.h"
#include "drone.h"
#include "auxiliares.h"

using namespace std;

int main()
{
  Posicion posG;
  Posicion posC;

  posG.x = 2;
  posG.y = 2;

  posC.x = 3;
  posC.y = 3;

  Campo _c;

  Secuencia<string> lista = cargarLista("[Cultivo,Cultivo,Cultivo,Cultivo]", "[", "]");
  imprimirLista(lista);

  lista = cargarLista("[[Cultivo,Cultivo,Cultivo,Cultivo],[Cultivo,Cultivo,Cultivo,Cultivo],[Cultivo,Cultivo,Granero,Cultivo],[Cultivo,Cultivo,Cultivo,Casa]]", "[", "]");
  imprimirLista(lista);


  lista = cargarLista("[[RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado],[RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado],[RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado],[RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado],[RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado],[RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado],[RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado],[RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado],[RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado],[RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado],[RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado,RecienSembrado]]", "[", "]");
  imprimirLista(lista);

  /*
  ifstream campoStr("campo.txt");
  if (campoStr.is_open()) {
    _c.cargar(campoStr);
    _c.guardar(cout);
  } else {
    _c.mostrar(cout);
    cout << "\n";
    _c.guardar(cout);
  }*/


/*
  Drone d;

  ifstream droneStr("drone.txt");
  if (droneStr.is_open()) {
    d.cargar(droneStr);
    cout << d;
  } else {
    d.mostrar(cout);
    cout << "\n";

    d.guardar(cout);
  }*/

  return 0;
}
