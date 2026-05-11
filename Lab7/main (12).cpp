#include <iostream>
#include <memory>    // Для unique_ptr
#include <stdexcept> // Для обробки помилок

using namespace std;

// ПУНКТ 3: Окрема структура Node (Вузол)
template <typename T>
struct Node {
    T data;
    unique_ptr<Node<T>> next;

    Node(T val) : data(val), next(nullptr) {}
};

// ПУНКТ 1, 4, 5: Клас для роботи із однозв'язним списком
template <typename T>
class SinglyLinkedList {
private:
    unique_ptr<Node<T>> head;
    size_t count;

public:
    SinglyLinkedList() : head(nullptr), count(0) {}

    // f. Перевірка на порожнечу
    bool isEmpty() const {
        return head == nullptr;
    }

    // e. Перевірка розміру
    size_t size() const {
        return count;
    }

    // a. Додавання на початок списку
    void pushFront(T val) {
        // Замість make_unique використовуємо явне створення для сумісності з C++11
        unique_ptr<Node<T>> newNode(new Node<T>(val));
        
        newNode->next = move(head);
        head = move(newNode);
        count++;
    }

    // h. Виведення списку на екран (cout)
    void print() const {
        Node<T>* temp = head.get();
        while (temp) {
            cout << "[" << temp->data << "] -> ";
            temp = temp->next.get();
        }
        cout << "nullptr" << endl;
    }
};

int main() {
    try {
        SinglyLinkedList<int> list;
        list.pushFront(10);
        list.pushFront(20);

        cout << "Перший запуск списку (C++11 compatible):" << endl;
        list.print();
        cout << "Розмір: " << list.size() << endl;

    } catch (const exception& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
    return 0;
}