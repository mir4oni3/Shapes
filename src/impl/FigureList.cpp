#include <fstream>

#include "../headers/FigureList.hpp"

FigureList::FigureList(unsigned int capacity) : figures(capacity) {}

const std::shared_ptr<Figure>& FigureList::getAt(int i) const {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    return figures[i];
}

void FigureList::setAt(int i, const std::shared_ptr<Figure>& figure) {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    if (!figure) {
        throw std::invalid_argument("Cannot insert nullptr");
    }
    figures[i] = figure;
}

void FigureList::removeAt(int i) {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    figures.erase(figures.begin() + i);
    size--;
}

void FigureList::pop() {
    if (size == 0) {
        throw std::out_of_range("List is empty");
    }
    figures.pop_back();
    size--;
}

void FigureList::insertAt(int i, const std::shared_ptr<Figure>& figure) {
    if (i > size) {
        throw std::out_of_range("Index out of range");
    }
    if (!figure) {
        throw std::invalid_argument("Cannot insert nullptr");
    }
    figures.insert(figures.begin() + i, figure);
    size++;
}

void FigureList::push(const std::shared_ptr<Figure>& figure) {
    if (!figure) {
        throw std::invalid_argument("Cannot insert nullptr");
    }
    figures.push_back(figure);
    size++;
}

void FigureList::duplicateAt(int i) {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    figures.push_back(figures[i]);
    size++;
}

void FigureList::print() const {
    for (int i = 0; i < size; i++) {
        figures[i]->print();
    }
}

void FigureList::printToFile(const std::string& filename) const {
    std::ofstream fileStream(filename);
    try {
        for (int i = 0; i < size; i++) {
            figures[i]->printToFile(fileStream);
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "Exception thrown! " << std::endl << e.what() << std::endl;
        std::cout << "Figures cannot be printed to file" << std::endl;
    }
}

int FigureList::getSize() const {
    return size;
}