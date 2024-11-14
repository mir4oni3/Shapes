/*
    name:
     Figures
     
    description:
     The Figure interface is declared here. All its concrete implementations
     need to be declared here.

    Exception safety levels:
     The output() and printToFile() functions from the Figure class have no exception safety.
     All other functions have basic exception safety.

*/

#pragma once

#include <iostream>

#include "StringConvertibleInterface.hpp"

class Figure : public StringConvertible {
    void output(std::ostream& oStream) const;
public:
    virtual void print() const;
    virtual void printToFile(std::ofstream& fileStream) const;
    virtual std::unique_ptr<Figure> clone() const = 0;
    virtual double getPerimeter() const = 0;
    virtual std::string toString() const override = 0;
    virtual ~Figure() = default;
};

class Triangle : public Figure {
    double a, b, c;
public:
    Triangle(double a, double b, double c); 
    std::unique_ptr<Figure> clone() const override;
    double getPerimeter() const override;
    std::string toString() const override;
};

class Circle : public Figure {
    double r;
public:
    Circle(double r); 
    std::unique_ptr<Figure> clone() const override;
    double getPerimeter() const override;
    std::string toString() const override;
};

class Rectangle : public Figure {
    double a, b;
public:
    Rectangle(double a, double b);
    std::unique_ptr<Figure> clone() const override;
    double getPerimeter() const override;
    std::string toString() const override;
};