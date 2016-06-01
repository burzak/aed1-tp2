#include "sistema.h"
#include <algorithm>
#include <sstream>

Sistema::Sistema()
{
}

Sistema::Sistema(const Campo & c, const Secuencia<Drone>& ds)
{
	_campo = c;
	Dimension dim = _campo.dimensiones();

	// revisar/preguntar porque no podemos pasarle las dimensiones a Grilla
	_estado = Grilla<EstadoCultivo>(dim);

	int i = 0;
	while (i < dim.ancho) {
		int j = 0;
		while (j < dim.largo) {
			_estado.parcelas[i][j] = NoSensado;
			j++;
		}
		i++;
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
	while(i < _campo.dimensiones().ancho){
			int j = 0;
			while (j < _campo.dimensiones().largo) {
				Posicion pos;
				pos.x = i;
				pos.y = j;
				if (estadoDelCultivo(pos) == RecienSembrado){
					_estado.parcelas[i][j] = EnCrecimiento;
				}
				else if (estadoDelCultivo(pos) == EnCrecimiento){
					_estado.parcelas[i][j] = ListoParaCosechar;
				}
				else{
					_estado.parcelas[i][j] = _estado.parcelas[i][j];
				}
				j++;
			}
		i++;
	}
}

void Sistema::seVinoLaMaleza(const Secuencia<Posicion>& ps)
{
	unsigned int i = 0;
	while(i < ps.size()){
		_estado.parcelas[ps[i].x][ps[i].y] = ConMaleza;
		i++;
	}
}

void Sistema::seExpandePlaga()
{
	int i = 0;
	while (i < _campo.dimensiones().ancho){
		int j = 0;
		while (j < _campo.dimensiones().largo){
			//Es necesario verificar que las parcelas vecinas existan.
			if(enRangoConPlaga(i+1,j)||enRangoConPlaga(i-1,j)||enRangoConPlaga(i,j+1)||enRangoConPlaga(i,j-1)){
				_estado.parcelas[i][j] = ConMaleza;
			}
			j++;
		}
		i++;
	}
}

void Sistema::despegar(const Drone & d)
{
	Posicion pos;

	if (parcelaLibre(d.posicionActual().x - 1, d.posicionActual().y) &&
			enRango(d.posicionActual().x - 1, d.posicionActual().y)){
		pos.x = d.posicionActual().x - 1;
		pos.y = d.posicionActual().y;
	}
	if (parcelaLibre(d.posicionActual().x, d.posicionActual().y + 1) &&
			enRango(d.posicionActual().x, d.posicionActual().y + 1)){
		pos.x = d.posicionActual().x;
		pos.y = d.posicionActual().y + 1;
	}
	if (parcelaLibre(d.posicionActual().x, d.posicionActual().y - 1) &&
			enRango(d.posicionActual().x, d.posicionActual().y - 1)){
		pos.x = d.posicionActual().x;
		pos.y = d.posicionActual().y - 1;
	}
	if (parcelaLibre(d.posicionActual().x + 1, d.posicionActual().y) &&
			enRango(d.posicionActual().x + 1, d.posicionActual().y)){
		pos.x = d.posicionActual().x + 1;
		pos.y = d.posicionActual().y;
	}

	unsigned int i = 0;
	while (i < _enjambre.size()){
		if (_enjambre[i].id() == d.id()){
			_enjambre[i].moverA(pos);
		}
		i++;
	}
}

bool Sistema::listoParaCosechar() const
{
	int i = 0;
	int parcelasListas = 0;
	//int cantidadParcelas = 0;

	//En vez de contar cantidadParcelas podemos hacer ancho * largo
	while (i < campo().dimensiones().ancho){
		int j = 0;
		while (j < campo().dimensiones().largo){
			Posicion pos;
			pos.x = i;
			pos.y = j;
			//if (_estado.parcelas[i][j] == ListoParaCosechar){
			if (estadoDelCultivo(pos) == ListoParaCosechar){
				parcelasListas++;
			}
			//cantidadParcelas++;
			j++;
		}
		i++;
	}
	//return (parcelasListas/cantidadParcelas) > 0.9;
	return ((parcelasListas/(campo().dimensiones().ancho * campo().dimensiones().largo)) >= 0.9);
}

void Sistema::aterrizarYCargarBaterias(Carga b)
{
}

void Sistema::fertilizarPorFilas()
{/*
	int i = 0;
	while (i < campo().dimensiones().largo){
		int pasos = 0;
		pasos = pasosIzquierdaPosibles(y);
		i++;
	}*/
}

void Sistema::volarYSensar(const Drone & d)
{
	unsigned int i = 0;
	int indiceDrone;

	//Hay que buscar un dron equivalente al que nos dieron en el enjambre del sistema.
	//Por invariante y requiere deberia siempre encontrarlo y ser unico.
	while (i < enjambreDrones().size()){
		if (enjambreDrones()[i].id() == d.id()){
			//Como quiero modificarlo tengo que usar _enjambre, no enjambreDeDrones() no?
			//Asigno por referencia para poder modificar el drone en cuestion
			indiceDrone = i;
		}
		i++;
	}

	Drone& droneUsado = _enjambre[indiceDrone];

	//El granero cuenta como parcelaDisponible? Falta la aux en la especificacion

	Posicion targetPos;
	//Estos muchos ifs no me gustan demasiado
	if (droneUsado.bateria() >0 && enRangoCultivableLibre(droneUsado.posicionActual().x + 1, droneUsado.posicionActual().y)){
		targetPos.x = droneUsado.posicionActual().x + 1;
		targetPos.y = droneUsado.posicionActual().y;
		droneUsado.moverA(targetPos);
		droneUsado.setBateria(droneUsado.bateria() - 1);
	}
	else if (droneUsado.bateria() >0 && enRangoCultivableLibre(droneUsado.posicionActual().x - 1, droneUsado.posicionActual().y)){
		targetPos.x = droneUsado.posicionActual().x - 1;
		targetPos.y = droneUsado.posicionActual().y;
		droneUsado.moverA(targetPos);
		droneUsado.setBateria(droneUsado.bateria() - 1);
	}
	else if (droneUsado.bateria() >0 && enRangoCultivableLibre(droneUsado.posicionActual().x, droneUsado.posicionActual().y + 1)){
		targetPos.x = droneUsado.posicionActual().x;
		targetPos.y = droneUsado.posicionActual().y + 1;
		droneUsado.moverA(targetPos);
		droneUsado.setBateria(droneUsado.bateria() - 1);
	}
	else if (droneUsado.bateria() >0 && enRangoCultivableLibre(droneUsado.posicionActual().x, droneUsado.posicionActual().y - 1)){
		targetPos.x = droneUsado.posicionActual().x;
		targetPos.y = droneUsado.posicionActual().y - 1;
		droneUsado.moverA(targetPos);
		droneUsado.setBateria(droneUsado.bateria() - 1);
	}

	//Si la parcela esta noSensada se le puede poner cualquier verdura (eh, entienden? Cualquier verdura para cultivar!)

	//Esta variable es por cuestiones meramente esteticas
	EstadoCultivo estado = estadoDelCultivo(targetPos);

	if (estado == NoSensado){
		_estado.parcelas[targetPos.x][targetPos.y] = RecienSembrado;
	}
	else if ((estado == RecienSembrado || estado == EnCrecimiento) &&
			tieneUnProducto(droneUsado.productosDisponibles(), Fertilizante)) {

		_estado.parcelas[targetPos.x][targetPos.y] = ListoParaCosechar;
		droneUsado.sacarProducto(Fertilizante);
		//Verificar si fertilizar gasta bateria.
		//Verificar si queda listo para cosechar cuando esta EnCrecimiento y RecienSembrado
	}
	else if (estado == ConPlaga){
		if (droneUsado.bateria() >=10 && tieneUnProducto(droneUsado.productosDisponibles(), Plaguicida)){
			_estado.parcelas[targetPos.x][targetPos.y] = RecienSembrado;
			droneUsado.sacarProducto(Plaguicida);
			droneUsado.setBateria(droneUsado.bateria() - 10);
		}
		else if (droneUsado.bateria() >=5 && tieneUnProducto(droneUsado.productosDisponibles(), PlaguicidaBajoConsumo)){
			_estado.parcelas[targetPos.x][targetPos.y] = RecienSembrado;
			droneUsado.sacarProducto(PlaguicidaBajoConsumo);
			droneUsado.setBateria(droneUsado.bateria() - 5);
		}
	}
	else if (estado == ConMaleza){
		if (droneUsado.bateria() >=5 && tieneUnProducto(droneUsado.productosDisponibles(), Herbicida)){
			_estado.parcelas[targetPos.x][targetPos.y] = RecienSembrado;
			droneUsado.sacarProducto(Herbicida);
			droneUsado.setBateria(droneUsado.bateria() - 5);
		}
		else if (droneUsado.bateria() >=5 && tieneUnProducto(droneUsado.productosDisponibles(), HerbicidaLargoAlcance)){
			_estado.parcelas[targetPos.x][targetPos.y] = RecienSembrado;
			droneUsado.sacarProducto(HerbicidaLargoAlcance);
			droneUsado.setBateria(droneUsado.bateria() - 5);
		}
	}


	/***RECORDAR***/
	//Cambiar bateria cuando se mueve (drone.moverA() no cambia la bateria)
	//Cambiar la bateria cuando se aplica un producto o similar




}

void Sistema::mostrar(std::ostream & os) const
{
}

void Sistema::guardar(std::ostream & os) const
{
}

void Sistema::cargar(std::istream & is)
{
  std::string raw;

  // process positions
  std::stringstream nuevo;
  nuevo.str(raw.c_str());
}

bool Sistema::operator==(const Sistema & otroSistema) const
{
	return false;
}

std::ostream & operator<<(std::ostream & os, const Sistema & s)
{
	s.mostrar(os);
	return os;
}



/********************** AUX *****************************/
bool Sistema::enRangoConPlaga(int x, int y) const{
	bool res = true;
	res = res && (x >= 0) && (x < _campo.dimensiones().ancho);
	res = res && (y >= 0) && (y < _campo.dimensiones().largo);
	res = res && _estado.parcelas[x][y] == ConPlaga;
	return res;
}

bool Sistema::enRango(int x, int y) const{
	bool res;
	bool xValida = (x >= 0 && x < campo().dimensiones().ancho);
	bool yValida = (y >= 0 && y < campo().dimensiones().largo);
	res = xValida && yValida;

	return res;
}

bool Sistema::parcelaLibre(int x, int y) const{
	bool res = true;

	unsigned int i = 0;
	while (i < enjambreDrones().size()){
		bool xDistinto = enjambreDrones()[i].posicionActual().x != x;
		bool yDistinto = enjambreDrones()[i].posicionActual().y != y;
		res = res && (xDistinto && yDistinto);
		i++;
	}

	return res;
}

bool Sistema::enRangoCultivableLibre(int x, int y) const{
	bool res = true;
	Posicion pos;
	pos.x = x;
	pos.y = y;

	res = res && (campo().contenido(pos) == Cultivo);

	unsigned int i = 0;
	while (i < enjambreDrones().size()){
		res = res && (enjambreDrones()[i].posicionActual().x != x && enjambreDrones()[i].posicionActual().y != y);
		i++;
	}
	return res;
}

bool Sistema::tieneUnProducto(const Secuencia<Producto> &ps, const Producto &productoABuscar){
	unsigned int i = 0;
	bool res = false;

	while (i < ps.size()){
		res = res || ps[i] == productoABuscar;
		i++;
	}

	return res;
}

/*int Sistema::pasosIzquierdaPosibles(int y){
	Drone d;
	int i = 0;
	while (i < enjambreDrones().size()){
		if (enjambreDrones()[i].posicionActual().y == y){
			d = enjambreDrones()[i];
		}
		i++;
	}
	int posX = d.posicionActual().x;
	i = posX;
	while (i >= 0){

		i--;
	}
}
*/

//A Galimba no le gusta que usemos  &=  :(
