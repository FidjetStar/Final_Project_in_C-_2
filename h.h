#pragma once
#include <iostream>

class Node {
    private:
        int data;
        Node* next;
    public:
        Node() : data(0), next(nullptr) {}
        Node(int value) : data(value), next(nullptr) {}
        ~Node() = default;
        int getData() const { return data; }
        Node* getNext() const { return next; }
        void setData(int value) { data = value; }
        void setNext(Node* nextNode) { next = nextNode; }
};

class Linked_cyclic_list {
    private:
        Node* head;
    public:
        Linked_cyclic_list() : head(nullptr) {}
        ~Linked_cyclic_list();
        Linked_cyclic_list(const Linked_cyclic_list& other);
        Node* getHead() const { return head; }
        void PushBack(int value);
        void Print() const;
        void Remove(Node* oldNode);
};  

void inputFromKeyboard(int &n, int &m, int &k);
void inputFromRandom(int &n, int &m, int &k);
bool inputFromFile(int &n, int &m, int &k);

void IKM(int n, int m, int k);
void MarkThrown(Linked_cyclic_list& resultList, int number);
