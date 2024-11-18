#include <catch2/catch_test_macros.hpp>
#include <cfloat>

#include "../src/headers/Figures.hpp"
#include "../src/headers/Constants.hpp"

TEST_CASE("Circle", "[circle]") {

    SECTION("Normal Params") {
        REQUIRE(std::abs(Circle(5).getPerimeter() - 10 * mathPI) <= epsilon);
        REQUIRE(std::abs(Circle(353.765).getPerimeter() - 2 * 353.765 * mathPI) <= epsilon);
    }

    SECTION("Big params") {
        double big = DBL_MAX / (4 * mathPI);
        REQUIRE(std::abs(Circle(big).getPerimeter() - 2 * mathPI * big) <= epsilon);
    }

    SECTION("Small params") {
        double small = 0.000005;
        REQUIRE(std::abs(Circle(small).getPerimeter() - 2 * mathPI * small) <= epsilon);
    }

    SECTION("Zero Radius") {
        //Check for correct default values (1 with perimeter 2*pi) in case of zero radius
        REQUIRE(std::abs(Circle(0).getPerimeter() - 2 * mathPI) <= epsilon);
    }

    SECTION ("Negative Radius") {
        //Check for correct default values (1 with perimeter 2*pi) in case of negative radius
        REQUIRE(std::abs(Circle(-1).getPerimeter() - 2 * mathPI) <= epsilon);
        REQUIRE(std::abs(Circle(-123).getPerimeter() - 2 * mathPI) <= epsilon);
        REQUIRE(std::abs(Circle(-3412.2311).getPerimeter() - 2 * mathPI) <= epsilon);
    }

    SECTION("Perimeter overflow") {
        //Check for correct default values (1 with perimeter 2*pi) in case of perimeter overflow
        REQUIRE(std::abs(Circle(DBL_MAX).getPerimeter() - 2 * mathPI) <= epsilon);
    }
    
}