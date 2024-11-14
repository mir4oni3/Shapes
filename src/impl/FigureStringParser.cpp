#include <sstream>

#include "../headers/FigureStringParser.hpp"

std::unique_ptr<Figure> FigureStringParser::createFigure(const std::string& figureStr) {
    std::istringstream iStringStream(figureStr);
    std::string figureType;

    iStringStream >> figureType;

    std::unique_ptr<Figure> result = nullptr;
    if (figureType == "Triangle") {
        double a, b, c;
        iStringStream >> a >> b >> c;
        result = std::make_unique<Triangle>(a, b, c);
    } else if (figureType == "Circle") {
        double r;
        iStringStream >> r;
        result = std::make_unique<Circle>(r);
    } else if (figureType == "Rectangle") {
        double a, b;
        iStringStream >> a >> b;
        result = std::make_unique<Rectangle>(a, b);
    } else {
        throw std::invalid_argument("Unknown figure type");
    }

    if (!iStringStream) {
        throw std::invalid_argument("Invalid figure parameters");
    }

    if (iStringStream.peek() != EOF) {
        throw std::invalid_argument("Untrimmed string/Extra parameters");
    }

    return result;
}