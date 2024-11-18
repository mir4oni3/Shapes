#include <catch2/catch_test_macros.hpp>
#include <cfloat>

#include "../src/headers/Figures.hpp"
#include "../src/headers/Constants.hpp"

TEST_CASE("Cloning", "[cloning]") {
    SECTION("Triangle") {
        Triangle t(2, 2, 3);
        REQUIRE(t.clone()->toString() == "triangle 2 2 3");
    }

    SECTION("Triangle2") {
        Triangle t(123.111, 99.123, 31.999);
        REQUIRE(t.clone()->toString() == "triangle 123.111 99.123 31.999");
    }

    SECTION("Triangle3") {
        Triangle t(0, 0, 0);
        REQUIRE(t.clone()->toString() == "triangle 1 1 1");
    }

    SECTION("Triangle4") {
        Triangle t(-5, -10, 30);
        REQUIRE(t.clone()->toString() == "triangle 1 1 1");
    }

    SECTION("Triangle5") {
        Triangle t(DBL_MAX, DBL_MAX, DBL_MAX);
        REQUIRE(t.clone()->toString() == "triangle 1 1 1");
    }

    SECTION("Circle1") {
        Circle c(5);
        REQUIRE(c.clone()->toString() == "circle 5");
    }

    SECTION("Circle2") {
        Circle c(123.123);
        REQUIRE(c.clone()->toString() == "circle 123.123");
    }

    SECTION("Circle3") {
        Circle c(0);
        REQUIRE(c.clone()->toString() == "circle 1");
    }

    SECTION("Circle4") {
        Circle c(-5);
        REQUIRE(c.clone()->toString() == "circle 1");
    }

    SECTION("Circle5") {
        Circle c(DBL_MAX);
        REQUIRE(c.clone()->toString() == "circle 1");
    }

    SECTION("Rectangle1") {
        Rectangle r(5, 10);
        REQUIRE(r.clone()->toString() == "rectangle 5 10");
    }

    SECTION("Rectangle2") {
        Rectangle r(123.123, 321.321);
        REQUIRE(r.clone()->toString() == "rectangle 123.123 321.321");
    }

    SECTION("Rectangle3") {
        Rectangle r(0, 0);
        REQUIRE(r.clone()->toString() == "rectangle 1 1");
    }

    SECTION("Rectangle4") {
        Rectangle r(-5, 10);
        REQUIRE(r.clone()->toString() == "rectangle 1 1");
    }

    SECTION("Rectangle5") {
        Rectangle r(DBL_MAX / 2, DBL_MAX / 2);
        REQUIRE(r.clone()->toString() == "rectangle 1 1");
    }
    
}