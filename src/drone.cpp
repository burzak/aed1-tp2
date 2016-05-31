#include "drone.h"
#include "campo.h"

Drone::Drone()
{
	_id = 1111;
	setBateria(99);
	_enVuelo = true;
	Posicion pos;
	pos.x = 1;
	pos.y = 2;
	_trayectoria.push_back(pos);
	pos.y = 3;
	_trayectoria.push_back(pos);
	_posicionActual = pos;

	_productos.push_back(Fertilizante);
	_productos.push_back(Plaguicida);
	_productos.push_back(PlaguicidaBajoConsumo);
	_productos.push_back(Fertilizante);
}

Drone::Drone(ID i, const std::vector<Producto>& ps)
{
	_id = i;
	setBateria(100);
	_enVuelo = false;
	_productos = ps;
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
	Secuencia<InfoVueloCruzado> vuelosCruzados;
	unsigned int n = 0;
	while (n < ds.size()) {
		unsigned int j = 0;
		while (j < ds[n].vueloRealizado().size()) {
			if (cantidadCruces(ds, ds[n].vueloRealizado()[j], ds[n].vueloRealizado().size()) > 1) {
				InfoVueloCruzado info;
				info.posicion = ds[n].vueloRealizado()[j];
				info.cantidadCruces = cantidadCruces(ds, ds[n].vueloRealizado()[j], ds[n].vueloRealizado().size());
				vuelosCruzados.push_back(info);
			}
			j++;
		}
		n++;
	}
	return Secuencia<InfoVueloCruzado>();
}

void Drone::mostrar(std::ostream & os) const
{
	os << "Drone[" << id() <<"] (";
	if (enVuelo()) {
		os << "volando";
	} else {
		os << "no volando";
	}

	os << " - " << bateria() << "%)";

	os << " Productos: [";
	unsigned int n = 0;
	while (n < productosDisponibles().size()) {
		os << productosDisponibles()[n];
		n++;
		if (n < productosDisponibles().size()) {
			os << ", ";
		}
	}
	os << "]";

	os << " Posicion: " << posicionActual() << " - Trayectoria: [";
	unsigned int i = 0;
	while (i < vueloRealizado().size()) {
		os << vueloRealizado()[n];
		i++;
		if (i < vueloRealizado().size()) {
			os << ", ";
		}
	}
	os << "]\n";
}



void Drone::guardar(std::ostream & os) const
{
	os << "{ D " << id() << " " << bateria() << " [";
	unsigned int n = 0;
	while (n < vueloRealizado().size()) {
		os << vueloRealizado()[n];
		n++;
		if (n < vueloRealizado().size()) {
			os << ",";
		}
	}
	os << "] [";
	unsigned int i = 0;
	while (i < productosDisponibles().size()) {
		os << productosDisponibles()[i];
		i++;
		if (i < productosDisponibles().size()) {
			os << ",";
		}
	}
	os << "] ";
	if (enVuelo()) {
		os << "true ";
	} else {
		os << "false ";
	}
	os << posicionActual() << "}";
}

void Drone::cargar(std::istream & is)
{
  std::string raw;
  getline(is, raw);
  Secuencia<std::string> datos = splitWhiteSpace(raw.substr(1, raw.length()-2));
  unsigned int n = 0;
  while (n < datos.size()) {
    std::cout << n << "-" << datos[n] << std::endl;
    n++;
  }

  _id = atoi(datos[1].c_str());
  setBateria(atoi(datos[2].c_str()));
  if (datos[5].compare("true") == 0) {
    _enVuelo = true;
  } else {
    _enVuelo = false;
  }
}

Secuencia<std::string> Drone::splitWhiteSpace(const std::string cadena) const {
  Secuencia<std::string> partes;
  std::string delimiter = " ";
  int inicio = 0;
  int indice = 0;
  while (indice < cadena.length()) {
    if (cadena.substr(indice, 1) == delimiter && (indice - inicio) > 1) {
      partes.push_back(cadena.substr(inicio+1, indice - inicio - 1));
      inicio = indice;
    }
    indice++;
  }
  partes.push_back(cadena.substr(inicio+1, cadena.length() - inicio));
  return partes;
}

void Drone::moverA(const Posicion pos)
{
	_enVuelo = true;
	_trayectoria.push_back(pos);
	cambiarPosicionActual(pos); // por invariante agregamos esta linea
	// debemos verificar invariante movimientoOK? pos tiene que ser un movimiento valido?
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
	int indiceProducto;
	unsigned n=0;
	while (n < _productos.size()) {
		if (_productos[n] == p) {
			indiceProducto = n;
		}
	}
	_productos.erase(_productos.begin() + indiceProducto);
}

bool Drone::operator==(const Drone & otroDrone) const
{
	bool res = true;
	res = res && id() == otroDrone.id();
	res = res && bateria() == otroDrone.bateria();
	res = res && enVuelo() == otroDrone.enVuelo();
	res = res && vueloRealizado() == otroDrone.vueloRealizado();
	res = res && posicionActual() == otroDrone.posicionActual();
	res = res && mismosProductos(productosDisponibles(), otroDrone.productosDisponibles());
	return res;
}

std::ostream & operator<<(std::ostream & os, const Drone & d)
{
	d.mostrar(os);
	return os;
}

/******************** AUX **************************/
bool Drone::mismosProductos(const Secuencia<Producto> lista1, const Secuencia<Producto> lista2) {
  bool res = lista1.size() == lista2.size();
  unsigned int n = 0;
  while (res && n < lista1.size()) {
		res = res && (cantidad(lista1, lista1[n]) == cantidad(lista2, lista1[n]));
    res = res && (cantidad(lista1, lista2[n]) == cantidad(lista2, lista2[n]));
    n++;
  }

  return res;
}

int Drone::cantidad(const Secuencia<Producto> lista, Producto producto) {
  unsigned int n = 0;
  int cant = 0;
  while (n < lista.size()) {
    if (lista[n] == producto) {
      cant++;
    }
    n++;
  }
  return cant;
}

int Drone::cantidadCruces(const Secuencia<Drone>& ds, Posicion pos, int longitud) {
	int n = 0;
	int total = 0;
	while (n < longitud) {
		int cant = 0;
		unsigned int j = 0;
		while (j < ds.size()) {
			if (ds[j].vueloRealizado()[n] == pos) {
				cant++;
			}
		}
		if (cant > 1) {
			total = total + cant;
		}
		cant = 0;
		n++;
	}
	return total;
}
