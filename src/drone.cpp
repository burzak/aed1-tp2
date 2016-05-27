#include "drone.h"

Drone::Drone()
{
}

Drone::Drone(ID i, const std::vector<Producto>& ps)
{
	_id = i;
	setBateria(100);
	_enVuelo = false;
	_productos = ps;

	// se inicializa posicionActual y trayectoria?
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
	return _posicionActual;
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

void Drone::moverA(const Posicion pos)
{
}

void Drone::setBateria(const Carga c)
{
	_bateria = c;
}

void Drone::borrarVueloRealizado()
{
	_enVuelo = false;
	_trayectoria = std::vector<Posicion>();
}

void Drone::cambiarPosicionActual(const Posicion p)
{
	_posicionActual = p;
}

void Drone::sacarProducto(const Producto p)
{
	_productos.erase(_productos.at(p));
}

bool Drone::operator==(const Drone & otroDrone) const
{
	return false;
}

std::ostream & operator<<(std::ostream & os, const Drone & d)
{
	return os;
}
