/*
    name:
     FigureStringParser
   
    description:
     Figure Factory, creates a figure from a string. Not to be confused
     with FigureFactory.hpp, which is a factory that creates different figure factories.
    
    usage:
     Since the createFigure function is static, you don't need to create an instance of this class.
*/

#pragma once

#include "Figures.hpp"

class FigureStringParser {
public:
    static std::unique_ptr<Figure> createFigure(const std::string& figureStr);
};