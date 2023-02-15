// my_dados_unittest.cc: Silvia Roldán


#include "dados.h"
#include "gtest/gtest.h"
#include <cmath>

// Tests the c'tor.
TEST(Dados, Constructor) {
  Dados d;
  
  EXPECT_EQ(1, d.getDado1());
  EXPECT_EQ(1, d.getDado2());
  EXPECT_EQ(2, d.getSuma());
}

// Tests operación lanzamiento
TEST(Dados, Lanzamiento) {
  Dados d;
  for (int i=0; i<100; i++){
    d.lanzamiento();
    EXPECT_GT(d.getDado1(), 0);
    EXPECT_LT(d.getDado1(), 7);
    EXPECT_GT(d.getDado2(), 0);
    EXPECT_LT(d.getDado2(), 7);
    }

}

// Tests operación suma
TEST(Dados, Suma) {
  Dados d;
  
  EXPECT_EQ(d.getDado1()+d.getDado2(), d.getSuma());
}

// Tests modificadores
TEST(Dados, Modificadores) {
  Dados d;
  EXPECT_FALSE(d.setDado1(9));
  EXPECT_EQ(1,d.getDado1());
  EXPECT_FALSE(d.setDado1(-9));
  EXPECT_EQ(1,d.getDado1());
  EXPECT_FALSE(d.setDado2(9));
  EXPECT_EQ(1,d.getDado2());
  EXPECT_FALSE(d.setDado2(-9));
  EXPECT_EQ(1,d.getDado2());
  EXPECT_TRUE(d.setDado1(3));
  EXPECT_EQ(3, d.getDado1());
  EXPECT_TRUE(d.setDado2(2));
  EXPECT_EQ(2, d.getDado2());
  EXPECT_EQ(5, d.getSuma());
}


//Tests operación diferencia
TEST(Dados, Diferencia){
  Dados d; 
  EXPECT_EQ(abs(d.getDado1()-d.getDado2()),d.getDiferencia());
  d.setDado1(4);
  d.setDado2(2);
  EXPECT_EQ(2, d.getDiferencia());
  d.setDado1(2);
  d.setDado2(4);
  EXPECT_EQ(2, d.getDiferencia());
}

//Tests lanzamientos de ambos dados
TEST(Dados, Lanzamientos){
  Dados d;
  EXPECT_EQ(0,d.getLanzamientos1());
  EXPECT_EQ(0,d.getLanzamientos2());
  d.setDado1(2);
  EXPECT_EQ(1,d.getLanzamientos1());
  EXPECT_EQ(0,d.getLanzamientos2());
  d.setDado2(3);
  EXPECT_EQ(1,d.getLanzamientos1());
  EXPECT_EQ(1,d.getLanzamientos2());
  for(int i=0;i<9;i++){
    d.lanzamiento();
  }
  EXPECT_EQ(10,d.getLanzamientos1());
  EXPECT_EQ(10,d.getLanzamientos2());
}

//Tests comprobación medias
TEST(Dados, Medias){
  Dados d;
  EXPECT_EQ(0,d.getMedia1());
  EXPECT_EQ(0,d.getMedia2());
  d.setDado1(2);
  d.setDado2(3);
  EXPECT_EQ(2,d.getMedia1());
  EXPECT_EQ(3,d.getMedia2());
  d.setDado1(2);
  d.setDado2(4);
  EXPECT_EQ(2,d.getMedia1());
  EXPECT_EQ(3.5,d.getMedia2());
}

//Test mostrar últimos cinco valores
TEST(Dados, Ultimos){
  Dados d;
  int v1[5],v2[5];
  for(int i=0;i<5;i++){
    d.setDado1(i+1);
    d.setDado2(i+1);
  }
  d.getUltimos1(v1);
  d.getUltimos2(v2);
  for(int i=0;i<5;i++){
    EXPECT_EQ(5-i,v1[i]);
    EXPECT_EQ(5-i,v2[i]);
  }
}