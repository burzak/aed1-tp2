#include "sistema.h"
#include "drone.h"
#include "aux.h"
#include <algorithm>
#include <sstream>
#include <ostream>

using namespace std;

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
			_estado.parcelas[i][j] = RecienSembrado;
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
	return _estado.parcelas[p.x][p.y];
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
			if (campo().contenido(pos) == Cultivo){
				if (estadoDelCultivo(pos) == RecienSembrado){
					_estado.parcelas[i][j] = EnCrecimiento;
				}
				else if (estadoDelCultivo(pos) == EnCrecimiento){
					_estado.parcelas[i][j] = ListoParaCosechar;
				}
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
	//Probablemente haya que arreglar porque estoy expandiendo la plaga al mismo tiempo que chequeo
	int i = 0;
	Grilla<EstadoCultivo> estado0 = _estado;
	while (i < campo().dimensiones().ancho){
		int j = 0;
		while (j < campo().dimensiones().largo){
			//Es necesario verificar que las parcelas vecinas existan.
			if(enRangoConPlaga(i+1,j, estado0)||enRangoConPlaga(i-1,j, estado0)||
				enRangoConPlaga(i,j+1, estado0)||enRangoConPlaga(i,j-1, estado0)){
				_estado.parcelas[i][j] = ConPlaga;
			}
			j++;
		}
		i++;
	}
}

void Sistema::despegar(const Drone & d)
{
	Posicion pos;
	bool seMueve = false;

	if (enRangoCultivableLibre(d.posicionActual().x - 1, d.posicionActual().y)){
			//enRango(d.posicionActual().x - 1, d.posicionActual().y)){
		pos.x = d.posicionActual().x - 1;
		pos.y = d.posicionActual().y;
		seMueve = true;
	}
	else if (enRangoCultivableLibre(d.posicionActual().x, d.posicionActual().y + 1)){
		pos.x = d.posicionActual().x;
		pos.y = d.posicionActual().y + 1;
		seMueve = true;
	}
	else if (enRangoCultivableLibre(d.posicionActual().x, d.posicionActual().y - 1)){
		pos.x = d.posicionActual().x;
		pos.y = d.posicionActual().y - 1;
		seMueve = true;
	}
	else if (enRangoCultivableLibre(d.posicionActual().x + 1, d.posicionActual().y)){
		pos.x = d.posicionActual().x + 1;
		pos.y = d.posicionActual().y;
		seMueve = true;
	}
	unsigned int i = 0;
	while (i < _enjambre.size()){
		if (seMueve && (_enjambre[i].id() == d.id())){
			_enjambre[i].moverA(pos);
		}
		i++;
	}
}

bool Sistema::listoParaCosechar() const
{
	int i = 0;
	float parcelasListas = 0;
	float cantidadParcelas = 0;

	//En vez de contar cantidadParcelas podemos hacer ancho * largo
	while (i < campo().dimensiones().ancho){
		int j = 0;
		while (j < campo().dimensiones().largo){
			Posicion pos;
			pos.x = i;
			pos.y = j;
			if(campo().contenido(pos) == Cultivo){
				if (estadoDelCultivo(pos) == ListoParaCosechar){
				//if (estadoDelCultivo(pos) == ListoParaCosechar){
					parcelasListas++;
				}
				cantidadParcelas++;
			}
			j++;
		}
		i++;
	}
	//Magia matematica para no comparar floats.
	int res = (parcelasListas/cantidadParcelas)*100;

	return res >= 90;

}

void Sistema::aterrizarYCargarBaterias(Carga b)
{
	int i = 0;
	while(i < enjambreDrones().size()){
		if(enjambreDrones()[i].bateria() < b){
			_enjambre[i].setBateria(100);
			_enjambre[i].cambiarPosicionActual(posG());
			_enjambre[i].borrarVueloRealizado();
		}
		i++;
	}
}

