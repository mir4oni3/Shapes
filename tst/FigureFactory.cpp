#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <sstream>

#include "../src/headers/FigureFactory.hpp"
#include "../src/headers/Figures.hpp"
#include "../src/headers/Constants.hpp"

TEST_CASE("AbstractFigureFactory", "[abstract_figure_factory]") {
    AbstractFigureFactory factory;

    SECTION("Random") {
        std::unique_ptr<FigureFactory> figureFactory = factory.getFigureFactory("random", "");
        REQUIRE(dynamic_cast<RandomFigureFactory*>(figureFactory.get()) != nullptr);
    }

    SECTION("STDIN") {
        std::unique_ptr<FigureFactory> figureFactory = factory.getFigureFactory("stdin", "");
        REQUIRE(dynamic_cast<StreamFigureFactory*>(figureFactory.get()) != nullptr);
    }

    SECTION("File") {
        std::ofstream ofs("ThisIsMyTempFile123.txt");
        std::unique_ptr<FigureFactory> figureFactory = factory.getFigureFactory("file", "ThisIsMyTempFile123.txt");
        REQUIRE(dynamic_cast<StreamFigureFactory*>(figureFactory.get()) != nullptr);
        remove("ThisIsMyTempFile123.txt");
    }

    SECTION("Invalid File") {
        REQUIRE_THROWS_AS(factory.getFigureFactory("file", "ThisFileDoesntExistWOW.txt"), std::invalid_argument);
    }

    SECTION("Unsupported") {
        REQUIRE_THROWS_AS(factory.getFigureFactory("unsupported", ""), std::invalid_argument);
    }

}

TEST_CASE("StreamFigureFactory", "[stream_figure_factory]") {
    //check if nullptr throws exception and check if invalid stream throws exception
    SECTION("nullptr") {
        std::shared_ptr<std::istream> stream;
        REQUIRE_THROWS_AS(StreamFigureFactory(stream), std::invalid_argument);
    }

    SECTION("Invalid stream") {
        std::shared_ptr<std::istream> stream;
        stream = std::make_shared<std::ifstream>("ThisFileDoesntExistWOW.txt");
        REQUIRE_THROWS_AS(StreamFigureFactory(stream), std::invalid_argument);
    }

    SECTION("Check normal data") {
        std::string str =  "triangle 2 2 3\nrectangle 5 10\ncircle 5\n";
        std::shared_ptr<std::istream> stringStream = std::make_shared<std::istringstream>(str);
        StreamFigureFactory factory(stringStream);

        REQUIRE(factory.create()->toString() == "triangle 2 2 3");
        REQUIRE(factory.create()->toString() == "rectangle 5 10");
        REQUIRE(factory.create()->toString() == "circle 5");
        REQUIRE(factory.create()->toString() == "circle 1"); //default circle because last line is empty
    }

    SECTION("Check incorrect data") {
        std::string str =  "triangle 10 60 120\nbla bla bla\ntriangle 2 2 3\nrectangle -20 30\ncircle -13\n";
        std::shared_ptr<std::istream> stringStream = std::make_shared<std::istringstream>(str);
        StreamFigureFactory factory(stringStream);

        REQUIRE(factory.create()->toString() == "triangle 1 1 1"); //default triangle
        REQUIRE(factory.create()->toString() == "circle 1"); //default circle
        REQUIRE(factory.create()->toString() == "triangle 2 2 3"); //correct data
        REQUIRE(factory.create()->toString() == "rectangle 1 1"); //default rectangle
        REQUIRE(factory.create()->toString() == "circle 1"); //default circle 
        REQUIRE(factory.create()->toString() == "circle 1"); //default circle because last line is empty
    }

    SECTION("Check empty stream") {
        //check what happens if stream is empty
        std::shared_ptr<std::istream> stringStream = std::make_shared<std::istringstream>("");
        StreamFigureFactory factory(stringStream);
        REQUIRE(factory.create()->toString() == "circle 1"); //default circle
    }

    SECTION("Check if error occurs") {
        //check what happens if error occurs
        std::string str =  "triangle 2 2 3\nrectangle 5 10\ncircle 5\nrectangle 20 30\n";
        std::shared_ptr<std::istringstream> stringStream = std::make_shared<std::istringstream>(str);
        std::shared_ptr<std::istream> istream = stringStream;

        StreamFigureFactory factory(istream);
        REQUIRE(factory.create()->toString() == "triangle 2 2 3");
        REQUIRE(factory.create()->toString() == "rectangle 5 10");

        stringStream->setstate(std::ios::failbit); //error occurs

        REQUIRE_THROWS_AS(factory.create()->toString(), std::invalid_argument);
    }
    
}

TEST_CASE("RandomFigureFactory", "[random_figure_factory]") {
    srand(time(0));
    const int sampleSize = 100000;
    const double tolerance = 0.03; //if increasing sampleSize, this could be reduced

    std::vector<std::unique_ptr<Figure>> figures(sampleSize);
    RandomFigureFactory factory;
    for (int i = 0;i < sampleSize;i++) {
        figures[i] = factory.create();
    }

    SECTION("Check even figure distribution") {
        int triangles = 0, circles = 0, rectangles = 0;

        for (int i = 0;i < sampleSize;i++) {
            if (dynamic_cast<Triangle*>(figures[i].get())) {
                triangles++;
            } else if (dynamic_cast<Circle*>(figures[i].get())) {
                circles++;
            } else if (dynamic_cast<Rectangle*>(figures[i].get())) {
                rectangles++;
            }
        }

        //the difference between figure count and expected figure count is within allowance
        int expected = sampleSize / 3; // sampleSize / figureTypeCount
        REQUIRE(std::abs(triangles - expected) <= tolerance * expected);
        REQUIRE(std::abs(circles - expected) <= tolerance * expected);
        REQUIRE(std::abs(rectangles - expected) <= tolerance * expected);
    }

    SECTION("Check parameters are within the specified range") {
        std::string dummy;
        double value;

        for (int i = 0;i < sampleSize;i++) {
            std::stringstream sStream(figures[i]->toString());
            sStream >> dummy; //ignore figure type
            while (sStream >> value) {
                REQUIRE(value >= dblrng::MIN_DBL);
                REQUIRE(value <= dblrng::MAX_DBL);
            }
            REQUIRE(sStream.eof());
        }
    }
}