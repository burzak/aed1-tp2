#ifndef AUX_H
#define AUX_H
#include "tipos.h"

//Declaren aqui sus funciones auxiliares globales...
Secuencia<std::string> splitBy(const std::string cadena, const std::string delimiter);
std::string sacarDelimitadorInicioFinal(const std::string cadena, const std::string delimiter);
Secuencia<Posicion> damePosiciones(const std::string posicionesStr);
std::vector<Producto> dameProductos(const std::string productosStr);

#endif //AUX_H
