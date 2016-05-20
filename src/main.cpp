#include <iostream>
#include "campo.h"

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
    return 0;
}
