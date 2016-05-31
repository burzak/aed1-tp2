#include <fstream>
#include "gtest/gtest.h"
#include "factories.h"

TEST(test_campo, crear_campo_y_sus_observadores_funcionan_ok) {
    Campo c1({5, 10}, {8, 12});
    EXPECT_EQ(c1.contenido({5, 10}), Granero);
    EXPECT_EQ(c1.contenido({8, 12}), Casa);
}

TEST(test_campo, guardar_y_cargar_campo_funcionan_ok) {
    Campo c1 = un_campo();

    char fname[] = "test_campo.txt";
    std::ofstream out;
    out.open(fname);
    c1.guardar(out);
    Campo c2;
    out.close();
    std::ifstream in(fname);
    c2.cargar(in);
    in.close();

    EXPECT_EQ(c1, c2);
}