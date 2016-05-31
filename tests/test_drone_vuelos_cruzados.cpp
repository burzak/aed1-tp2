#include <vector>
#include <drone.h>
#include "aux.h"
#include "gtest/gtest.h"

TEST(test_drone_vuelos_cruzados, ninguno_cruzado) {
    std::vector<Producto> ps;
    Drone d1(1, ps);
    Drone d2(1, ps);
    Drone d3(1, ps);
    d1.moverA({4, 4});
    d1.moverA({4, 5});
    d1.moverA({4, 6});
    d1.moverA({4, 7});

    d2.moverA({5, 4});
    d2.moverA({5, 5});
    d2.moverA({5, 6});
    d2.moverA({5, 7});

    d3.moverA({6, 4});
    d3.moverA({6, 5});
    d3.moverA({6, 6});
    d3.moverA({6, 7});

    std::vector<Drone> ds;
    ds.push_back(d1);
    ds.push_back(d2);
    ds.push_back(d3);
    EXPECT_TRUE(Drone::vuelosCruzados(ds).empty());
}

TEST(test_drone_vuelos_cruzados, cruce_al_final) {
    std::vector<Producto> ps;
    Drone d1(1, ps);
    Drone d2(2, ps);
    Drone d3(3, ps);
    d1.moverA({3, 5});
    d1.moverA({4, 5});
    d1.moverA({4, 6});
    d1.moverA({4, 7});
    d1.moverA({5, 7});

    d2.moverA({4, 4});
    d2.moverA({5, 4});
    d2.moverA({5, 5});
    d2.moverA({5, 6});
    d2.moverA({5, 7});

    d3.moverA({6, 4});
    d3.moverA({6, 5});
    d3.moverA({6, 6});
    d3.moverA({6, 7});
    d3.moverA({5, 7});

    std::vector<Drone> ds;
    ds.push_back(d1);
    ds.push_back(d2);
    ds.push_back(d3);
    EXPECT_EQ(test::cuenta({{5, 7}, 3}, Drone::vuelosCruzados(ds)), 1);
}

TEST(test_drone_vuelos_cruzados, varios_cruces) {
    std::vector<Producto> ps;
    Drone d1(1, ps);
    Drone d2(2, ps);
    Drone d3(3, ps);
    d1.moverA({3, 5});
    d1.moverA({4, 5});
    d1.moverA({4, 6});
    d1.moverA({4, 7});
    d1.moverA({5, 7});
    d1.moverA({4, 7});
    d1.moverA({4, 8});
    d1.moverA({5, 8});

    d2.moverA({4, 4});
    d2.moverA({5, 4});
    d2.moverA({5, 5});
    d2.moverA({5, 6});
    d2.moverA({5, 7});
    d2.moverA({5, 6});
    d2.moverA({5, 7});
    d2.moverA({5, 8});

    d3.moverA({6, 4});
    d3.moverA({6, 5});
    d3.moverA({6, 6});
    d3.moverA({6, 7});
    d3.moverA({5, 7});
    d3.moverA({6, 7});
    d3.moverA({6, 8});
    d3.moverA({5, 8});

    std::vector<Drone> ds;
    ds.push_back(d1);
    ds.push_back(d2);
    ds.push_back(d3);
    EXPECT_EQ(test::cuenta({{5, 7}, 3}, Drone::vuelosCruzados(ds)), 1);
    EXPECT_EQ(test::cuenta({{5, 8}, 3}, Drone::vuelosCruzados(ds)), 1);
}
