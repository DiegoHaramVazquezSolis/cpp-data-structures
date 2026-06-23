//
// Created by Diego Vazquez on 21/06/26.
//

#ifndef CLION_DYNAMIC_ARRAY_H
#define CLION_DYNAMIC_ARRAY_H
#include <cstddef>
#include <stdexcept>

#include <iterator>
#include <__ranges/data.h>

template <typename T>
class DynamicArray {
public:
    DynamicArray();                       // starts empty
    ~DynamicArray();                      // frees the heap block

    void   push_back(const T& value);     // append; grow if full

    void   pop_back();                    // remove last element (size--)

    T&        operator[](std::size_t i);        // no bounds check
    const T&  operator[](std::size_t i) const;

    T&        at(std::size_t i);                 // bounds-checked: throws std::out_of_range
    const T&  at(std::size_t i) const;

    T&        front();                    // first element
    T&        back();                     // last element

    std::size_t size() const;             // # elements stored
    std::size_t capacity() const;         // # elements the block can hold
    bool        empty() const;            // size == 0

    void clear();                         // size -> 0 (capacity may stay)

private:
    T*          data_;      // <-- THE CONTENT lives here
    std::size_t size_;      // how many slots are currently in use
    std::size_t capacity_;  // how many slots data_ can hold
};

template <typename T>
DynamicArray<T>::DynamicArray() {
    capacity_ = 1;
    size_ = 0;
    data_ = new T[capacity_];
}

template <typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (capacity_ == size_) {
        const size_t new_capacity = capacity_ * 2;

        // Create array with double the capacity
        T* temp = new T[new_capacity];

        // Reassign values to the new array
        for (std::size_t i = 0; i < size(); i++) {
            *(temp + i) = data_[i];
        }

        // Free memory from old array
        delete[] data_;

        // Point data to new array
        data_ = temp;
        // Update capacity
        capacity_ = new_capacity;
    }

    // Store value
    *(data_ + size()) = value;

    // Update size by 1
    size_++;
}

template <typename T>
void DynamicArray<T>::pop_back() {
    if (size_ > 0) {
        size_--;
    }
}

template <typename T>
T& DynamicArray<T>::operator[](std::size_t i) {
    return *(data_ + i);
}

template <typename T>
const T& DynamicArray<T>::operator[](std::size_t i) const {
    return *(data_ + i);
}

template <typename T>
T& DynamicArray<T>::at(std::size_t i) {
    if (i >= size_) {
        throw std::out_of_range("DynamicArray::at: is out of range!");
    }

    return *(data_ + i);
}

template <typename T>
const T& DynamicArray<T>::at(std::size_t i) const {
    if (i >= size_) {
        throw std::out_of_range("DynamicArray::at: is out of range!");
    }

    return *(data_ + i);
}

template <typename T>
T& DynamicArray<T>::front() {
    return *data_;
}

template <typename T>
T& DynamicArray<T>::back() {
    return *(data_ + size() - 1);
}

template <typename T>
std::size_t DynamicArray<T>::size() const {
    return size_;
}

template <typename T>
std::size_t DynamicArray<T>::capacity() const {
    return capacity_;
}

template<typename T>
bool DynamicArray<T>::empty() const {
    return size_ == 0;
}

template<typename T>
void DynamicArray<T>::clear() {
    size_ = 0;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data_;
}

#endif //CLION_DYNAMIC_ARRAY_H
