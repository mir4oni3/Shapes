/*
    name:
        FigureFactory

    description:
        The AbstractFigureFactory is an abstract factory for figure factories.
        Different figure factories need to be declared here.
        
        1.) StreamFigureFactory:
         Creates figures, read from an istream.
         It receives a shared pointer to an istream, but the factory doesn't own the stream!
         This means it shouldn't be required to delete the stream after the
         factory is done with it, unless it is the last pointer to the stream.

        2.) RandomFigureFactory:
         Creates random figures. The distribution of different figures is expected be even.
         The figures are created with random parameters, but the parameters are within
         the specified in Constants.hpp range(dblrng namespace).
*/
#pragma once

#include <memory>

#include "Figures.hpp"

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
    std::shared_ptr<std::istream> stream; // non-owning
public:
    StreamFigureFactory(std::shared_ptr<std::istream>& in);
    std::unique_ptr<Figure> create() const override;
};

class AbstractFigureFactory {
public:
    std::unique_ptr<FigureFactory> getFigureFactory(const std::string& FigureFactoryType, const std::string& filename) const;
    virtual ~AbstractFigureFactory() = default;
};