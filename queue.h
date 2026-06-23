#ifndef CLION_QUEUE_H
#define CLION_QUEUE_H
#include <cstddef>
#include "linked_list.h"

template <typename T>
class Queue {
    LinkedList<T> data_;

    public:
        Queue();
        ~Queue();

        void push(const T& value);   // enqueue at the back
        void pop();                  // dequeue from the front

        T&       front();            // oldest element (next to be removed)
        const T& front() const;
        T&       back();             // newest element (just pushed)
        const T& back() const;

        std::size_t size() const;
        bool        empty() const;
        void        clear();
};

template<typename T>
Queue<T>::Queue() = default;

template<typename T>
void Queue<T>::push(const T &value) {
    data_.push_back(value);
}

template<typename T>
void Queue<T>::pop() {
    data_.pop_front();
}

template<typename T>
T& Queue<T>::front() {
    return data_.front();
}

template<typename T>
const T& Queue<T>::front() const {
    return data_.front();
}

template<typename T>
T& Queue<T>::back() {
    return data_.back();
}

template<typename T>
const T& Queue<T>::back() const {
    return data_.back();
}

template<typename T>
std::size_t Queue<T>::size() const {
    return data_.size();
}

template<typename T>
bool Queue<T>::empty() const {
    return data_.empty();
}

template<typename T>
void Queue<T>::clear() {
    data_.clear();
}

template<typename T>
Queue<T>::~Queue() {}

#endif //CLION_QUEUE_H