#include <sistema.h>
#include "gtest/gtest.h"
#include "factories.h"
#include "aux.h"

TEST(test_sistema_se_vino_la_maleza, lista_vacia_no_modifica_nada) {
    Campo campo_3x3({0, 0}, {0, 1}, {3, 3});
    Sistema s1(campo_3x3, algunos_drones());

    s1._estado.parcelas[0][2] = RecienSembrado;
    s1._estado.parcelas[1][0] = NoSensado;
    s1._estado.parcelas[1][1] = RecienSembrado;
    s1._estado.parcelas[1][2] = EnCrecimiento;
    s1._estado.parcelas[2][0] = ConMaleza;
    s1._estado.parcelas[2][1] = ListoParaCosechar;
    s1._estado.parcelas[2][2] = EnCrecimiento;

    s1.seVinoLaMaleza({});

    EXPECT_EQ(s1.estadoDelCultivo({0, 2}), RecienSembrado);
    EXPECT_EQ(s1.estadoDelCultivo({1, 0}), NoSensado);
    EXPECT_EQ(s1.estadoDelCultivo({1, 1}), RecienSembrado);
    EXPECT_EQ(s1.estadoDelCultivo({1, 2}), EnCrecimiento);
    EXPECT_EQ(s1.estadoDelCultivo({2, 0}), ConMaleza);
    EXPECT_EQ(s1.estadoDelCultivo({2, 1}), ListoParaCosechar);
    EXPECT_EQ(s1.estadoDelCultivo({2, 2}), EnCrecimiento);

    EXPECT_EQ(s1.campo(), campo_3x3);
    EXPECT_TRUE(test::mismos(s1.enjambreDrones(), algunos_drones()));
}

TEST(test_sistema_se_vino_la_maleza, se_pone_con_maleza_las_posiciones_de_la_lista) {
    Campo campo_3x3({0, 0}, {0, 1}, {3, 3});
    Sistema s1(campo_3x3, algunos_drones());

    s1._estado.parcelas[0][2] = RecienSembrado;
    s1._estado.parcelas[1][0] = NoSensado;
    s1._estado.parcelas[1][1] = RecienSembrado;
    s1._estado.parcelas[1][2] = EnCrecimiento;
    s1._estado.parcelas[2][0] = ConMaleza;
    s1._estado.parcelas[2][1] = ListoParaCosechar;
    s1._estado.parcelas[2][2] = EnCrecimiento;

    s1.seVinoLaMaleza({{0, 2},
                       {1, 2}});

    EXPECT_EQ(s1.estadoDelCultivo({0, 2}), ConMaleza);
    EXPECT_EQ(s1.estadoDelCultivo({1, 0}), NoSensado);
    EXPECT_EQ(s1.estadoDelCultivo({1, 1}), RecienSembrado);
    EXPECT_EQ(s1.estadoDelCultivo({1, 2}), ConMaleza);
    EXPECT_EQ(s1.estadoDelCultivo({2, 0}), ConMaleza);
    EXPECT_EQ(s1.estadoDelCultivo({2, 1}), ListoParaCosechar);
    EXPECT_EQ(s1.estadoDelCultivo({2, 2}), EnCrecimiento);

    EXPECT_EQ(s1.campo(), campo_3x3);
    EXPECT_TRUE(test::mismos(s1.enjambreDrones(), algunos_drones()));
}
