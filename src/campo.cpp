#include "campo.h"
#include "aux.h"

Campo::Campo()
{
}

Campo::Campo(const Posicion &posG, const Posicion &posC)
{
	// Revisarlo para que se cumpla el invariante posicionesAlcanzablesEn100
	_dimension.ancho = std::max(posG.x + 1, posC.x + 1);
	_dimension.largo = std::max(posG.y + 1, posC.y + 1);

	_grilla = crearGrilla(_dimension);
	_grilla.parcelas[posG.x][posG.y] = Granero;
	_grilla.parcelas[posC.x][posC.y] = Casa;

	//Guardamos posC y posG:
	_posC = posC;
	_posG = posG;
	//-----//

}

Campo::Campo(const Posicion &posG, const Posicion &posC, Dimension dimension) {
    _dimension = dimension;
    _grilla = Grilla<Parcela>(_dimension);
    _grilla.parcelas[posG.x][posG.y] = Granero;
    _grilla.parcelas[posC.x][posC.y] = Casa;
}

Dimension Campo::dimensiones() const
{
	return _dimension;
}

Parcela Campo::contenido(const Posicion & p) const
{
	return _grilla.parcelas[p.x][p.y];
}

void Campo::mostrar(std::ostream & os) const
{
	os << "Campo: " << _dimension.ancho << "x";
	os << _dimension.largo << " - Casa: (" << _posC.x << ",";
	os << _posC.y << ") - Granero: (" << _posG.x << "," << _posG.y;
	os << ")" << std::endl;
}

void Campo::guardar(std::ostream & os) const
{
  Dimension dim = dimensiones();
  os << "{ C " << dim << " [";
  int x = 0;
  while (x < dim.ancho) {
    int y = 0;
    os << "[";
    while (y < dim.largo) {
      Posicion p;
      p.x = x;
      p.y = y;
      os << contenido(p);
      y++;
      if (y < dim.largo) {
        os << ",";
      }
    }
    os << "]";
    x++;
    if (x < dim.ancho) {
      os << ",";
    }
  }
  os << "]}";
}

void Campo::cargar(std::istream & is)
{
  std::string raw;
  getline(is, raw, '}');
  Secuencia<std::string> datos = splitBy(raw.substr(1, raw.length()-1), " ");

  // reutilizo la funcion damePosicion para cargar la Dimension, es el mismo formato solo cambia el tipo
  Posicion dim = damePosiciones(datos[1])[0];
  _dimension.ancho = dim.x;
  _dimension.largo = dim.y;

  _grilla = crearGrilla(_dimension);

  Secuencia<std::string> lista = cargarLista(datos[2], "[", "]");
  unsigned int n=0;
  while (n < lista.size()) {
    Secuencia<std::string> productos = cargarLista(lista[n], "[", "]");
    unsigned int j = 0;
    while (j < productos.size()) {
      if (productos[j].compare("Casa") == 0) {
				Posicion posC;
				posC.x = n;
				posC.y = j;
				_posC = posC;
        _grilla.parcelas[n][j] = Casa;
      }
      if (productos[j].compare("Granero") == 0) {
				Posicion posG;
				posG.x = n;
				posG.y = j;
				_posG = posG;
        _grilla.parcelas[n][j] = Granero;
      }
      j++;
    }
    n++;
  }
}

bool Campo::operator==(const Campo & otroCampo) const
{
	bool res = true;

	res = dimensiones().ancho == otroCampo.dimensiones().ancho;
	res = res && dimensiones().largo == otroCampo.dimensiones().largo;

	int x = 0;
	while (x < _dimension.ancho) {

		int y = 0;
		while (y < _dimension.largo) {
			res = res && (_grilla.parcelas[x][y] == otroCampo._grilla.parcelas[x][y]);
			y++;
		}

		x++;
	}
	return res;
}

std::ostream & operator<<(std::ostream & os, const Campo & c)
{
	c.mostrar(os);
	return os;
}
