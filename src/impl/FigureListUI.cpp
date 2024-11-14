#include "../headers/FigureListUI.hpp"

int ConsoleUI::enterCount() {
    int N;
    do {
        std::cout << "Please enter the number of figures you would like to create(0 < N <= 1 000 000): ";
        std::cin >> N;
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
    std::unique_ptr<FigureFactory> figureFactory = factory.getFigureFactory(choice, filename);

    std::unique_ptr<FigureList> list = std::make_unique<FigureList>(new FigureList(N));
    for (int i = 0; i < N; i++) {
        list->push(figureFactory->create());
    }

    return list;
}

void ConsoleUI::startLoop(std::unique_ptr<FigureList>& list) {
    std::string choice;
     while(true) {
        choice = promptUser();
        if (choice == "exit") {
            break;
        }
        else if (choice == "list") {
            list->print();
        }
        else if (choice == "del") {
            int index;
            std::cin >> index;
            list->removeAt(index);
        }
        else if (choice == "dup") {
            int index;
            std::cin >> index;
            list->duplicateAt(index);
        }
        else if (choice == "store") {
            std::string filename;
            std::cin >> filename;
            list->printToFile(filename);
        }
    }
}

void ConsoleUI::execute() {
    int count = enterCount();
    std::string choice = enterChoice();

    if (choice == "exit") {
        return;
    }
    std::string filename = "";
    if (choice == "file") {
        std::cout << "Please enter the filename: ";
        std::cin >> filename;
    }

    std::unique_ptr<FigureList> list = createList(choice, filename, count);
    startLoop(list);
}