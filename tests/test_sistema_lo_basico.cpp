#include <sistema.h>
#include "gtest/gtest.h"
#include "factories.h"
#include "aux.h"

TEST(test_sistema_lo_basico, crear_sistema_y_sus_observadores_funcionan_ok) {
    Sistema s1(un_campo(), algunos_drones());
    EXPECT_EQ(s1.campo(), un_campo());
    for (int i = 0; i < s1.campo().dimensiones().ancho; i++) {
        for (int j = 0; j < s1.campo().dimensiones().largo; j++) {
            EXPECT_EQ(s1.estadoDelCultivo({i, j}), RecienSembrado);
        }
    }
    EXPECT_TRUE(test::mismos(s1.enjambreDrones(), algunos_drones()));
}

TEST(test_sistema_lo_basico, crecer_funciona_ok) {
    Campo campo_3x3({0, 0}, {0, 1}, {3, 3});
    Sistema s1(campo_3x3, algunos_drones());

    s1._estado.parcelas[0][2] = RecienSembrado;
    s1._estado.parcelas[1][0] = NoSensado;
    s1._estado.parcelas[1][1] = RecienSembrado;
    s1._estado.parcelas[1][2] = EnCrecimiento;
    s1._estado.parcelas[2][0] = ConMaleza;
    s1._estado.parcelas[2][1] = ListoParaCosechar;
    s1._estado.parcelas[2][2] = EnCrecimiento;

    s1.crecer();

    EXPECT_EQ(s1.estadoDelCultivo({0, 2}), EnCrecimiento);
    EXPECT_EQ(s1.estadoDelCultivo({1, 0}), NoSensado);
    EXPECT_EQ(s1.estadoDelCultivo({1, 1}), EnCrecimiento);
    EXPECT_EQ(s1.estadoDelCultivo({1, 2}), ListoParaCosechar);
    EXPECT_EQ(s1.estadoDelCultivo({2, 0}), ConMaleza);
    EXPECT_EQ(s1.estadoDelCultivo({2, 1}), ListoParaCosechar);
    EXPECT_EQ(s1.estadoDelCultivo({2, 2}), ListoParaCosechar);

    EXPECT_TRUE(test::mismos(s1.enjambreDrones(), algunos_drones()));
}