void Sistema::fertilizarPorFilas()
{
	unsigned int i = 0;
	while (i < campo().dimensiones().largo){
		unsigned int pasos = 0;
		pasos = pasosIzquierdaPosibles(i);


		//Busco el drone para modificarlo
		int indiceDrone;
		unsigned int j = 0;
		while (j < _enjambre.size()){
			if(_enjambre[j].posicionActual().y == i){
				indiceDrone = j;
			}
			j++;
		}

		int posXIni = _enjambre[indiceDrone].posicionActual().x;

		//Fertilizo las parcelas por las que paso y veo cuanto fertilizante hay que sacar.
		int fertUsado = 0;
		j = 0;
		while(j < pasos){
			Posicion pos;
			pos.y = i;
			pos.x = posXIni - j;
			if(campo().contenido(pos) == Cultivo){
				if(estadoDelCultivo(pos) == EnCrecimiento || estadoDelCultivo(pos) == RecienSembrado){
					fertUsado++;
					_estado.parcelas[posXIni - j][i] = ListoParaCosechar;
				}
			}
			j++;
		}


		j = 0;
		while(j <= fertUsado){
			_enjambre[indiceDrone].sacarProducto(Fertilizante);
			j++;
		}

		_enjambre[indiceDrone].setBateria(_enjambre[indiceDrone].bateria() - pasos);

		j = 0;
		while(j <= posXIni){
			Posicion pos;
			pos.x = posXIni - j;
			pos.y = i;
			_enjambre[indiceDrone].moverA(pos);
			j++;
		}

		i++;
	}
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

	Drone& drone = _enjambre[indiceDrone];
	int posX = drone.posicionActual().x;
	int posY = drone.posicionActual().y;
	bool seMovio = false;

	//El granero cuenta como parcelaDisponible? Falta la aux en la especificacion

	Posicion targetPos;
	//Estos muchos ifs no me gustan demasiado
	if (drone.bateria() >0 && enRangoCultivableLibre(posX + 1, posY)){
		targetPos.x = posX + 1;
		targetPos.y = posY;
		drone.moverA(targetPos);
		drone.setBateria(drone.bateria() - 1);
		seMovio = true;
	}
	else if (drone.bateria() >0 && enRangoCultivableLibre(posX - 1, posY)){
		targetPos.x = posX - 1;
		targetPos.y = posY;
		drone.moverA(targetPos);
		drone.setBateria(drone.bateria() - 1);
		seMovio = true;
	}
	else if (drone.bateria() >0 && enRangoCultivableLibre(posX, posY + 1)){
		targetPos.x = posX;
		targetPos.y = posY + 1;
		drone.moverA(targetPos);
		drone.setBateria(drone.bateria() - 1);
		seMovio = true;
	}
	else if (drone.bateria() >0 && enRangoCultivableLibre(posX, posY - 1)){
		targetPos.x = posX;
		targetPos.y = posY - 1;
		drone.moverA(targetPos);
		drone.setBateria(d.bateria() - 1);
		seMovio = true;
	}

	//Si la parcela esta noSensada se le puede poner cualquier verdura (eh, entienden? Cualquier verdura para cultivar!)

	if(seMovio == true){
		modificarCultivoYDrone(targetPos, drone);
	}

}


	/***RECORDAR***/
	//Cambiar bateria cuando se mueve (drone.moverA() no cambia la bateria)
	//Cambiar la bateria cuando se aplica un producto o similar



void Sistema::mostrar(std::ostream & os) const
{
	os << "Sistema: Drones: " << enjambreDrones().size() << " " << campo();
}

