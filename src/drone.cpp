#include "drone.h"

Drone::Drone()
{
}

Drone::Drone(ID i, const std::vector<Producto>& ps)
{
	// v Esto lo hizo Dante, probablemente este mal
	_id = i;
	_bateria = 100;
	_enVuelo = false;
	_productos = ps;

	//La posicion actual se guarda aca?
	//No deberia guardarse en trayectoria.

	//En la especificacion no aclara nada sobre la trayectoria pero deberia
	//tener que ser vacia.
	_trayectoria = std::vector<Posicion>();
	
	// ^ Esto lo hizo Dante, probablemente este mal
}

ID Drone::id() const
{
	return _id;
}

Carga Drone::bateria() const
{
	return _bateria;
}

bool Drone::enVuelo() const
{
	return _enVuelo;
}

const Secuencia<Posicion>& Drone::vueloRealizado() const
{	
	return _trayectoria;
}

Posicion Drone::posicionActual() const
{
	return _trayectoria[_trayectoria.size() - 1];
}

const Secuencia<Producto>& Drone::productosDisponibles() const
{
	return _productos;
}

/*bool Drone::vueloEscalerado() const
{
	bool res = _enVuelo;

	//Si la cantidad de movimientos es menor a 2, siempre es escalerado
	if (2 < _trayectoria.size()) {
		int distanciaX = (_trayectoria[2].x - _trayectoria[0].x);
		int distanciaY = (_trayectoria[2].y - _trayectoria[0].y);

		//Compruebo que no se mueva en linea recta.
		res = res && distanciaX != 0 && distanciaY != 0;

		int i = 0;
		//Evaluo para todos los puntos alternados que tengan la misma pendiente
		// i + 2 para que no se vaya de rango: solo evalua con los que existen
		while (i+2 <= (int) _trayectoria.size()) {
			int coord1 = (_trayectoria[i+2].x - _trayectoria[i].x);
			int coord2 = (_trayectoria[i+2].y - _trayectoria[i].y);
			
			res = res && (distanciaX == coord1 && distanciaY == coord2);
			i++;
		}
	}

	return res;
}*/

bool Drone::vueloEscalerado() const
{
	bool res = _enVuelo;

	int i = 0;
	while (i+2 < (int) _trayectoria.size()) {
		int distanciaX = (_trayectoria[2].x - _trayectoria[0].x);
		int distanciaY = (_trayectoria[2].y - _trayectoria[0].y);

		int coord1 = (_trayectoria[i+2].x - _trayectoria[i].x);
		int coord2 = (_trayectoria[i+2].y - _trayectoria[i].y);

		res = res && distanciaX == coord1 && distanciaY == coord2 && coord1 != 0 && coord2 != 0;
		i++;
	}

	return res;
}

Secuencia<InfoVueloCruzado> Drone::vuelosCruzados(const Secuencia<Drone>& ds)
{
	return Secuencia<InfoVueloCruzado>();
}

void Drone::mostrar(std::ostream & os) const
{
}

void Drone::guardar(std::ostream & os) const
{
}

void Drone::cargar(std::istream & is)
{
}

bool Drone::operator==(const Drone & otroDrone) const
{
	return false;
}

std::ostream & operator<<(std::ostream & os, const Drone & d)
{
	return os;
}
