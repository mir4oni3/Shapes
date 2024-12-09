/*
    name:
     FigureStringParser
   
    description:
     Figure Factory, creates a figure from a string. Not to be confused
     with FigureFactory.hpp, which is a factory that creates different figure factories.
    
    NOTES: 
    1.) In case of invalid values for the parameters, a default figure is created.

    2.) The createFigure function has no exception safety and throws an exception in these cases:
            -the figure type is unknown
            -there are extra/not enough parameters
*/

#pragma once

#include <unordered_map>

#include "Figures.hpp"

class FigureStringParser {
    static const std::unordered_map<std::string, int> paramCount;
public:
    std::unique_ptr<Figure> createFigure(const std::string& figureStr) const;
};