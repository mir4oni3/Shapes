#include <fstream>
#include <algorithm>
#include <string>
#include <cfloat>

#include "../headers/FigureFactory.hpp"
#include "../headers/Constants.hpp"
#include "../headers/FigureStringParser.hpp"

std::unique_ptr<FigureFactory> AbstractFigureFactory::getFigureFactory(const std::string& FigureFactoryType, const std::string& filename) const {
    if (FigureFactoryType == "random") {
        return std::make_unique<RandomFigureFactory>();
    } else if (FigureFactoryType == "stdin") {
        std::shared_ptr<std::istream> stream(&std::cin, [](std::istream*) { });
        return std::make_unique<StreamFigureFactory>(stream);
    } else if (FigureFactoryType == "file") {
        std::shared_ptr<std::istream> stream = std::make_shared<std::ifstream>(filename, std::ios::in);
        if (!stream || !*stream) {
            throw std::invalid_argument("Invalid file");
        }
        return std::make_unique<StreamFigureFactory>(stream);
    } else {
        throw std::invalid_argument("Unsupported factory type");
    }
}

namespace {
    double generateRandomDouble(double min, double max) {
        //uniform distribution between min and max
        double random = (double) rand() / RAND_MAX; // generate random number between 0 and 1
        return min + random * (max - min); // scale and shift
    }
    std::unique_ptr<Triangle> createRandomTriangle() {
        //ensure triangle inequality is kept, all sides are between the specified in Constants.hpp range, and the perimeter doesn't exceed DBL_MAX
        double sides[3];
        sides[0] = generateRandomDouble(dblrng::MIN_DBL, std::min(dblrng::MAX_DBL, DBL_MAX / 2 - epsilon));
        sides[1] = generateRandomDouble(dblrng::MIN_DBL, std::min(dblrng::MAX_DBL, DBL_MAX / 2 - epsilon));
        sides[2] = generateRandomDouble(std::max(dblrng::MIN_DBL, std::abs(sides[0] - sides[1])), std::min(dblrng::MAX_DBL, sides[0] + sides[1]));
        
        //in our case, triangle with sides A,B,C will be considered different from triangle with sides B,A,C
        int choose = rand() % 3; // choose which will be side A
        std::swap(sides[0], sides[choose]);
        choose = rand() % 2 + 1; // choose which will be side B
        std::swap(sides[1], sides[choose]);

        return std::make_unique<Triangle>(sides[0], sides[1], sides[2]);
    }

    std::unique_ptr<Circle> createRandomCircle() {
        double radius = generateRandomDouble(dblrng::MIN_DBL, std::min(dblrng::MAX_DBL, DBL_MAX / (2 * mathPI) - epsilon));
        return std::make_unique<Circle>(radius);
    }

    std::unique_ptr<Rectangle> createRandomRectangle() {
        double a = generateRandomDouble(dblrng::MIN_DBL, std::min(dblrng::MAX_DBL, DBL_MAX / 2 - epsilon));
        double b = generateRandomDouble(dblrng::MIN_DBL, std::min(dblrng::MAX_DBL, (DBL_MAX - 2 * a) / 2 - epsilon));
        
        //in our case, rectangle with sides A,B will be considered different from rectangle with sides B,A
        if (rand() % 2) {
            std::swap(a, b);
        }

        return std::make_unique<Rectangle>(a, b);
    }
}

std::unique_ptr<Figure> RandomFigureFactory::create() const {
    int choice = rand() % 3;
    if (choice == 0) {
        return createRandomTriangle();
    } 
    else if (choice == 1) {
        return createRandomCircle();
    } 
    else {
        return createRandomRectangle();
    }
}

StreamFigureFactory::StreamFigureFactory(std::shared_ptr<std::istream>& in) : stream(in) {
    if (!stream || !*stream) {
        throw std::invalid_argument("Invalid stream");
    }
}

std::unique_ptr<Figure> StreamFigureFactory::create() const {
    if (!stream || !*stream) {
        throw std::invalid_argument("Invalid stream/No more data");
    }

    if (stream->peek() == '\n') {
        stream->ignore();
    }
    std::string figureStr;
    std::getline(*stream, figureStr);

    std::unique_ptr<Figure> result;
    try {
        result = FigureStringParser::createFigure(figureStr);
    } catch (std::invalid_argument& e) {
        std::cout << "Exception thrown! " << std::endl << e.what() << std::endl;
        std::cout << "Type: " + figureStr + " doesn't exist" << std::endl;
        std::cout << "Creating default circle with radius 1 instead..." << std::endl;
        std::cout << std::endl << std::endl;
        result = std::make_unique<Circle>(1);
    }

    return result;
}