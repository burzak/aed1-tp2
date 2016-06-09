bool Sistema::listoParaCosechar() const
{
  //E0
  int i = 0;
  //E1
  Dimension dim = campo().dimensiones();
  //E2
  float parcelasListas = 0;
  //E3
  float cantidadParcelas = dim.ancho * dim.largo;
  //E4
  while (i < cantidadParcelas){
    //E-C0
    Posicion pos{i/dim.largo, i % dim.largo};
    //E-C1
    if(campo().contenido(pos) == Cultivo && estadoDelCultivo(pos) == ListoParaCosechar){
      //E-CIF-1
      parcelasListas++;
      //E-CIF-2
    }
    //E-C2
    i++;
    //E-C3
  }

  //E5
  //Magia matematica para no comparar floats.
  //cantidadParcelas es ancho*alto del campo menos la casa y el granero => (ancho*largo) - 2
  int res = (parcelasListas/(cantidadParcelas-2))*100;

  //E6
  return res >= 90;
  //E7
}
