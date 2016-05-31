#include "tipos.h"

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

const bool operator==(const Posicion &p1, const Posicion &p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

const bool operator==(const InfoVueloCruzado &a, const InfoVueloCruzado &b) {
    return a.posicion == b.posicion && a.cantidadCruces == b.cantidadCruces;
}
