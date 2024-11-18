#include <catch2/catch_test_macros.hpp>
#include <cfloat>

#include "../src/headers/Figures.hpp"
#include "../src/headers/Constants.hpp"

TEST_CASE("Rectangle", "[rectangle]") {
    SECTION("Normal Params") {
        REQUIRE(std::abs(Rectangle(5, 10).getPerimeter() - 30) <= epsilon);
        REQUIRE(std::abs(Rectangle(123.321, 321.123).getPerimeter() - (2 * 123.321 + 2 * 321.123)) <= epsilon);
    }

    SECTION("Big params") {
        double big = DBL_MAX / 5;
        Rectangle r(big, big);
        REQUIRE(std::abs(r.getPerimeter() - 4 * big) <= epsilon);
    }

    SECTION("Small params") {
        double small = 0.000005;
        Rectangle r(small, small);
        REQUIRE(std::abs(r.getPerimeter() - 4 * small) <= epsilon);
    }

    SECTION("Zero Side") {
        //Check for correct default values (1,1 with perimeter 4) in case of zero sides
        REQUIRE(std::abs(Rectangle(0, 20).getPerimeter() - 4) <= epsilon);
        REQUIRE(std::abs(Rectangle(30, 0).getPerimeter() - 4) <= epsilon);
        REQUIRE(std::abs(Rectangle(0, 0).getPerimeter() - 4) <= epsilon);
    }

    SECTION ("Negative Side") {
        //Check for correct default values (1,1 with perimeter 4) in case of negative sides
        REQUIRE(std::abs(Rectangle(-5, 10).getPerimeter() - 4) <= epsilon);
        REQUIRE(std::abs(Rectangle(20, -20).getPerimeter() - 4) <= epsilon);
        REQUIRE(std::abs(Rectangle(-30, -20).getPerimeter() - 4) <= epsilon);
    }

    SECTION("Perimeter overflow") {
        //Check for correct default values (1,1 with perimeter 4) in case of perimeter overflow
        REQUIRE(std::abs(Rectangle(DBL_MAX / 2, 2).getPerimeter() - 4) <= epsilon);
        REQUIRE(std::abs(Rectangle(30, DBL_MAX).getPerimeter() - 4) <= epsilon);
        REQUIRE(std::abs(Rectangle(DBL_MAX / 3, DBL_MAX / 3).getPerimeter() - 4) <= epsilon);
    }
    
}