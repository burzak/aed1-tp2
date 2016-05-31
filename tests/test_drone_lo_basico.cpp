#include <fstream>
#include <algorithm>
#include <drone.h>
#include "gtest/gtest.h"
#include "factories.h"
#include "aux.h"

TEST(test_drone_lo_basico, crear_drone_y_sus_observadores_funcionan_ok) {
    Drone d1(1, algunos_productos());
    EXPECT_EQ(d1.id(), 1);
    EXPECT_EQ(d1.bateria(), 100);
    EXPECT_TRUE(!d1.enVuelo());
    EXPECT_TRUE(d1.vueloRealizado().empty());
    EXPECT_TRUE(test::mismos({HerbicidaLargoAlcance, Herbicida, PlaguicidaBajoConsumo}, d1.productosDisponibles()));
}

TEST(test_drone_lo_basico, igualdad_drone_funciona_ok) {
    Drone d1(1, algunos_productos());
    Drone d2(1, algunos_productos_pero_en_otro_orden());
    EXPECT_TRUE(d1 == d2);

    Drone d3(2, algunos_productos());
    EXPECT_FALSE(d1 == d3);

    Drone d4(1, otros_productos());
    EXPECT_FALSE(d1 == d4);

    Posicion p = d1.posicionActual();
    p.x++;
    p.y++;
    Drone d5(1, algunos_productos());
    d5.cambiarPosicionActual(p);
    EXPECT_FALSE(d1 == d5);
}

TEST(test_drone_lo_basico, mover_a_funciona_ok) {
    Drone d1 = un_drone();
    EXPECT_TRUE(!d1.enVuelo());
    EXPECT_TRUE(d1.vueloRealizado().empty());

    d1.moverA(Posicion{0, 1});
    d1.moverA(Posicion{0, 2});

    EXPECT_EQ(d1.id(), 1);
    EXPECT_EQ(d1.bateria(), 100);
    EXPECT_TRUE(d1.enVuelo());
    std::vector<Posicion> vueloRealizado = {{0, 1},
                                            {0, 2}};
    EXPECT_EQ(d1.vueloRealizado(), vueloRealizado);
    EXPECT_TRUE(test::mismos(d1.productosDisponibles(), algunos_productos()));
}

TEST(test_drone_lo_basico, set_bateria_funciona_ok) {
    Drone d1 = un_drone();
    d1.setBateria(30);
    EXPECT_EQ(d1.bateria(), 30);
}

TEST(test_drone_lo_basico, borrar_vuelo_realizado_funciona_ok) {
    Drone d1 = un_drone();
    d1.moverA(Posicion{0, 1});
    d1.moverA(Posicion{0, 2});
    d1.moverA(Posicion{0, 3});

    d1.borrarVueloRealizado();

    EXPECT_EQ(d1.id(), 1);
    EXPECT_EQ(d1.bateria(), 100);
    EXPECT_TRUE(!d1.enVuelo());
    EXPECT_TRUE(d1.vueloRealizado().empty());
    EXPECT_TRUE(test::mismos(d1.productosDisponibles(), algunos_productos()));
}

TEST(test_drone_lo_basico, cambiar_posicion_actual_funciona_ok) {
    Drone d1 = un_drone();
    Posicion posicionInicial = {0, 0};
    EXPECT_EQ(d1.posicionActual(), posicionInicial);

    Posicion nuevaPosicion = {10, 10};
    d1.cambiarPosicionActual(nuevaPosicion);
    EXPECT_EQ(d1.posicionActual(), nuevaPosicion);
}

TEST(test_drone_lo_basico, sacar_producto_funciona_ok) {
    Drone d1 = un_drone();
    Producto un_producto_cualquiera = HerbicidaLargoAlcance;
    d1.sacarProducto(un_producto_cualquiera);

    EXPECT_EQ(d1.id(), 1);
    EXPECT_EQ(d1.bateria(), 100);
    EXPECT_TRUE(!d1.enVuelo());
    EXPECT_TRUE(d1.vueloRealizado().empty());
    EXPECT_TRUE(test::mismos(d1.productosDisponibles(), {PlaguicidaBajoConsumo, Herbicida}));
}
