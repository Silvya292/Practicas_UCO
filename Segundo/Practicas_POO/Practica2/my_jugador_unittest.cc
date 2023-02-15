//my_jugador_unittest.cc: My own test to prove the class Jugador

#include <fstream>
#include <list>
#include "jugador.h"
#include "gtest/gtest.h"

using namespace std;

TEST(Jugador, ConstructorParametrosDefecto){
    Jugador j("33XX", "1");

    EXPECT_EQ("33XX", j.getDNI());
    EXPECT_EQ("1", j.getCodigo());
    EXPECT_EQ("", j.getNombre());
    EXPECT_EQ("", j.getApellidos());
    EXPECT_EQ(0, j.getEdad());
    EXPECT_EQ("", j.getDireccion());
    EXPECT_EQ("", j.getLocalidad());
    EXPECT_EQ("", j.getProvincia());
    EXPECT_EQ("", j.getPais());
    EXPECT_EQ(", ", j.getApellidosyNombre());   
}

TEST(Jugador, ConstructorParametros){
    Jugador j("33XX", "1", "Silvia", "Roldán", 19, "avda Rabanales s/n", "Córdoba", "Córdoba", "España");

    EXPECT_EQ("33XX", j.getDNI());
    EXPECT_EQ("1", j.getCodigo());
    EXPECT_EQ("Silvia", j.getNombre());
    EXPECT_EQ("Roldán", j.getApellidos());
    EXPECT_EQ(19, j.getEdad());
    EXPECT_EQ("avda Rabanales s/n", j.getDireccion());
    EXPECT_EQ("Córdoba", j.getLocalidad());
    EXPECT_EQ("Córdoba", j.getProvincia());
    EXPECT_EQ("España", j.getPais());
    EXPECT_EQ("Roldán, Silvia", j.getApellidosyNombre());
}

TEST(Jugador, funcionesDinero) {
  Jugador j("33XX", "1");

  EXPECT_EQ(1000, j.getDinero());
  j.setDinero(2000);
  EXPECT_EQ(2000, j.getDinero());
}

TEST(Jugador, setApuestasygetApuestas) {
  Jugador j("49W", "1");
  string nomfich=j.getDNI()+".txt";
  ofstream salida(nomfich.c_str());
  salida << 1 << "," << "21" << "," << 30<< "\n";
  salida << 2 << "," << "rojo" << "," << 15<< "\n";
  salida << 3 << "," << "par" << "," << 20<< "\n";
  salida << 4 << "," << "alto" << "," << 12<< "\n";
  salida.close();
  list<Apuesta> l;
  j.setApuestas();
  l= j.getApuestas();
  EXPECT_EQ(4, l.size());
  list<Apuesta>::iterator i;
  i=l.begin();
  EXPECT_EQ(1, (*i).tipo);
  EXPECT_EQ("21", (*i).valor);
  EXPECT_EQ(30, (*i).cantidad);
  i++;
  EXPECT_EQ(2, (*i).tipo);
  EXPECT_EQ("rojo", (*i).valor);
  EXPECT_EQ(15, (*i).cantidad);
  i++;
  EXPECT_EQ(3, (*i).tipo);
  EXPECT_EQ("par", (*i).valor);
  EXPECT_EQ(20, (*i).cantidad);
  i++;
  EXPECT_EQ(4, (*i).tipo);
  EXPECT_EQ("alto", (*i).valor);
  EXPECT_EQ(12, (*i).cantidad);
}