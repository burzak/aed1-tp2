#include "aux.h"

//Implementen aqui sus funciones auxiliares globales definidas en aux.h...
using namespace std;


Secuencia<std::string> splitBy(const std::string cadena, const std::string delimiter) {
  Secuencia<std::string> partes;
  int inicio = 0;
  int indice = 0;
  int cantidadLetras = 1;
  while (indice < cadena.length()) {
    if (cadena.compare(indice, delimiter.length(), delimiter) == 0) {
      std::string aux = cadena.substr(inicio, cantidadLetras);
      aux = sacarDelimitadorInicioFinal(aux, delimiter);
      if (aux.length() > 0) {
        partes.push_back(aux);
      }
      inicio = indice + delimiter.length();
      cantidadLetras = 0;
    }
    cantidadLetras++;
    indice++;
  }
  partes.push_back(cadena.substr(inicio + delimiter.length() - 1, cadena.length() - inicio));
  return partes;
}

std::string sacarDelimitadorInicioFinal(const std::string cadena, const std::string delimiter) {
  if (cadena.length() < delimiter.length()) {
    return cadena.substr(0, cadena.length());
  }
  int inicio = 0;
  int cantidad = cadena.length();
  if (cadena.substr(cadena.length() - delimiter.length(), delimiter.length()).compare(delimiter) == 0) {
    cantidad = cantidad - delimiter.length();
  }
  if (cadena.substr(0, delimiter.length()).compare(delimiter) == 0) {
    inicio = inicio + delimiter.length();
    cantidad = cantidad - delimiter.length();
  }
  return cadena.substr(inicio, cantidad);
}


Secuencia<Posicion> damePosiciones(const std::string posicionesStr) {
  Secuencia<std::string> coordenadas;
  Secuencia<Posicion> posiciones;
  coordenadas = splitBy(posicionesStr, ",");
  unsigned int n = 0;
  while (n < coordenadas.size()) {
    Posicion p;
    p.x = atoi(
      sacarDelimitadorInicioFinal(coordenadas[n], "[").c_str()
    );
    p.y = atoi(
      sacarDelimitadorInicioFinal(coordenadas[n+1], "]").c_str()
    );
    posiciones.push_back(p);
    p.x = 0;
    p.y = 0;
    n = n + 2;
  }
  return posiciones;
}

Secuencia<Producto> dameProductos(const std::string productosStr) {
  const char *listaProductos[] = {"Fertilizante", "Plaguicida", "PlaguicidaBajoConsumo", "Herbicida", "HerbicidaLargoAlcance"};
  Secuencia<Producto> productos;
	Secuencia<string> productosStrings = splitBy(productosStr, ",");
  unsigned int n = 0;
  while (n < productosStrings.size()) {
    unsigned int i = 0;
    while (i < 5) {
      if (productosStrings[n].compare(listaProductos[i]) == 0) {
        productos.push_back((Producto) i);
      }
      i++;
    }
    n++;
  }
  return productos;
}
