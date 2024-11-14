/*
    name:
        FigureList

    description:
        This is a container for figures, whose main purpose is to show how the other
        classes work together. It can store, remove, duplicate, and print figures.
        This class is used for demonstrative purposes!
*/
#pragma once

#include <vector>

#include "Figures.hpp"
#include "FigureFactory.hpp"

class FigureList {
    std::vector<std::unique_ptr<Figure>> figures;
public:
    FigureList(int capacity);
    virtual ~FigureList();

    std::unique_ptr<Figure>& getAt(int i) const;
    void setAt(int i, const std::unique_ptr<Figure>& figure);
    void removeAt(int i);
    void pop();
    void insertAt(int i, const std::unique_ptr<Figure>& figure);
    void push(const std::unique_ptr<Figure>& figure);
    void duplicateAt(int i);

    void print() const;
    void printToFile(const std::string& filename) const;
    int getSize() const;
};