#ifndef ELEMENTOS_H_
#define ELEMENTOS_H_

enum class Zona { Granja, Caverna, Pueblo };

enum class Terreno { Pasto, Tierra, Camino, PisoCaverna, Pared, PisoPueblo };

enum class ElementosGranja {
  Cabania1,
  Cabania2,
  Cabania3,
  Cabania4,
  Cabania5,
  //Cabania6,
  Arbol1,
  Arbol2,
  Piedra,
  Agua,
  ArbustoRedondo,
  ArbustoGrande,
  PiedraGrisGrande,
  PiedraGris,
  TroncoCaido,
  Tocon,
  BuzonRojo,
  CartelVacio,
  SalidaPueblo
};

enum class ElementosCaverna {
  Escalera,
  SalidaCaverna,
  Barril,
  Calavera,
  Hueso,
  Escombros,
  Antorcha,
  Candelabro,
  Escudo
};

enum class ElementosPueblo {
  NpcMarnie,
  NpcClint,
  NpcPierre,
  NpcRobin,
  CentroComunitario,
  SalidaGranja,
  EntradaMina,
  FarolNaranja,
  FarolAzul,
  BancoMadera,
  BuzonGris,
  BuzonAzul,
  CasaChica,
  CasaMediana,
  CasaMarnie,
  CasaClint,
  CasaPierre,
  CasaRobin
};

#endif // ELEMENTOS_H_
