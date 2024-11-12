/*
    name:
     Figures
     
    description:
     The Figure interface is declared here. All its concrete implementations
     need to be declared here.
*/

#pragma once

#include <iostream>

#include "StringConvertibleInterface.hpp"

class Figure : public StringConvertible {
public:
    virtual std::unique_ptr<Figure> clone() const = 0;
    virtual std::string toString() const override = 0;
    virtual double getPerimeter() const = 0;
    virtual ~Figure() = default;
};

class Triangle : public Figure {
    double a, b, c;
public:
    Triangle(double a, double b, double c); //check if perimeter is overflow
    std::unique_ptr<Figure> clone() const override;
    double getPerimeter() const override;
    std::string toString() const override;
};

class Circle : public Figure {
    double r;
public:
    Circle(double r); //check if perimeter is overflow
    std::unique_ptr<Figure> clone() const override;
    double getPerimeter() const override;
    std::string toString() const override;
};

class Rectangle : public Figure {
    double a, b;
public:
    Rectangle(double a, double b); //check if perimeter is overflow
    std::unique_ptr<Figure> clone() const override;
    double getPerimeter() const override;
    std::string toString() const override;
};