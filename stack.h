#ifndef CLION_STACK_H
#define CLION_STACK_H
#include <cstddef>
#include "linked_list.h"

template <typename T>
class Stack {
    LinkedList<T> data_;

    public:
        Stack();
        ~Stack();

        void push(const T& value);   // add on top
        void pop();                  // remove the top element

        T&       top();              // the most recently pushed element
        const T& top() const;

        std::size_t size() const;
        bool        empty() const;
        void        clear();
};

template<typename T>
Stack<T>::Stack() = default;

template<typename T>
void Stack<T>::push(const T &value) {
    // Use front because all related operations are O(1)
    data_.push_front(value);
}

template<typename T>
void Stack<T>::pop() {
    // Use front because all related operations are O(1)
    data_.pop_front();
}

template<typename T>
T& Stack<T>::top() {
    // Use front because all related operations are O(1)
    return data_.front();
}

template<typename T>
const T& Stack<T>::top() const {
    // Use front because all related operations are O(1)
    return data_.front();
}

template<typename T>
std::size_t Stack<T>::size() const {
    return data_.size();
}

template<typename T>
bool Stack<T>::empty() const {
    return data_.empty();
}

template<typename T>
void Stack<T>::clear() {
    data_.clear();
}

template<typename T>
Stack<T>::~Stack() {}

#endif //CLION_STACK_H