#include <catch2/catch_test_macros.hpp>
#include <cfloat>

#include "../src/headers/Figures.hpp"
#include "../src/headers/Constants.hpp"

TEST_CASE("Triangle", "[triangle]") {

    SECTION("Normal Params") {
        REQUIRE(std::abs(Triangle(10, 20, 25).getPerimeter() - 55) <= epsilon);
        REQUIRE(std::abs(Triangle(13.123, 14.98, 24.315).getPerimeter() - (13.123 + 14.98 + 24.315)) <= epsilon);
    }

    SECTION("Big params") {
        double big = DBL_MAX / 6;
        Triangle t(big, big, big);
        REQUIRE(std::abs(t.getPerimeter() - 3 * big) <= epsilon);
    }

    SECTION("Small params") {
        Triangle t(0.000005, 0.000004, 0.000005);
        REQUIRE(std::abs(t.getPerimeter() - (0.000005 + 0.000004 + 0.000005)) <= epsilon);
    }

    SECTION("Zero Side") {
        //Check for correct default values (1,1,1 with perimeter 3) in case of zero sides
        REQUIRE(std::abs(Triangle(0, 20, 30).getPerimeter() - 3) <= epsilon);
        REQUIRE(std::abs(Triangle(0, 0, 30).getPerimeter() - 3) <= epsilon);
        REQUIRE(std::abs(Triangle(30, 20, 0).getPerimeter() - 3) <= epsilon);
    }

    SECTION ("Negative Side") {
        //Check for correct default values (1,1,1 with perimeter 3) in case of negative sides
        REQUIRE(std::abs(Triangle(-5, 50, -30).getPerimeter() - 3) <= epsilon);
        REQUIRE(std::abs(Triangle(0, -20, 70).getPerimeter() - 3) <= epsilon);
        REQUIRE(std::abs(Triangle(30, 20, -5).getPerimeter() - 3) <= epsilon);
    }

    SECTION("Perimeter overflow") {
        //Check for correct default values (1,1,1 with perimeter 3) in case of perimeter overflow
        REQUIRE(std::abs(Triangle(DBL_MAX, 20, 30).getPerimeter() - 3) <= epsilon);
        REQUIRE(std::abs(Triangle(30, DBL_MAX, 20).getPerimeter() - 3) <= epsilon);
        REQUIRE(std::abs(Triangle(30, 20, DBL_MAX).getPerimeter() - 3) <= epsilon);
    }

    SECTION("Unsatisfied triangle inequality") {
         //Check for correct default values (1,1,1 with perimeter 3) in case of unsatisfied triangle inequality
        REQUIRE(std::abs(Triangle(1, 2, 3).getPerimeter() - 3) <= epsilon);
        REQUIRE(std::abs(Triangle(100, 1, 99).getPerimeter() - 3) <= epsilon);
        REQUIRE(std::abs(Triangle(500, 2, 300).getPerimeter() - 3) <= epsilon);
    }
    
}