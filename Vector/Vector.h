// Fuck pcf
#pragma once
#include <exception>
#include <algorithm>

class IntVector {
public:
    explicit IntVector();
    explicit IntVector(int size);
    explicit IntVector(const std::initializer_list<int>& list);
    explicit IntVector(const IntVector& vector);
    explicit IntVector(IntVector&& vector);
    ~IntVector();

    void Swap(IntVector& vector) noexcept;
    const int Size() const;
    const int Capacity() const;
    void PushBack(int value);
    void PopBack();
    void Clear();
    void Reserve(int size);

    friend std::ostream& operator<<(std::ostream& out, const IntVector& vec);
    IntVector& operator=(const IntVector& vec);
    int& operator[] (const int index);
    const int operator[] (const int index) const;

private:
    int* elem_ = new int[1];
    int size_ = 0;
    int capacity_ = 1;
};

IntVector::IntVector() = default;

IntVector::IntVector(int size) {
    capacity_ = size;
    elem_ = new int[capacity_];
    size_ = size;
    for (int it = 0; it < size; ++it) {
        elem_[it] = 0;
    }
}

IntVector::IntVector(const std::initializer_list<int>& list) {
    capacity_ = list.size();
    elem_ = new int[capacity_];
    size_ = list.size();
    int jt = 0;
    for (auto it = list.begin(); it < list.end(); ++it, ++jt) {
        elem_[jt] = *it;
    }
}

IntVector::IntVector(const IntVector& vector) {
    this->size_ = vector.size_;
    this->capacity_ = vector.capacity_;
    this->elem_ = new int[capacity_];
    for (int it = 0; it < vector.size_; ++it) {
        elem_[it] = vector.elem_[it];
    }
}

IntVector::IntVector(IntVector&& vector) {
    this->size_ = vector.size_;
    this->capacity_ = vector.capacity_;
    this->elem_ = vector.elem_;
    vector = IntVector();
}

IntVector::~IntVector() {
    if (elem_ != NULL)
        delete[] elem_;
}

void IntVector::Swap(IntVector& vector) noexcept {
    IntVector copy(*this);
    this->size_ = vector.size_;
    this->capacity_ = vector.capacity_;
    this->elem_ = new int[vector.capacity_];
    for (int it = 0; it < vector.size_; ++it) {
        this->elem_[it] = vector.elem_[it];
    }
    vector.capacity_ = copy.capacity_;
    vector.size_ = copy.size_;
    vector.elem_ = copy.elem_;
}

const int IntVector::Size() const {
    return this->size_;
}

const int IntVector::Capacity() const {
    return this->capacity_;
}

void IntVector::PushBack(int value) {
    if (size_ == capacity_)
        Reserve(capacity_ * 2);
    elem_[size_] = value;
    size_++;
}

void IntVector::PopBack() {
    size_--;
}

void IntVector::Clear() {
    size_ = 0;
}

void IntVector::Reserve(int size) {
    if (capacity_ >= size)
        return;
    int* old = elem_;
    capacity_ = size;
    elem_ = new int[capacity_];
    for (int it = 0; it < size_; ++it) {
        elem_[it] = old[it];
    }
    delete[] old;
}

std::ostream& operator<<(std::ostream& out, const IntVector& vec) {
    for (int it = 0; it < vec.size_; ++it) {
        out << vec.elem_[it] << " ";
    }
    out << "\n";
    return out;
}

IntVector& IntVector::operator=(const IntVector& other) {
    IntVector copy(other);
    this->Swap(copy);
    return *this;
}

int& IntVector::operator[] (const int index) {
    if (index >= size_ || index < 0)
        throw std::runtime_error("Index out of bounds");
    return this->elem_[index];
}

const int IntVector::operator[] (const int index) const {
    if (index >= size_ || index < 0)
        throw std::runtime_error("Index out of bounds");
    return this->elem_[index];
}
