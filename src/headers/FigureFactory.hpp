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
    std::shared_ptr<std::istream> stream; // non-owning
public:
    StreamFigureFactory(std::shared_ptr<std::istream>& in);
    std::unique_ptr<Figure> create() const override;
};