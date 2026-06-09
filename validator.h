#pragma once
#include <iostream>
#include <limits>
#include <string>
#include <fstream>

class Validator {
public:
    static int getValidChoice(int min, int max) {
        int choice;
        while (!(std::cin >> choice) || choice < min || choice > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Введите число от " << min << " до " << max << ": ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
    }
    static int getValidNumber(const std::string& message = "Неверный ввод! Введите положительное число: ") {
        int val;
        while (!(std::cin >> val && val > 0)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << message;
        }
        return val;
    }
    static bool isFileOpen(std::ifstream& file, const std::string& filename) {
        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла " << filename << "\n";
            return false;
        }
        return true;
    }
};
