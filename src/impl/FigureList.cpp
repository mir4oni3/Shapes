#include <fstream>

#include "../headers/FigureList.hpp"

const std::shared_ptr<Figure>& FigureList::getAt(int i) const {
    if (i >= figures.size()) {
        throw std::out_of_range("Index out of range");
    }
    return figures[i];
}

void FigureList::setAt(int i, const std::shared_ptr<Figure>& figure) {
    if (i >= figures.size()) {
        throw std::out_of_range("Index out of range");
    }
    if (!figure) {
        throw std::invalid_argument("Cannot insert nullptr");
    }
    figures[i] = figure;
}

void FigureList::removeAt(int i) {
    if (i >= figures.size()) {
        throw std::out_of_range("Index out of range");
    }
    figures.erase(figures.begin() + i);
}

void FigureList::pop() {
    if (figures.size() == 0) {
        throw std::out_of_range("List is empty");
    }
    figures.pop_back();
}

void FigureList::insertAt(int i, const std::shared_ptr<Figure>& figure) {
    if (i > figures.size()) {
        throw std::out_of_range("Index out of range");
    }
    if (!figure) {
        throw std::invalid_argument("Cannot insert nullptr");
    }
    figures.insert(figures.begin() + i, figure);
}

void FigureList::push(const std::shared_ptr<Figure>& figure) {
    if (!figure) {
        throw std::invalid_argument("Cannot insert nullptr");
    }
    figures.push_back(figure);
}

void FigureList::duplicateAt(int i) {
    if (i >= figures.size()) {
        throw std::out_of_range("Index out of range");
    }
    figures.push_back(figures[i]);
}

void FigureList::print() const {
    for (int i = 0; i < figures.size(); i++) {
        figures[i]->print();
    }
    std::cout << std::endl << std::endl;
}

void FigureList::printToFile(const std::string& filename) const {
    std::ofstream fileStream(filename, std::ios::out | std::ios::app);
    try {
        for (int i = 0; i < figures.size(); i++) {
            figures[i]->printToFile(fileStream);
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "Exception thrown! " << std::endl << e.what() << std::endl;
        std::cout << "Figures cannot be printed to file" << std::endl;
        std::cout << std::endl << std::endl;
    }
}

int FigureList::getSize() const {
    return figures.size();
}