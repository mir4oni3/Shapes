#include <catch2/catch_test_macros.hpp>
#include <cfloat>

#include "../src/headers/Figures.hpp"

TEST_CASE("ToString", "[tostring]") {

    SECTION("Triangle1") {
        Triangle t(2, 2, 3);
        REQUIRE(t.toString() == "triangle 2 2 3");
    }

    SECTION("Triangle2") {
        Triangle t(123.111, 99.123, 31.999);
        REQUIRE(t.toString() == "triangle 123.111 99.123 31.999");
    }

    SECTION("Triangle3") {
        Triangle t(0, 0, 0);
        REQUIRE(t.toString() == "triangle 1 1 1");
    }

    SECTION("Triangle4") {
        Triangle t(-5, -10, 30);
        REQUIRE(t.toString() == "triangle 1 1 1");
    }

    SECTION("Triangle5") {
        Triangle t(DBL_MAX, DBL_MAX, DBL_MAX);
        REQUIRE(t.toString() == "triangle 1 1 1");
    }

    SECTION("Circle1") {
        Circle c(5);
        REQUIRE(c.toString() == "circle 5");
    }

    SECTION("Circle2") {
        Circle c(123.123);
        REQUIRE(c.toString() == "circle 123.123");
    }

    SECTION("Circle3") {
        Circle c(0);
        REQUIRE(c.toString() == "circle 1");
    }

    SECTION("Circle4") {
        Circle c(-5);
        REQUIRE(c.toString() == "circle 1");
    }

    SECTION("Circle5") {
        Circle c(DBL_MAX);
        REQUIRE(c.toString() == "circle 1");
    }

    SECTION("Rectangle1") {
        Rectangle r(5, 10);
        REQUIRE(r.toString() == "rectangle 5 10");
    }

    SECTION("Rectangle2") {
        Rectangle r(123.123, 321.321);
        REQUIRE(r.toString() == "rectangle 123.123 321.321");
    }

    SECTION("Rectangle3") {
        Rectangle r(0, 0);
        REQUIRE(r.toString() == "rectangle 1 1");
    }

    SECTION("Rectangle4") {
        Rectangle r(-5, 10);
        REQUIRE(r.toString() == "rectangle 1 1");
    }

    SECTION("Rectangle5") {
        Rectangle r(DBL_MAX / 2, DBL_MAX / 2);
        REQUIRE(r.toString() == "rectangle 1 1");
    }
    
}