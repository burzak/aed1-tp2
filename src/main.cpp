#include <iostream>
#include <fstream>
#include "campo.h"
#include "drone.h"
#include "aux.h"

using namespace std;

int main()
{
	Posicion posG;
	Posicion posC;

	posG.x = 2;
	posG.y = 2;

	posC.x = 3;
	posC.y = 3;

	Campo _c = Campo(posG, posC);
	_c.mostrar(std::cout);


	Drone d;

	ifstream droneStr("drone.txt");
	if (droneStr.is_open()) {
		d.cargar(droneStr);
    cout << d;
	} else {
    d.mostrar(cout);
    cout << "\n";

    d.guardar(cout);
  }

	return 0;
}
