#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
struct Node {
    T data;
    unique_ptr<Node<T>> next;
    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class SinglyLinkedList {
private:
    unique_ptr<Node<T>> head;
    size_t count;

public:
    SinglyLinkedList() : head(nullptr), count(0) {}

    bool isEmpty() const { return head == nullptr; }
    size_t size() const { return count; }

    void pushFront(T val) {
        unique_ptr<Node<T>> newNode(new Node<T>(val));
        newNode->next = move(head);
        head = move(newNode);
        count++;
    }

    // --- НОВІ МЕТОДИ ДЛЯ ДРУГОГО КОМІТУ ---

    // 6.a Додавання в кінець
    void pushBack(T val) {
        if (isEmpty()) {
            pushFront(val);
            return;
        }
        Node<T>* temp = head.get();
        while (temp->next) {
            temp = temp->next.get();
        }
        temp->next = unique_ptr<Node<T>>(new Node<T>(val));
        count++;
    }

    // 6.b Вилучення першого
    void popFront() {
        if (isEmpty()) throw runtime_error("Список порожній!");
        head = move(head->next);
        count--;
    }

    // 6.b Вилучення останнього
    void popBack() {
        if (isEmpty()) throw runtime_error("Список порожній!");
        if (count == 1) {
            head.reset();
        } else {
            Node<T>* temp = head.get();
            while (temp->next->next) {
                temp = temp->next.get();
            }
            temp->next.reset();
        }
        count--;
    }

    // 6.c Доступ за індексом
    T& operator[](size_t index) {
        if (index >= count) throw out_of_range("Індекс поза межами списку!");
        Node<T>* temp = head.get();
        for (size_t i = 0; i < index; ++i) {
            temp = temp->next.get();
        }
        return temp->data;
    }

    // 6.g Пошук елемента
    int find(T val) {
        Node<T>* temp = head.get();
        for (size_t i = 0; i < count; ++i) {
            if (temp->data == val) return i;
            temp = temp->next.get();
        }
        return -1;
    }

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
        
        cout << "Додаємо 10, 20 в кінець, 5 на початок:" << endl;
        list.pushBack(10);
        list.pushBack(20);
        list.pushFront(5);
        list.print(); // Очікуємо: [5] -> [10] -> [20]

        cout << "Елемент за індексом 1: " << list[1] << endl;
        cout << "Індекс числа 20: " << list.find(20) << endl;

        cout << "Видаляємо перший та останній:" << endl;
        list.popFront();
        list.popBack();
        list.print();

    } catch (const exception& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
    return 0;
}