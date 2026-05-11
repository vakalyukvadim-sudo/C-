#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

// ПУНКТ 3: Вузол
template <typename T>
struct Node {
    T data;
    unique_ptr<Node<T>> next;
    Node<T>* prev; // Для двозв'язного списку

    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

// ПУНКТ 1, 4, 5: Однозв'язний список
template <typename T>
class SinglyLinkedList {
protected:
    unique_ptr<Node<T>> head;
    size_t count;

public:
    SinglyLinkedList() : head(nullptr), count(0) {}

    bool isEmpty() const { return head == nullptr; }
    size_t size() const { return count; }

    // a. Додавання на початок
    void pushFront(T val) {
        unique_ptr<Node<T>> newNode(new Node<T>(val));
        newNode->next = move(head);
        head = move(newNode);
        count++;
    }

    // a. Додавання в кінець
    void pushBack(T val) {
        if (isEmpty()) { pushFront(val); return; }
        Node<T>* temp = head.get();
        while (temp->next) temp = temp->next.get();
        temp->next = unique_ptr<Node<T>>(new Node<T>(val));
        count++;
    }

    // b. Вилучення першого
    void popFront() {
        if (isEmpty()) throw runtime_error("Список порожній!");
        head = move(head->next);
        count--;
    }

    // c. Доступ за індексом (оператор [])
    T& operator[](size_t index) {
        if (index >= count) throw out_of_range("Index error");
        Node<T>* temp = head.get();
        for (size_t i = 0; i < index; ++i) temp = temp->next.get();
        return temp->data;
    }

    // g. Пошук елемента
    int find(T val) {
        Node<T>* temp = head.get();
        for (size_t i = 0; i < count; ++i) {
            if (temp->data == val) return i;
            temp = temp->next.get();
        }
        return -1;
    }

    // d. Видалення за індексом
    void removeAt(size_t index) {
        if (index >= count) throw out_of_range("Index error");
        if (index == 0) { popFront(); }
        else {
            Node<T>* temp = head.get();
            for (size_t i = 0; i < index - 1; ++i) temp = temp->next.get();
            temp->next = move(temp->next->next);
            count--;
        }
    }

    // 6.h Виведення через оператор <<
    friend ostream& operator<<(ostream& os, const SinglyLinkedList<T>& list) {
        Node<T>* temp = list.head.get();
        while (temp) {
            os << "[" << temp->data << "] -> ";
            temp = temp->next.get();
        }
        os << "null";
        return os;
    }
};

// ПУНКТ 2: Двозв'язний список
template <typename T>
class DoublyLinkedList : public SinglyLinkedList<T> {
public:
    void pushBack(T val) {
        unique_ptr<Node<T>> newNode(new Node<T>(val));
        Node<T>* newNodePtr = newNode.get();
        if (this->isEmpty()) {
            this->head = move(newNode);
        } else {
            Node<T>* temp = this->head.get();
            while (temp->next) temp = temp->next.get();
            newNodePtr->prev = temp;
            temp->next = move(newNode);
        }
        this->count++;
    }

    // Для двозв'язного списку краще виводити стрілочки в обидва боки
    friend ostream& operator<<(ostream& os, const DoublyLinkedList<T>& list) {
        Node<T>* temp = list.head.get();
        while (temp) {
            os << "[" << temp->data << "] <-> ";
            temp = temp->next.get();
        }
        os << "null";
        return os;
    }
};

int main() {
    try {
        cout << "=== ТЕСТ ОДНОЗВ'ЯЗНОГО СПИСКУ ===" << endl;
        SinglyLinkedList<int> sList;

        sList.pushBack(10);
        sList.pushBack(20);
        sList.pushFront(5);
        cout << "Після додавання (5, 10, 20): " << sList << endl;

        cout << "Розмір списку: " << sList.size() << " | Порожній? " << (sList.isEmpty() ? "Так" : "Ні") << endl;
        cout << "Елемент за індексом [1]: " << sList[1] << endl;

        int pos = sList.find(20);
        cout << "Число 20 знайдено на позиції: " << pos << endl;

        sList.removeAt(1); 
        cout << "Після видалення індексу [1]: " << sList << endl;

        sList.popFront();
        cout << "Після popFront: " << sList << endl;

        cout << "\n=== ТЕСТ ДВОЗВ'ЯЗНОГО СПИСКУ (на рядках) ===" << endl;
        DoublyLinkedList<string> dList;
        dList.pushBack("C++");
        dList.pushBack("Java");
        dList.pushBack("Python");
        cout << "Двозв'язний список: " << dList << endl;

        cout << "\n=== ТЕСТ ПОМИЛКИ ===" << endl;
        cout << "Спробуємо дістати індекс 99..." << endl;
        cout << sList[99]; 

    } catch (const exception& e) {
        cerr << "ПЕРЕХОПЛЕНО ПОМИЛКУ: " << e.what() << endl;
    }

    return 0;
}