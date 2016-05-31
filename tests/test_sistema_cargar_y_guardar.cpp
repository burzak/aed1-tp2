#include <fstream>
#include <sistema.h>
#include "gtest/gtest.h"
#include "factories.h"

TEST(test_sistema, guardar_y_cargar_sistema_funcionan_ok) {
    Sistema s1(un_campo(), algunos_drones());

    char fname[] = "test_sistema.txt";
    std::ofstream out;
    out.open(fname);
    s1.guardar(out);
    Sistema s2;
    out.close();
    std::ifstream in(fname);
    s2.cargar(in);
    in.close();

    EXPECT_EQ(s1, s2);
}