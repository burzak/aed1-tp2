#ifndef AUX_H
#define AUX_H
#include "tipos.h"

//Declaren aqui sus funciones auxiliares globales...
Secuencia<std::string> splitBy(const std::string cadena, const std::string delimiter);
std::string sacarDelimitadorInicioFinal(const std::string cadena, const std::string delimiter);
Secuencia<Posicion> damePosiciones(const std::string posicionesStr);
std::vector<Producto> dameProductos(const std::string productosStr);
Secuencia<std::string> cargarLista(const std::string listaStr, const std::string caracterComienzo, const std::string caracterFin);
Grilla<Parcela> crearGrilla(Dimension dimension);
EstadoCultivo dameEstadoCultivoDesdeString(const std::string estadoStr);

Posicion restarPosiciones(const Posicion & pos1, const Posicion & pos2);

void imprimirLista(const Secuencia<std::string> & secuencia);

std::ostream &operator<<(std::ostream &os, const Dimension &d);

inline std::ostream & operator<<(std::ostream & os, const Posicion & p) { return os << "[" << p.x << "," << p.y << "]"; };


#endif //AUX_H
