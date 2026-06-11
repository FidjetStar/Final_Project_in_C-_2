#pragma once
#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <stdexcept>

class Validator {
public:
    static int getValidChoice(int min, int max) {
        int value;
        if (!(std::cin >> value)) {
            throw std::invalid_argument("Ошибка ввода: ожидалось целое число");
        }
        if (value < min || value > max) {
            throw std::out_of_range("Введите число от " + std::to_string(min) + " до " + std::to_string(max));
        }
        return value;
    }
    static int getValidNumber(const std::string& message = "Ошибка ввода: введите положительное число") {
        int value;
        if (!(std::cin >> value)) {
            throw std::invalid_argument(message);
        }
        if (value <= 0) {
            throw std::domain_error("Число должно быть больше 0");
        }
        return value;
    }
    static void isFileOpen(std::ifstream& file, const std::string& filename) {
        if (!file.is_open()) {
            throw std::runtime_error("Ошибка открытия файла: " + filename);
        }
    }
};
