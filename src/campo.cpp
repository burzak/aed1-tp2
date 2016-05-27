#include "campo.h"

Campo::Campo()
{
}

Campo::Campo(const Posicion &posG, const Posicion &posC)
{
	// Revisarlo para que se cumpla el invariante posicionesAlcanzablesEn100
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
	os << "Campo: " << _dimension.ancho << "x";
	os << _dimension.largo << " - Casa: (" << _posC.x << ",";
	os << _posC.y << ") - Granero: (" << _posG.x << "," << _posG.y;
	os << ")" << std::endl;
}

void Campo::guardar(std::ostream & os) const
{
}

void Campo::cargar(std::istream & is)
{
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

std::ostream & operator<<(std::ostream & os, const Parcela & p)
{
	const char *parcelas[] = {"Cultivo", "Granero", "Casa"};
	return os << parcelas[p];
}

std::ostream & operator<<(std::ostream & os, const Producto & p)
{
	const char *productos[] = {"Fertilizante", "Plaguicida", "PlaguicidaBajoConsumo", "Herbicida", "HerbicidaLargoAlcance"};
	return os << productos[p];
}

std::ostream & operator<<(std::ostream & os, const EstadoCultivo & e)
{
	const char *estados[] = {"RecienSembrado", "EnCrecimiento", "ListoParaCosechar", "ConMaleza", "ConPlaga", "NoSensado"};
	return os << estados[e];
}
