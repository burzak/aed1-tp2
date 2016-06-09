#include "auxiliares.h"

//Implementen aqui sus funciones auxiliares globales definidas en aux.h...
using namespace std;


void imprimirLista(const Secuencia<std::string> & secuencia) {
  unsigned int n = 0;
  unsigned int size = secuencia.size();
  cout << endl << "Lista:" << endl;
  while (n < size) {
    cout << "-" << secuencia[n] << "-" << endl;
    n++;
  }
}

Secuencia<string> splitBy(const string cadena, const string delimiter) {
  Secuencia<string> partes;
  int inicio = 0;
  unsigned int indice = 0;
  int cantidadLetras = 1;
  while (indice < cadena.length()) {
    if (cadena.compare(indice, delimiter.length(), delimiter) == 0) {
      string aux = cadena.substr(inicio, cantidadLetras);
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

string sacarDelimitadorInicioFinal(const string cadena, const string delimiter) {
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


Secuencia<Posicion> damePosiciones(const string posicionesStr) {
  Secuencia<string> coordenadas;
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

Secuencia<Producto> dameProductos(const string productosStr) {
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

Secuencia<string> cargarLista(const string listaStr, const string caracterComienzo, const string caracterFin) {
  Secuencia<string> lista;
  unsigned int inicio = 0;
  unsigned int index = 0;
  unsigned int cantidad = 0;
  unsigned int contador = 0;
  while (index < listaStr.length()) {
    string actual = listaStr.substr(index, 1);
    if (actual.compare(",") == 0 && contador == 1) {
      lista.push_back(listaStr.substr(inicio, cantidad));
      cantidad = 0;
      inicio = index + 1;
    } else if (actual.compare(caracterComienzo) == 0 && contador == 0) {
      contador++;
      inicio++;
    } else if (actual.compare(caracterComienzo) == 0) {
      contador++;
      cantidad++;
    } else if (actual.compare(caracterFin) == 0 && contador == 1) {
      contador--;
      lista.push_back(listaStr.substr(inicio, cantidad));
    } else if (actual.compare(caracterFin) == 0) {
      contador--;
      cantidad++;
    } else {
      cantidad++;
    }
    index++;
  }
  return lista;
}

Grilla<Parcela> crearGrilla(Dimension dimension) {
  Grilla<Parcela> grilla = Grilla<Parcela>(dimension);
  int x = 0;
  while (x < dimension.ancho) {
    int y = 0;
    while (y < dimension.largo) {
      grilla.parcelas[x][y] = Cultivo;
      y++;
    }
    x++;
  }
  return grilla;
}

ostream &operator<<(ostream &os, const Dimension &d) {
  return os << "[" << d.ancho << "," << d.largo << "]";
}

EstadoCultivo dameEstadoCultivoDesdeString(const string estadoStr) {
  const char *estados[] = {"RecienSembrado", "EnCrecimiento", "ListoParaCosechar", "ConMaleza", "ConPlaga", "NoSensado"};
	int n = 0;
  EstadoCultivo estado;
  while (n < 6) { // era mas comodo poner el 6 que hacer un count del array!
    if (estadoStr.compare(estados[n]) == 0) {
      estado = (EstadoCultivo) n;
    }
    n++;
  }
  return estado;
}

/*
problema restarPosiciones(pos1, pos2: Posicion) = res: Posicion {
  asegura prm(res) == prm(pos2) - prm(pos1) ^ sgd(res) == sgd(pos2) - sgd(pos1);
}
*/
Posicion restarPosiciones(const Posicion & pos1, const Posicion & pos2) {
  Posicion p;
  p.x = pos2.x - pos1.x;
  p.y = pos2.y - pos2.y;
  return p;
}
