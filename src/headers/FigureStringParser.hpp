/*
    name:
     FigureStringParser
   
    description:
     Figure Factory, creates a figure from a string. Not to be confused
     with FigureFactory.hpp, which is a factory that creates different figure factories.
    
    usage:
     Since the createFigure function is static, you don't need to create an instance of this class.
     
    NOTE: 
     The createFigure function has no exception safety and throws an exception in these cases:
       -the input string is not trimmed properly
       -the figure type is unknown
       -there are extra/not enough parameters
*/

#pragma once

#include "Figures.hpp"

class FigureStringParser {
public:
    std::unique_ptr<Figure> createFigure(const std::string& figureStr) const;
};