void Sistema::guardar(std::ostream & os) const
{
	os << "{ S ";
	campo().guardar(os);
	os << " [";
	unsigned int n = 0;
	Secuencia<Drone> enjambre = enjambreDrones();
	while (n < enjambre.size()) {
		enjambre[n].guardar(os);
		n++;
		if (n < enjambre.size()) {
			os << ",";
		}
	}
	os << "] [";
	int x = 0;
	Dimension dim = campo().dimensiones();
	while (x < dim.ancho) {
		int y = 0;
		os << "[";
		while (y < dim.largo) {
			Posicion p;
			p.x = x;
			p.y = y;
			os << estadoDelCultivo(p);
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

void Sistema::cargar(std::istream & is)
{
	std::string non;
	//adelanto hasta el campo
	getline(is, non, '{');
	getline(is, non, '{');
	is.putback('{');
	_campo.cargar(is);

	// cargo todos los drones
	char c;
	while (c != ']') {
		is.get(c);
		if (c == '{') {
			is.putback('{');
			Drone d;
			d.cargar(is);
			_enjambre.push_back(d);
		}
	}

	// despues de los drones obtengo todo hasta el final que son los estados de cultivos
	getline(is, non);
	Secuencia<std::string> estadosCultivosFilas;
	// con el substr saco el " " inicial y el } final!
	estadosCultivosFilas = cargarLista(non.substr(1, non.length()-2), "[", "]");

	Secuencia<std::string> todosEstadosCultivos;

	int n = 0;
	while (n < estadosCultivosFilas.size()) {
		Secuencia<string> tmp = splitBy(estadosCultivosFilas[n].substr(1, estadosCultivosFilas[n].length() - 2), ",");
		todosEstadosCultivos.insert(todosEstadosCultivos.end(), tmp.begin(), tmp.end());
		n++;
	}
	Dimension dim;
	dim.ancho = estadosCultivosFilas.size();
	dim.largo = todosEstadosCultivos.size() / estadosCultivosFilas.size();
	_estado = Grilla<EstadoCultivo>(dim);

	int x = 0;
	while (x < dim.ancho) {
		int y = 0;
		while (y < dim.largo) {
			_estado.parcelas[x][y] = dameEstadoCultivoDesdeString(todosEstadosCultivos[x*dim.ancho+y]);
			y++;
		}
		x++;
	}
}

bool Sistema::operator==(const Sistema & otroSistema) const
{
	bool res = true;
	res == res && mismosDrones(enjambreDrones(), otroSistema.enjambreDrones());
	res == res && campo() == otroSistema.campo();
	Dimension dim = campo().dimensiones();
	int x = 0;
	while (res && x < dim.ancho) {
		int y = 0;
		while (res && y < dim.largo) {
			Posicion p;
			p.x = x;
			p.y = y;
			res = res && estadoDelCultivo(p) == otroSistema.estadoDelCultivo(p);
			y++;
		}
		x++;
	}
	return res;
}

std::ostream & operator<<(std::ostream & os, const Sistema & s)
{
	s.mostrar(os);
	return os;
}



/********************** AUX *****************************/
bool Sistema::enRangoConPlaga(int x, int y, Grilla<EstadoCultivo> estado0) const{
	bool res = true;
	Posicion pos;
	pos.x = x;
	pos.y = y;

	if(enRango(x,y)){
		if(campo().contenido(pos) == Cultivo){
			res = estado0.parcelas[x][y] == ConPlaga;
		}
		else{
			res = false;
		}
	}
	else{
		res = false;
	}
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
	bool res = enRango(x, y);
	Posicion pos;
	pos.x = x;
	pos.y = y;

	if (enRango(x, y)){
		res = res && (campo().contenido(pos) == Cultivo);

		unsigned int i = 0;
		while (i < enjambreDrones().size()){
			res = res && ((enjambreDrones()[i].posicionActual().x != x) || (enjambreDrones()[i].posicionActual().y != y));
			i++;
		}
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

Posicion Sistema::posG() const{
	Posicion posG;
	int i = 0;
	while(i < campo().dimensiones().ancho){
		int j = 0;
		while(j < campo().dimensiones().largo){
			Posicion posAux;
			posAux.x = i;
			posAux.y = j;
			if(campo().contenido(posAux) == Granero){
				posG.x = posAux.x;
				posG.y = posAux.y;
			}
			j++;
		}
		i++;
	}

	return posG;
}

int Sistema::pasosIzquierdaPosibles(int y){
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
	//Los inicializo en -1 para que en caso que no haya ni G ni C en la fila se pueda usar como limite
	int xGranero = -1;
	int xCasa = -1;
	while (i >= 0){
		Posicion pos;
		pos.x = i;
		pos.y = y;
		if(campo().contenido(pos) == Casa){
			xCasa = i;
		}
		if(campo().contenido(pos) == Granero){
			xGranero = i;
		}
		i--;
	}

	int fertilizante = 0;
	i = 0;
	while(i < d.productosDisponibles().size()){
		if(d.productosDisponibles()[i] == Fertilizante){
			fertilizante++;
		}
		i++;
	}

	i = posX;
	int pasosFert = 0;
	while(i > mayor(xCasa, xGranero)){
		Posicion pos;
		pos.x = i;
		pos.y = y;
		if((estadoDelCultivo(pos) != EnCrecimiento && estadoDelCultivo(pos) != RecienSembrado) &&
			fertilizante > 0){
			pasosFert++;
		}
		if((estadoDelCultivo(pos) == EnCrecimiento || estadoDelCultivo(pos) == RecienSembrado) &&
			fertilizante > 0){
			pasosFert++;
			fertilizante--;
		}
		i--;
	}

	return menor(pasosFert, menor(d.bateria(), menor(posX - xGranero, posX - xCasa)));


}

int Sistema::mayor(int a, int b){
	int res;
	if(a > b){
		res = a;
	}
	else {
		res = b;
	}
	return res;
}

int Sistema::menor(int a, int b){
		int res;
	if(a < b){
		res = a;
	}
	else {
		res = b;
	}
	return res;
}

void Sistema::modificarCultivoYDrone(Posicion pos, Drone &d){
	EstadoCultivo estado = estadoDelCultivo(pos);

	if (estado == NoSensado){
		_estado.parcelas[pos.x][pos.y] = RecienSembrado;
	}
	else if ((estado == RecienSembrado || estado == EnCrecimiento) &&
				tieneUnProducto(d.productosDisponibles(), Fertilizante)) {

		_estado.parcelas[pos.x][pos.y] = ListoParaCosechar;
		d.sacarProducto(Fertilizante);
		//Verificar si fertilizar gasta bateria.
		//Verificar si queda listo para cosechar cuando esta EnCrecimiento y RecienSembrado
	}
	else if (estado == ConPlaga){
		if (d.bateria() >=10 && tieneUnProducto(d.productosDisponibles(), Plaguicida)){
			_estado.parcelas[pos.x][pos.y] = RecienSembrado;
			d.sacarProducto(Plaguicida);
			d.setBateria(d.bateria() - 10);
		}
		else if (d.bateria() >=5 && tieneUnProducto(d.productosDisponibles(), PlaguicidaBajoConsumo)){
			_estado.parcelas[pos.x][pos.y] = RecienSembrado;
			d.sacarProducto(PlaguicidaBajoConsumo);
			d.setBateria(d.bateria() - 5);
		}
	}
	else if (estado == ConMaleza){
		if (d.bateria() >=5 && tieneUnProducto(d.productosDisponibles(), Herbicida)){
			_estado.parcelas[pos.x][pos.y] = RecienSembrado;
			d.sacarProducto(Herbicida);
			d.setBateria(d.bateria() - 5);
		}
		else if (d.bateria() >=5 && tieneUnProducto(d.productosDisponibles(), HerbicidaLargoAlcance)){
			_estado.parcelas[pos.x][pos.y] = RecienSembrado;
			d.sacarProducto(HerbicidaLargoAlcance);
			d.setBateria(d.bateria() - 5);
		}
	}
}


bool Sistema::mismosDrones(const Secuencia<Drone> & ds1, const Secuencia<Drone> & ds2) {
	bool res = ds1.size() == ds2.size();
  unsigned int n = 0;
  while (res && n < ds1.size()) {
		res = res && (cantidadDrones(ds1, ds1[n]) == cantidadDrones(ds2, ds1[n]));
    res = res && (cantidadDrones(ds1, ds2[n]) == cantidadDrones(ds2, ds2[n]));
    n++;
  }
  return res;
}

int Sistema::cantidadDrones(const Secuencia<Drone> & ds, const Drone & d) {
  unsigned int n = 0;
  int cant = 0;
  while (n < ds.size()) {
    if (ds[n] == d) {
      cant++;
    }
    n++;
  }
  return cant;
}


//A Galimba no le gusta que usemos  &=  :(
