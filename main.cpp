#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>

#include "h.h"
#include "validator.h"

#ifdef _WIN64
#include <windows.h>
#endif


void IKM_menu() {
    int choice;
    int n, m, k;
    do {
        std::cout << "\n========================================\n";
        std::cout << "   ЗАДАЧА «ХИТРЫЙ КУПЕЦ»\n";
        std::cout << "========================================\n";
        std::cout << "Правила:\n";
        std::cout << " - Всего тюков: 2*N (N у каждого купца)\n";
        std::cout << " - Тюки расположены по кругу\n";
        std::cout << " - Начало с позиции M (день месяца)\n";
        std::cout << " - Выбрасывается каждый K+1-й тюк\n";
        std::cout << " - Процесс идёт, пока не останется N тюков\n";
        std::cout << "========================================\n";
        std::cout << "1. Ввод данных с клавиатуры\n";
        std::cout << "2. Случайные данные\n";
        std::cout << "3. Ввод из файла\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        try {
            choice = Validator::getValidChoice(0, 3);
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка ввода: " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        try {
            switch (choice) {
                case 1: {
                    inputFromKeyboard(n, m, k);
                    IKM(n, m, k);
                    break;
                }
                case 2: {
                    inputFromRandom(n, m, k);
                    IKM(n, m, k);
                    break;
                }
                case 3: {
                    try {
                        inputFromFile(n, m, k);
                        IKM(n, m, k);
                    }
                    catch (const std::exception& e) {
                        std::cerr << "Ошибка файла: " << e.what() << "\n";
                    }
                    break;
                }
                case 0:
                    break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка выполнения: " << e.what() << "\n";
        }

    } 
    while (choice != 0);
}


int main() {
    #ifdef _WIN64
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    #endif
    int mainChoice;
    do {
        std::cout << "\n========== ГЛАВНОЕ МЕНЮ ==========\n";
        std::cout << "1. Задача ИКМ\n";
        std::cout << "0. Выход\n";
        std::cout << "==================================\n";
        std::cout << "Выберите пункт: ";
        try {
            mainChoice = Validator::getValidChoice(0, 1);
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка ввода: " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        switch (mainChoice) {
            case 1:
                IKM_menu();
                break;
            case 0:
                std::cout << "\nПрограмма завершена\n";
                break;
        }
    } 
    while (mainChoice != 0);
    return 0;
}
