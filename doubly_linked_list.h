//
// Created by Diego Vazquez on 22/06/26.
//

#ifndef CLION_DOUBLY_LINKED_LIST_H
#define CLION_DOUBLY_LINKED_LIST_H
#include <cstddef>
#include <stdexcept>

template <typename T>
struct Node {
    T value;
    Node* next = nullptr;
    Node* previous = nullptr;
};

template <typename T>
class DoublyLinkedList {
    Node<T>* head;
    Node<T>* tail;
    std::size_t size_;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void push_front(const T& value);   // O(1)
    void push_back(const T& value);    // O(1)
    void pop_front();                  // O(1)
    void pop_back();                   // O(1)

    T&       front();
    T&       back();

    T&       at(std::size_t i);        // throws std::out_of_range
    const T& at(std::size_t i) const;

    std::size_t size() const;
    bool        empty() const;
    void        clear();
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    size_ = 0;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
void DoublyLinkedList<T>::push_front(const T &value) {
    auto* node = new Node<T>;
    node->value = value;

    if (empty()) {
        head = node;
        tail = node;
    } else {
        head->previous = node;
        node->next = head;
        head = node;
    }

    size_++;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T &value) {
    auto* node = new Node<T>;
    node->value = value;

    if (empty()) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        node->previous = tail;
        tail = node;
    }

    size_++;
}

template<typename T>
void DoublyLinkedList<T>::pop_front() {
    if (empty()) {
        return;
    }

    const Node<T>* toDelete = head;
    if (head->next != nullptr) {
        head = head->next;
        head->previous = nullptr;
    }

    delete toDelete;
    size_--;

    if (empty()) {
        head = nullptr;
        tail = nullptr;
    }
}

template<typename T>
void DoublyLinkedList<T>::pop_back() {
    if (tail == nullptr) {
        return;
    }

    const Node<T>* toDelete = tail;
    if (tail->previous != nullptr) {
        tail = tail->previous;
        tail->next = nullptr;
    }

    delete toDelete;
    size_--;

    if (empty()) {
        head = nullptr;
        tail = nullptr;
    }
}

template<typename T>
T& DoublyLinkedList<T>::front() {
    return head->value;
}

template<typename T>
T& DoublyLinkedList<T>::back() {
    return tail->value;
}

template<typename T>
T& DoublyLinkedList<T>::at(std::size_t i) {
    if (i >= size()) {
        throw std::out_of_range("LinkedList::at: is out of range!");
    }

    Node<T>* point = head;
    for (std::size_t index = 0; index < i; index++) {
        point = point->next;
    }

    return point->value;
}

template<typename T>
const T& DoublyLinkedList<T>::at(std::size_t i) const {
    if (i >= size()) {
        throw std::out_of_range("LinkedList::at: is out of range!");
    }

    const Node<T>* point = head;
    for (std::size_t index = 0; index < i; index++) {
        point = point->next;
    }

    return point->value;
}

template<typename T>
std::size_t DoublyLinkedList<T>::size() const {
    return size_;
}

template<typename T>
bool DoublyLinkedList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
void DoublyLinkedList<T>::clear() {
    Node<T>* pointer = head;
    while (pointer != nullptr) {
        const Node<T>* nodeToDelete = pointer;
        pointer = pointer->next;

        delete nodeToDelete;
    }

    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

#endif //CLION_DOUBLY_LINKED_LIST_H