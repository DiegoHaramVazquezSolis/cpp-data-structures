//
// Created by Diego Vazquez on 22/06/26.
//

#ifndef CLION_LINKED_LIST_H
#define CLION_LINKED_LIST_H
#include <cstddef>
#include <stdexcept>

template <typename T>
struct Node {
    T value;
    Node* next = nullptr;
};

template <typename T>
class LinkedList {
Node<T>* head_;
Node<T>* tail_;
std::size_t size_;

public:
    LinkedList();
    ~LinkedList();                        // free every node

    void push_front(const T& value);      // O(1)
    void push_back(const T& value);       // O(1) with tail pointer
    void pop_front();                     // remove first node
    void pop_back();                      // remove last node (O(n) walk)

    T&       front();                     // first value
    const T&       front() const;
    T&       back();                      // last value
    const T&       back() const;

    T&       at(std::size_t i);           // walk i hops; throws std::out_of_range
    const T& at(std::size_t i) const;

    std::size_t size() const;
    bool        empty() const;
    void        clear();                  // free all nodes, size -> 0
};

template<typename T>
LinkedList<T>::LinkedList() {
    size_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
}

template<typename T>
void LinkedList<T>::push_front(const T &value) {
    if (size_ == 0) {
        head_ = new Node<T>;
        head_->value = value;
        head_->next = nullptr;
        tail_ = head_;
    } else {
        auto* newNode = new Node<T>;
        newNode->value = value;
        newNode->next = head_;
        head_ = newNode;
    }

    size_++;
}

template<typename T>
void LinkedList<T>::push_back(const T &value) {
    if (size_ == 0) {
        head_ = new Node<T>;
        head_->value = value;
        head_->next = nullptr;
        tail_ = head_;
    } else {
        auto* newNode = new Node<T>;
        newNode->value = value;
        newNode->next = nullptr;
        tail_->next = newNode;
        tail_ = newNode;
    }

    size_++;
}

template<typename T>
void LinkedList<T>::pop_front() {
    if (empty()) {
        return;
    }

    const Node<T>* toDelete = head_;
    head_ = head_->next;

    delete toDelete;
    size_--;

    if (size_ == 0) {
        head_ = nullptr;
        tail_ = nullptr;
    }
}

template<typename T>
void LinkedList<T>::pop_back() {
    if (empty()) {
        return;
    }

    Node<T>* pointer = head_;
    Node<T>* previous = pointer;
    while (pointer->next != nullptr) {
        previous = pointer;
        pointer = pointer->next;
    }

    previous->next = nullptr;
    tail_ = previous;
    delete pointer;
    size_--;

    if (size_ == 0) {
        head_ = nullptr;
        tail_ = nullptr;
    }
}

template<typename T>
T& LinkedList<T>::front() {
    return head_->value;
}

template<typename T>
const T& LinkedList<T>::front() const {
    return head_->value;
}

template<typename T>
T& LinkedList<T>::back() {
    return tail_->value;
}

template<typename T>
const T& LinkedList<T>::back() const {
    return tail_->value;
}

template<typename T>
T& LinkedList<T>::at(std::size_t i) {
    if (i >= size_) {
        throw std::out_of_range("LinkedList::at: is out of range!");
    }

    Node<T>* pointer = head_;
    for (unsigned int index = 0; index < i; index++) {
        pointer = pointer->next;
    }

    return pointer->value;
}

template<typename T>
const T& LinkedList<T>::at(std::size_t i) const {
    if (i >= size_) {
        throw std::out_of_range("LinkedList::at: is out of range!");
    }

    Node<T>* pointer = head_;
    for (unsigned int index = 0; index < i; index++) {
        pointer = pointer->next;
    }

    return pointer->value;
}

template<typename T>
std::size_t LinkedList<T>::size() const {
    return size_;
}

template<typename T>
bool LinkedList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
void LinkedList<T>::clear() {
    Node<T>* pointer = head_;
    while (pointer != nullptr) {
        const Node<T>* toDelete = pointer;
        pointer = pointer->next;

        delete toDelete;
    }

    head_ = nullptr;
    tail_ = nullptr;

    size_ = 0;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

#endif //CLION_LINKED_LIST_H
