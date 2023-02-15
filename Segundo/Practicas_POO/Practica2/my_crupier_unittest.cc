//my_crupier_unittest.cc: My own test to prove the class Crupier

#include "crupier.h"
#include "gtest/gtest.h"

TEST(Crupier, ConstructorParametrosDefecto){
    Crupier c("33XX", "1");

    EXPECT_EQ("33XX", c.getDNI());
    EXPECT_EQ("1", c.getCodigo());
    EXPECT_EQ("", c.getNombre());
    EXPECT_EQ("", c.getApellidos());
    EXPECT_EQ(0, c.getEdad());
    EXPECT_EQ("", c.getDireccion());
    EXPECT_EQ("", c.getLocalidad());
    EXPECT_EQ("", c.getProvincia());
    EXPECT_EQ("", c.getPais());
    EXPECT_EQ(", ", c.getApellidosyNombre());   
}

TEST(Crupier, ConstructorParametros){
    Crupier c("33XX", "1", "Silvia", "Roldán", 19, "avda Rabanales s/n", "Córdoba", "Córdoba", "España");

    EXPECT_EQ("33XX", c.getDNI());
    EXPECT_EQ("1", c.getCodigo());
    EXPECT_EQ("Silvia", c.getNombre());
    EXPECT_EQ("Roldán", c.getApellidos());
    EXPECT_EQ(19, c.getEdad());
    EXPECT_EQ("avda Rabanales s/n", c.getDireccion());
    EXPECT_EQ("Córdoba", c.getLocalidad());
    EXPECT_EQ("Córdoba", c.getProvincia());
    EXPECT_EQ("España", c.getPais());
    EXPECT_EQ("Roldán, Silvia", c.getApellidosyNombre());
}

TEST(Crupier, ConstructorCopiaDefecto){
    Crupier c("33XX", "1", "Silvia", "Roldán", 19, "avda Rabanales s/n", "Córdoba", "Córdoba", "España");
    Crupier a(c);
    Crupier b=c;

    EXPECT_EQ("33XX", a.getDNI());
    EXPECT_EQ("1", a.getCodigo());
    EXPECT_EQ("Silvia", a.getNombre());
    EXPECT_EQ("Roldán", a.getApellidos());
    EXPECT_EQ(19, a.getEdad());
    EXPECT_EQ("avda Rabanales s/n", a.getDireccion());
    EXPECT_EQ("Córdoba", a.getLocalidad());
    EXPECT_EQ("Córdoba", a.getProvincia());
    EXPECT_EQ("España", a.getPais());
    EXPECT_EQ("Roldán, Silvia", a.getApellidosyNombre()); 

    EXPECT_EQ("33XX", b.getDNI());
    EXPECT_EQ("1", b.getCodigo());
    EXPECT_EQ("Silvia", b.getNombre());
    EXPECT_EQ("Roldán", b.getApellidos());
    EXPECT_EQ(19, b.getEdad());
    EXPECT_EQ("avda Rabanales s/n", b.getDireccion());
    EXPECT_EQ("Córdoba", b.getLocalidad());
    EXPECT_EQ("Córdoba", b.getProvincia());
    EXPECT_EQ("España", b.getPais());
    EXPECT_EQ("Roldán, Silvia", b.getApellidosyNombre());  
}

TEST(Crupier, OperadorIgualDefecto){
    Crupier c("33XX", "1", "Silvia", "Roldán", 19, "avda Rabanales s/n", "Córdoba", "Córdoba", "España");
    Crupier a("11ZZ", "2");
    a=c;

    EXPECT_EQ("33XX", a.getDNI());
    EXPECT_EQ("1", a.getCodigo());
    EXPECT_EQ("Silvia", a.getNombre());
    EXPECT_EQ("Roldán", a.getApellidos());
    EXPECT_EQ(19, a.getEdad());
    EXPECT_EQ("avda Rabanales s/n", a.getDireccion());
    EXPECT_EQ("Córdoba", a.getLocalidad());
    EXPECT_EQ("Córdoba", a.getProvincia());
    EXPECT_EQ("España", a.getPais());
    EXPECT_EQ("Roldán, Silvia", a.getApellidosyNombre()); 
}