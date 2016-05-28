#include "sistema.h"
#include <algorithm>

Sistema::Sistema()
{
}

Sistema::Sistema(const Campo & c, const Secuencia<Drone>& ds)
{
	_campo = c;
	Dimension dim = _campo.dimensiones();

	// revisar/preguntar porque no podemos pasarle las dimensiones a Grilla
	_estado = Grilla<EstadoCultivo>();

	int i = 0;
	while (i < dim.ancho) {
		int j = 0;
		while (j < dim.largo) {
			_estado.parcelas[i][j] = NoSensado;
		}
	}

	_enjambre = ds;
}

const Campo & Sistema::campo() const
{
	return _campo;
}

EstadoCultivo Sistema::estadoDelCultivo(const Posicion & p) const
{
	return EstadoCultivo();
}

const Secuencia<Drone>& Sistema::enjambreDrones() const
{
	return _enjambre;
}

void Sistema::crecer()
{
	int i = 0;
	while(i < _estado.ancho){
			int j = 0;
			while (j < _estado.largo) {
				if (_estado[i][j] == RecienSembrado){
					_estado[i][j] == EnCrecimiento;
				}
				if (_estado[i][j] == EnCrecimiento){
					_estado[i][j] == ListoParaCosechar;
				}
				j++;
			}
		i++;
	}
}

void Sistema::seVinoLaMaleza(const Secuencia<Posicion>& ps)
{
}

void Sistema::seExpandePlaga()
{
}

void Sistema::despegar(const Drone & d)
{
}

bool Sistema::listoParaCosechar() const
{
	return false;
}

void Sistema::aterrizarYCargarBaterias(Carga b)
{
}

void Sistema::fertilizarPorFilas()
{
}

void Sistema::volarYSensar(const Drone & d)
{
}

void Sistema::mostrar(std::ostream & os) const
{
}

void Sistema::guardar(std::ostream & os) const
{
}

void Sistema::cargar(std::istream & is)
{
}

bool Sistema::operator==(const Sistema & otroSistema) const
{
	return false;
}

std::ostream & operator<<(std::ostream & os, const Sistema & s)
{
	// TODO: insert return statement here
	return os;
}
