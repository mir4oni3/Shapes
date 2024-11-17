#include <fstream>
#include <sstream>
#include <cfloat>

#include "../headers/Figures.hpp"
#include "../headers/Constants.hpp"

namespace {
    void checkTriangleParams(double a, double b, double c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            throw std::invalid_argument("Triangle sides must be positive");
        }
        if (DBL_MAX - a < b || DBL_MAX - a < c || DBL_MAX - b < c) {
            throw std::invalid_argument("Triangle sides are too big");
        }
        if (DBL_MAX - a - b < c || DBL_MAX - a - c < b || DBL_MAX - b - c < a) {
            throw std::invalid_argument("Triangle sides are too big");
        }
        if (a + b <= c || a + c <= b || b + c <= a) {
            throw std::invalid_argument("Triangle sides must satisfy triangle inequality");
        }
    }

    void checkCircleParams(double r) {
        if (r <= 0) {
            throw std::invalid_argument("Circle radius must be positive");
        }
        if (r >= DBL_MAX / (2 * mathPI)) {
            throw std::invalid_argument("Circle radius is too big");
        }
    }

    void checkRectangleParams(double a, double b) {
        if (a <= 0 || b <= 0) {
            throw std::invalid_argument("Rectangle sides must be positive");
        }
        if (DBL_MAX / 2 < a || DBL_MAX / 2 < b) {
            throw std::invalid_argument("Rectangle sides are too big");
        }
        if (DBL_MAX - 2*a < 2*b) {
            throw std::invalid_argument("Rectangle sides are too big");
        }
    }
}

void Figure::output(std::ostream& oStream) const {
    if (!oStream) {
        throw std::invalid_argument("Stream is not in a good state");
    }
    oStream << toString() << std::endl;
}

void Figure::print() const {
    try {
        output(std::cout);
    } catch (const std::invalid_argument& e) {
        std::cout << "Exception thrown! " << std::endl << e.what() << std::endl;
        std::cout << "Figure cannot be printed" << std::endl;
        std::cout << std::endl << std::endl;
    }
}

void Figure::printToFile(std::ofstream& stream) const {
    if (!stream.is_open()) {
        throw std::invalid_argument("File is not open");
    }

    try {
        output(stream);
    } catch (const std::invalid_argument& e) {
        std::cout << "Exception thrown! " << std::endl << e.what() << std::endl;
        std::cout << "Figure cannot be printed" << std::endl;
        std::cout << std::endl << std::endl;
    }
}

Triangle::Triangle(double a, double b, double c) : a(a), b(b), c(c) {
    try {
        checkTriangleParams(a, b, c);
    } catch (const std::invalid_argument& e) {
        std::cout << "Exception thrown! " << std::endl << e.what() << std::endl;
        std::cout << "Setting default values..." << std::endl;
        std::cout << std::endl << std::endl;
        this->a = 1;
        this->b = 1;
        this->c = 1;
    }
}

std::unique_ptr<Figure> Triangle::clone() const {
    return std::make_unique<Triangle>(*this);
}

double Triangle::getPerimeter() const {
    return a + b + c;
}

std::string Triangle::toString() const {
    std::stringstream strStream;
    strStream << "triangle " << a << " " << b << " " << c;
    return strStream.str();
}

Circle::Circle(double r) : r(r) {
   try {
        checkCircleParams(r);
    } catch (const std::invalid_argument& e) {
        std::cout << "Exception thrown! " << std::endl << e.what() << std::endl;
        std::cout << "Setting default values..." << std::endl;
        std::cout << std::endl << std::endl;
        this->r = 1;
    }
}

std::unique_ptr<Figure> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}

double Circle::getPerimeter() const {
    return 2 * mathPI * r;
}

std::string Circle::toString() const {
    std::stringstream strStream;
    strStream << "circle " << r;
    return strStream.str();
}

Rectangle::Rectangle(double a, double b) : a(a), b(b) {
    try {
        checkRectangleParams(a, b);
    } catch (const std::invalid_argument& e) {
        std::cout << "Exception thrown! " << std::endl << e.what() << std::endl;
        std::cout << "Setting default values..." << std::endl;
        std::cout << std::endl << std::endl;
        this->a = 1;
        this->b = 1;
    }
}

std::unique_ptr<Figure> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}

double Rectangle::getPerimeter() const {
    return 2 * (a + b);
}

std::string Rectangle::toString() const {
    std::stringstream strStream;
    strStream << "rectangle " << a << " " << b;
    return strStream.str();
}