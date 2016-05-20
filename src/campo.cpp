#include "campo.h"

Campo::Campo()
{
}

Campo::Campo(const Posicion &posG, const Posicion &posC)
{
	// Verificar que no sean iguales posC y posG
	
	//

	_dimension.ancho = std::max(posG.x + 1, posC.x + 1);
	_dimension.largo = std::max(posG.y + 1, posC.y + 1);
	
	_grilla = Grilla<Parcela>(_dimension);
	_grilla.parcelas[posG.x][posG.y] = Granero;
	_grilla.parcelas[posC.x][posC.y] = Casa;

	//Guardamos posC y posG:
	_posC = posC;
	_posG = posG;
	//-----//

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
	os << " -- Campo: " << "[Dimensiones: (" << _dimension.ancho << ",";
	os << _dimension.largo << ")], [Posicion Casa: (" << _posC.x << ",";
	os << _posC.y << ")], [Posicion Granero: (" << _posG.x << "," << _posG.y;
	os << ")]" << std::endl;
}

void Campo::guardar(std::ostream & os) const
{
}

void Campo::cargar(std::istream & is)
{
}

bool Campo::operator==(const Campo & otroCampo) const
{
	int x = 0;
	bool res = true;
	
	while (x < _dimension.ancho){
		int y = 0;

		while (y < _dimension.largo){
			res = res && (_grilla.parcelas[x][y] == otroCampo._grilla.parcelas[x][y]);
			y++;
		}

		x++;
	}
	return res;
}

std::ostream & operator<<(std::ostream & os, const Campo & c)
{
	return os << "Campo " << c.dimensiones().ancho;
}

std::ostream & operator<<(std::ostream & os, const Parcela & p)
{
	return os;
}

std::ostream & operator<<(std::ostream & os, const Producto & p)
{
	return os;
}

std::ostream & operator<<(std::ostream & os, const EstadoCultivo & e)
{
	return os;
}
