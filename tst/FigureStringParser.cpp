#include <catch2/catch_test_macros.hpp>

#include "../src/headers/Figures.hpp"
#include "../src/headers/Constants.hpp"
#include "../src/headers/FigureStringParser.hpp"

TEST_CASE("FigureStringParser", "[figure_string_parser]") {
    FigureStringParser parser;
    
    SECTION("Unknown figure") {
        REQUIRE_THROWS_AS(parser.createFigure("wow 2 2 3"), std::invalid_argument);
        REQUIRE_THROWS_AS(parser.createFigure("triangl 2 2 3"), std::invalid_argument);
        REQUIRE_THROWS_AS(parser.createFigure("wow wow wow WOOW"), std::invalid_argument);
        REQUIRE_THROWS_AS(parser.createFigure("hmm 1 2 mmh"), std::invalid_argument);
    }

    SECTION("Empty string") {
        REQUIRE_THROWS_AS(parser.createFigure(""), std::invalid_argument);
    }

    SECTION("Triangle1") {
        std::string str = "triangle 2 2 3";
        std::unique_ptr<Figure> t = parser.createFigure(str);
        REQUIRE(t->toString() == str);
    }

    SECTION("Triangle2") {
        std::string str = "triangle 123.111 99.123 31.999";
        std::unique_ptr<Figure> t = parser.createFigure(str);
        REQUIRE(t->toString() == str);
    }

    SECTION("Triangle3") {
        std::string str = "triangle 1 1";
        REQUIRE_THROWS_AS(parser.createFigure(str), std::invalid_argument);
    }

    SECTION("Triangle4") {
        std::string str = "triangle 1 1 1 1";
        REQUIRE_THROWS_AS(parser.createFigure(str), std::invalid_argument);
    }

    SECTION("Triangle5") {
        std::string str = "triangle    2         2           3";
        REQUIRE(parser.createFigure(str)->toString() == "triangle 2 2 3");
    }

    SECTION("Triangle6") {
        std::string str = "triangle 1 2 3";
        REQUIRE(parser.createFigure(str)->toString() == "triangle 1 1 1");
    }

    SECTION("Triangle7") {
        std::string str = "triangle 2 2 3 ";
        REQUIRE(parser.createFigure(str)->toString() == "triangle 2 2 3");
    }
    
    SECTION("Circle1") {
        std::string str = "circle 5";
        std::unique_ptr<Figure> c = parser.createFigure(str);
        REQUIRE(c->toString() == str);
    }

    SECTION("Circle2") {
        std::string str = "circle 123.123";
        std::unique_ptr<Figure> c = parser.createFigure(str);
        REQUIRE(c->toString() == str);
    }

    SECTION("Circle3") {
        std::string str = "circle";
        REQUIRE_THROWS_AS(parser.createFigure(str), std::invalid_argument);
    }

    SECTION("Circle4") {
        std::string str = "circle 1 1";
        REQUIRE_THROWS_AS(parser.createFigure(str), std::invalid_argument);
    }

    SECTION("Circle5") {
        std::string str = "circle    5";
        REQUIRE(parser.createFigure(str)->toString() == "circle 5");
    }

    SECTION("Circle6") {
        std::string str = "circle -123";
        REQUIRE(parser.createFigure(str)->toString() == "circle 1");
    }
   
    SECTION("Circle7") {
        std::string str = "circle 1 ";
        REQUIRE(parser.createFigure(str)->toString() == "circle 1");
    }

    SECTION("Rectangle1") {
        std::string str = "rectangle 5 10";
        std::unique_ptr<Figure> r = parser.createFigure(str);
        REQUIRE(r->toString() == str);
    }

    SECTION("Rectangle2") {
        std::string str = "rectangle 123.123 321.321";
        std::unique_ptr<Figure> r = parser.createFigure(str);
        REQUIRE(r->toString() == str);
    }

    SECTION("Rectangle3") {
        std::string str = "rectangle 10";
        REQUIRE_THROWS_AS(parser.createFigure(str), std::invalid_argument);
    }

    SECTION("Rectangle4") {
        std::string str = "rectangle 1 1 1";
        REQUIRE_THROWS_AS(parser.createFigure(str), std::invalid_argument);
    }

    SECTION("Rectangle5") {
        std::string str = "rectangle    5         10";
        REQUIRE(parser.createFigure(str)->toString() == "rectangle 5 10");
    }

    SECTION("Rectangle6") {
        std::string str = "rectangle -5 10";
        REQUIRE(parser.createFigure(str)->toString() == "rectangle 1 1");
    }

    SECTION("Rectangle7") {
        std::string str = "rectangle 1 2 ";
        REQUIRE(parser.createFigure(str)->toString() == "rectangle 1 2");
    }

}