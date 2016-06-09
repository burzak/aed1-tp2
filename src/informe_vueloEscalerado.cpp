/*
problema restarPosiciones(pos1, pos2: Posicion) = res: Posicion {
  asegura prm(res) == prm(pos2) - prm(pos1) ^ sgd(res) == sgd(pos2) - sgd(pos1);
}
*/
Posicion restarPosiciones(const Posicion & pos1, const Posicion & pos2) {
  Posicion p;
  p.x = pos2.x - pos1.x;
  p.y = pos2.y - pos1.y;
  return p;
}

bool Drone::vueloEscalerado() const
{
  // E0
  bool res = enVuelo();
  // E1
  Secuencia<Posicion> posiciones = vueloRealizado();
  //E2
  if (posiciones.size() > 2 && enVuelo()) {
    //E-IF0
    Posicion distancia1a3 = restarPosiciones(posiciones[0], posiciones[2]);
    //E-IF1
    int i = 0;
    //E-IF3
    while (i < (int) posiciones.size() - 2) {
      //E-C0
      Posicion distanciaDeADos = restarPosiciones(posiciones[i], posiciones[i+2]);
      //E-C1
      res = res && distanciaDeADos == distancia1a3;
      //E-C2
      i++;
      //E-C3
    }
    //E-IF4
    res = res && distancia1a3.x != 0 && distancia1a3.y != 0;
    //E-IF5
  }
  //E3
  return res;
  //E4
}
