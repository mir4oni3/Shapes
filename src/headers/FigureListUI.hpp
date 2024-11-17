/*
    name:
        FigureListUI

    description:
        The main purpose of this class is to implement a console UI
        for the FigureList class. The FigureList class is a container, whose
        purpose is to show how the other classes work together.
        This class is used for demonstrative purposes!
*/
#pragma once

#include <iostream>
#include <vector>

#include "FigureList.hpp"

class ConsoleUI {
    static int enterCount();
    static std::string enterChoice();
    static std::string promptUser();
    static std::unique_ptr<FigureList> createList(const std::string& choice, const std::string& filename, int N);
    static std::string action(const std::string& choice, std::unique_ptr<FigureList>& list);
    static void startLoop(std::unique_ptr<FigureList>& list);
public:
    static void execute();
};