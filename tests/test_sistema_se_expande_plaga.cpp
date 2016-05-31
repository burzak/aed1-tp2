#include <sistema.h>
#include "gtest/gtest.h"
#include "factories.h"
#include "aux.h"

TEST(test_sistema_se_expande_plaga, si_no_hay_plaga_no_cambia) {
    Campo campo_3x3({0, 0}, {0, 1}, {3, 3});
    Sistema s1(campo_3x3, algunos_drones());

    s1._estado.parcelas[0][2] = RecienSembrado;
    s1._estado.parcelas[1][0] = NoSensado;
    s1._estado.parcelas[1][1] = RecienSembrado;
    s1._estado.parcelas[1][2] = EnCrecimiento;
    s1._estado.parcelas[2][0] = ConMaleza;
    s1._estado.parcelas[2][1] = ListoParaCosechar;
    s1._estado.parcelas[2][2] = EnCrecimiento;

    s1.seExpandePlaga();

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

TEST(test_sistema_se_expande_plaga, si_hay_plaga_se_expande) {
    Campo campo_3x3({0, 0}, {0, 1}, {3, 3});
    Sistema s1(campo_3x3, algunos_drones());

    s1._estado.parcelas[0][2] = ConPlaga;
    s1._estado.parcelas[1][0] = NoSensado;
    s1._estado.parcelas[1][1] = RecienSembrado;
    s1._estado.parcelas[1][2] = ConPlaga;
    s1._estado.parcelas[2][0] = ConMaleza;
    s1._estado.parcelas[2][1] = ListoParaCosechar;
    s1._estado.parcelas[2][2] = EnCrecimiento;

    s1.seExpandePlaga();

    EXPECT_EQ(s1.estadoDelCultivo({0, 2}), ConPlaga);
    EXPECT_EQ(s1.estadoDelCultivo({1, 0}), NoSensado);
    EXPECT_EQ(s1.estadoDelCultivo({1, 1}), ConPlaga);
    EXPECT_EQ(s1.estadoDelCultivo({1, 2}), ConPlaga);
    EXPECT_EQ(s1.estadoDelCultivo({2, 0}), ConMaleza);
    EXPECT_EQ(s1.estadoDelCultivo({2, 1}), ListoParaCosechar);
    EXPECT_EQ(s1.estadoDelCultivo({2, 2}), ConPlaga);

    EXPECT_EQ(s1.campo(), campo_3x3);
    EXPECT_TRUE(test::mismos(s1.enjambreDrones(), algunos_drones()));
}
