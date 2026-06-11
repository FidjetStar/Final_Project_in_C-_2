#include "h.h"
#include "validator.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <limits>


//========================================================================================================================

Linked_cyclic_list::~Linked_cyclic_list() { // деструктор
    if (!head) {
        return;
    }
    Node* current = head->getNext();
    while (current != head) {
        Node* temp = current;
        current = current->getNext();
        delete temp;
    }
    delete head;
    head = nullptr;
}

void Linked_cyclic_list::PushBack(int val) { // добавление элемента в конец списка
    Node* newNode = new Node(val);
    if (head == nullptr) {
        head = newNode;
        newNode->setNext(newNode); // узел указывает на себя, так как это единственный элемент
    }
    else {
        Node* tail = head;
        while (tail->getNext() != head) {
            tail = tail->getNext();
        }
        tail->setNext(newNode);
        newNode->setNext(head);
    }
}

Linked_cyclic_list::Linked_cyclic_list(const Linked_cyclic_list& other) : head(nullptr){ // конструктор копирования
    if (!other.head) {
        return;
    }
    Node* current = other.head;
    do {
        PushBack(current->getData());
        current = current->getNext();
    }
    while (current != other.head);
}

void Linked_cyclic_list::Remove(Node* oldNode) { // удаление узла из списка
    if (!head || !oldNode) {
        return;
    }
    // Случай 1: список из одного элемента
    if (head == oldNode && head->getNext() == head) {
        delete oldNode;
        head = nullptr;
        return;
    }
    Node* current = head;
    // Случай 2: удаляем голову (но в списке >1 элемента)
    if (head == oldNode) {
        // Находим последний элемент (который указывает на head)
        while (current->getNext() != head) {
            current = current->getNext();
        }
        // Последний элемент теперь указывает на новый head
        current->setNext(head->getNext());
        head = head->getNext();
        delete oldNode;
        return;
    }
    // Случай 3: удаляем не голову
    while (current->getNext() != oldNode) {
        current = current->getNext();
        if (current == head) {
            return; // узел не найден
        }
    }
    current->setNext(oldNode->getNext());
    delete oldNode;
}

void Linked_cyclic_list::Print() const { // вывод элементов списка
    if (head == nullptr) {
        std::cout << "Список пуст\n";
        return;
    }
    Node* current = head;
    std::cout << "Элементы циклического списка: ";
    do {
        std::cout << current->getData() << " ";
        current = current->getNext();
    } 
    while(current != head);
    std::cout << std::endl;
}

//========================================================================================================================

void inputFromKeyboard(int &n, int &m, int &k) { // ввод данных с клавиатуры с валидацией
    std::cout << "Введите N (кол-во тюков у каждого купца): ";
    while (true) {
        try {
            n = Validator::getValidNumber();
            break;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << "\nПопробуйте снова: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cout << "Введите M (номер стартовой позиции 1-31): ";
    while (true) {
        try {
            m = Validator::getValidChoice(1, 31);
            break;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << "\nПопробуйте снова: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cout << "Введите K (шаг > 0): ";
    while (true) {
        try {
            k = Validator::getValidNumber();
            break;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << "\nПопробуйте снова: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void inputFromRandom(int &n, int &m, int &k) { // генерация случайных данных
    std::cout << "Данные генерируются в диапазоне: N(1-100), M(1-31), K(1-10)\n";
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    n = 1 + std::rand() % 50; // N от 1 до 50
    m = 1 + std::rand() % 31; // M от 1 до 31
    k = 1 + std::rand() % 10; // K от 1 до 10
    std::cout << "Сгенерированные данные: N=" << n << ", M=" << m << ", K=" << k << "\n";
}

bool inputFromFile(int &n, int &m, int &k) {
    std::cout << "Введите имя файла: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::string filename;
    std::getline(std::cin, filename);
    std::ifstream file(filename);
    Validator::isFileOpen(file, filename);
    if (!(file >> n >> m >> k)) {
        throw std::runtime_error("Ошибка чтения данных из файла");
    }
    if (n <= 0 || k <= 0 || m < 1 || m > 31) {
        throw std::runtime_error("Некорректные значения: N>0, K>0, M от 1 до 31");
    }
    std::cout << "\nДанные успешно считаны из файла:\n";
    std::cout << "N = " << n << "\n";
    std::cout << "M = " << m << "\n";
    std::cout << "K = " << k << "\n\n";
    return true;
}

//========================================================================================================================
// помечаем выброшенный тюк в итоговом списке, устанавливая его значение в -1

void MarkThrown(Linked_cyclic_list& resultList, int number) {
    Node* cur = resultList.getHead();
    do {
        if (cur->getData() == number) {
            cur->setData(-1);
            return;
        }
        cur = cur->getNext();
    } 
    while (cur != resultList.getHead());
}

void IKM(int N, int M, int K){ // основная логика решения задачи ИКМ
    std::cout << "===== Решение задачи =====\n";
    int total = 2 * N;
    int startPos = ((M - 1) % total) + 1;  // номер стартовой позиции в списке
    Linked_cyclic_list workList; // список где удаляются элементы
    Linked_cyclic_list resultList; // список для отображения итоговых позиций
    for (int i = 1; i <= total; i++) {
        workList.PushBack(i);
        resultList.PushBack(i);
    }
    Node* current = workList.getHead();
    if (!current) {
        std::cout << "Ошибка создания списка.\n";
        return;
    }
    for (int i = 1; i < startPos; i++) { // переход к стартовой позиции
        current = current->getNext();
    }
    std::cout << "Стартовый тюк: " << current->getData() << "\n";
    int remain = total; // количество оставшихся тюков
    int stepCount = 1; // счетчик шагов для отладки
    while (remain > N) { // основной цикл удаления, пока не останется N тюков
        int thrownNumber = current->getData();
        std::cout << "\nШаг " << stepCount++ << "\n";
        std::cout << "Выбрасываем тюк: " << thrownNumber << "\n";
        MarkThrown(resultList, thrownNumber); // помечаем выброшенный тюк в итоговом списке
        Node* nextNode = current->getNext();
        workList.Remove(current);
        remain--;
        std::cout << "Осталось после удаления : " << remain << " элементов" << "\n";
        if (remain == 0)
            break;
        current = nextNode;
        int steps = K % remain;
        for (int step = 0; step < steps; step++) {
            std::cout << "-> перешли на: " << current->getData() << "\n";
            current = current->getNext();
        }
    }
    std::cout << "\n===== Итоговые позиции купца =====\n";
    Node* cur = resultList.getHead();
    if (cur) {
        do {
            if (cur->getData() != -1)
                std::cout << cur->getData() << " ";
            cur = cur->getNext();
        } 
        while (cur != resultList.getHead());
    }
    std::cout << "\n";
}
