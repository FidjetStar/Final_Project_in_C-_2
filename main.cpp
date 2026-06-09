#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
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
        std::cout << " - Всего тюков: 2*N (N тюков у каждого купца)\n";
        std::cout << " - Тюки расставлены по кругу\n";
        std::cout << " - Выбрасывается каждый K-й тюк, начиная с позиции M-число месяца(1-31)\n";
        std::cout << " - Всего выбрасывают N тюков (половину)\n";
        std::cout << " - Задача: найти N \"выживших\" позиций, куда купец должен поставить свой груз\n";
        std::cout << "========================================\n";
        std::cout << "1. Ввод данных с клавиатуры\n";
        std::cout << "2. Случайные данные\n";
        std::cout << "3. Ввод из файла\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        choice = Validator::getValidChoice(0, 3);
        switch(choice) {
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
                n = m = k = 0;  // защита от мусорных значений
                inputFromFile(n, m, k);
                if (n > 0 && k > 0)
                    IKM(n, m, k);
                break;
            }
            case 0: {
                break;
            }
        }
    } 
    while(choice != 0);
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
        mainChoice = Validator::getValidChoice(0, 1);
        switch (mainChoice) {
            case 1: {
                IKM_menu();
                break;
            }
            case 0: {
                std::cout << "\nПрограмма завершена\n";
                break;
            }
        }
    }
    while (mainChoice != 0);
}
