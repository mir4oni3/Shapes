#include "../headers/FigureListUI.hpp"

int ConsoleUI::enterCount() {
    int N;
    do {
        std::cout << "Please enter the number of figures you would like to create(0 < N <= 1 000 000): ";
        std::cin >> N;
        std::cout << std::endl << std::endl;
    } while (N <= 0 || N > 1'000'000);
    return N;
}

std::string ConsoleUI::enterChoice() {
    std::cout << "How would you like to create new figures?" << std::endl;
    std::cout << "1.) Random: figures are created using a random number generator." << std::endl;
    std::cout << "2.) STDIN: figures are read from STDIN." << std::endl;
    std::cout << "3.) File: figures are read from a file." << std::endl;
    std::cout << "4.) Exit: exit the program." << std::endl;

    std::string choice;
    do {
        std::cout << "Please enter your choice [random|stdin|file|exit]: ";
        std::cin >> choice;
    } while (choice != "random" && choice != "stdin" && choice != "file" && choice != "exit");
    std::cout << std::endl << std::endl;

    return choice;
}

std::string ConsoleUI::promptUser() {
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1.) List figures." << std::endl;
    std::cout << "2.) Delete a figure at index." << std::endl;
    std::cout << "3.) Duplicate a figure at index and put at the end of list." << std::endl;
    std::cout << "4.) Store to file." << std::endl;
    std::cout << "5.) Exit." << std::endl;

    std::string choice;
    do {
        std::cout << "Please enter your choice [list|del|dup|store|exit]: " << std::endl;
        std::cin >> choice;
    } while (choice != "list" && choice != "del" && choice != "dup" && choice != "store" && choice != "exit");
    return choice;
}

std::unique_ptr<FigureList> ConsoleUI::createList(const std::string& choice, const std::string& filename, int N) {
    AbstractFigureFactory factory;

    std::unique_ptr<FigureFactory> figureFactory;
    try {
        figureFactory = factory.getFigureFactory(choice, filename);
    } catch(std::invalid_argument& e) {
        std::cout << "Exception thrown! " << std::endl << e.what() << std::endl;
        std::cout << "Creating random figure factory instead..." << std::endl;
        std::cout << std::endl << std::endl;
        figureFactory = std::make_unique<RandomFigureFactory>();
    }

    std::unique_ptr<FigureList> list = std::make_unique<FigureList>();

    for (int i = 0; i < N; i++) {
        try {
            list->push(figureFactory->create());
        } catch(std::invalid_argument& e) {
            std::cout << "Exception thrown! " << std::endl << e.what() << std::endl;
            std::cout << "Couldn't add figure to list..." << std::endl;
            std::cout << std::endl << std::endl;
            break;
        }
    }

    return list;
}

std::string ConsoleUI::action(const std::string& choice, std::unique_ptr<FigureList>& list) {
    if (choice == "list") {
        list->print();
    }
    else if (choice == "del") {
        int index;
        std::cin >> index;
        try {
            list->removeAt(index);
        } catch(const std::out_of_range& e) {
            std::cout << "Exception thrown! " << std::endl << e.what() << std::endl;
            std::cout << "Figure cannot be deleted" << std::endl;
            std::cout << std::endl << std::endl;
        }
    }
    else if (choice == "dup") {
        int index;
        std::cin >> index;
        try {
            list->duplicateAt(index);
        } catch(const std::out_of_range& e) {
            std::cout << "Exception thrown! " << std::endl << e.what() << std::endl;
            std::cout << "Figure cannot be duplicated" << std::endl;
            std::cout << std::endl << std::endl;
        }
    }
    else if (choice == "store") {
        std::string filename;
        std::cout << "Please enter the filename: " << std::endl;
        std::cin >> filename;
        list->printToFile(filename);
    }
    return choice;
}

void ConsoleUI::startLoop(std::unique_ptr<FigureList>& list) {
    std::string choice;
     while(choice != "exit") {
        choice = promptUser();
        action(choice, list);
    }
}

void ConsoleUI::execute() {
    int count = enterCount();
    std::string choice = enterChoice();

    if (choice == "exit") {
        return;
    }
    if (choice == "stdin") {
        std::cout << "Please enter the figures in the following format: figureType [PARAMETER]..." << std::endl;
    }
    std::string filename;
    if (choice == "file") {
        std::cout << "Please enter the filename: ";
        std::cin >> filename;
    }

    std::unique_ptr<FigureList> list = createList(choice, filename, count);
    startLoop(list);
}