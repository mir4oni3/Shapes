#include <sstream>
#include <vector>

#include "../headers/FigureStringParser.hpp"

const std::unordered_map<std::string, int> FigureStringParser::paramCount =
    {
        {"triangle", 3},
        {"circle", 1},
        {"rectangle", 2},
    };

std::unique_ptr<Figure> FigureStringParser::createFigure(const std::string& figureStr) const {
    std::istringstream iStringStream(figureStr);
    std::string figureType;

    iStringStream >> figureType;
    if (paramCount.find(figureType) == paramCount.end()) {
        throw std::invalid_argument("Unknown figure type");
    }

    std::vector<double> params;
    double arg;
    while(iStringStream >> arg) {
        params.push_back(arg);
    }

    if (paramCount.at(figureType) != params.size()) {
        throw std::invalid_argument("Invalid number of parameters");
    }

    if (figureType == "triangle") {
        return std::make_unique<Triangle>(params[0], params[1], params[2]);
    } 
    else if (figureType == "circle") {
        return std::make_unique<Circle>(params[0]);
    } 
    else if (figureType == "rectangle") {
        return std::make_unique<Rectangle>(params[0], params[1]);
    }

    return nullptr;
}