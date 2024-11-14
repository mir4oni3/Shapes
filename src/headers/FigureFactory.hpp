/*
    name:
        FigureFactory

    description:
        The AbstractFigureFactory is an abstract factory for figure factories.
        Different figure factories need to be declared here.
*/
#pragma once

#include "Figures.hpp"

class AbstractFigureFactory {
public:
    std::unique_ptr<FigureFactory> getFigureFactory(const std::string& FigureFactoryType, const std::string& filename) const;
    virtual ~AbstractFigureFactory() = default;
};

class FigureFactory {
public:
    virtual std::unique_ptr<Figure> create() const = 0;
    virtual ~FigureFactory() = default;
};

class RandomFigureFactory : public FigureFactory {
public:
    std::unique_ptr<Figure> create() const override;
};

class StreamFigureFactory : public FigureFactory {
public:
    StreamFigureFactory(std::istream& in); // either STDIN(using cin maybe) or from file(using ifstream maybe)
    std::unique_ptr<Figure> create() const override; // read a line of text from the stream and then pass it to the FigureStringParser factory
};