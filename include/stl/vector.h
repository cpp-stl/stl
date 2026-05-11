#ifndef VECTOR_H
#define VECTOR_H

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <initializer_list>

#include "stl/exceptions.h"
#include "stl/iterator.h"
#include "stl/reverse_iterator.h"

#include "types.h"

namespace stl {

enum class pop_back_status : uint8_t { success, empty };

template <typename T>
class vector {
   public:
    using iterator = stl::iterator<T>;
    using reverse_iterator = stl::reverse_iterator<T>;

    // constructors
    vector() noexcept : buffer_(nullptr), capacity_(0), size_(0) {}
    vector(size_t capacity, const T &o = T()) noexcept(false) : vector() 
    {
        this->resize(capacity, o);
    }

    vector(const vector &other) noexcept(false) : vector() {
        this->resize(other.size());
        std::memcpy(this->buffer_, other.buffer_, sizeof(T) * other.size());
    }

    vector(std::initializer_list<T> p) noexcept(false) : vector() {
        size_t size = p.size();
        this->reserve(size);
        this->size_ = size;
        size_t start = 0;
        for (auto &i : p) {
            this->buffer_[start] = i;
            start++;
        }
    }

    vector &operator=(const vector &other) noexcept(false) {
        if (this != &other) {
            this->size_ = other.size();
            this->reserve(other.capacity_);
            void *tmp = std::memcpy(this->buffer_, other.buffer_, sizeof(T) * other.size());
        }
        return *this;
    }

    ~vector() noexcept { std::free(this->buffer_); }

    T &operator[](size_t index) noexcept { return this->buffer_[index]; }

    T &at(size_t index) const noexcept(false) {
        if (index < 0 || index >= this->size()) {
            throw stl::out_of_bounds();
        }
        return this->buffer_[index];
    }

    void push_back(const T &object) noexcept(false) {
        if (this->size() == this->capacity()) {
            this->reserve(this->privGetNewCapacity());
        }
        this->buffer_[this->size_] = object;
        this->size_++;
    }

    [[nodiscard]] pop_back_status pop_back(T &object) noexcept {
        if (this->empty()) {
            return pop_back_status::empty;
        }
        else {
            this->size_--;
            object = this->buffer_[this->size_];
            return pop_back_status::success;
        }
    }

    void shrink_to_fit() { privReallocateMem(this->size_); }

    void clear() { this->size_ = 0; }

    constexpr size_t size() const noexcept { return this->size_; }

    constexpr size_t capacity() const noexcept { return this->capacity_; }

    void resize(size_t capacity, const T &defaultValue = T()) noexcept(false) {
        this->privResize(capacity, defaultValue);
    }

    void reserve(size_t newCap) noexcept(false) {
        if (newCap > this->capacity()) {
            privReallocateMem(newCap);
        }
    }

    bool empty() const noexcept { return this->buffer_ == nullptr; }

    const T& front() const {
        if (this->empty()) {
            throw stl::out_of_bounds();
        }
        return this->at(0);
    }

    const T& back() const {
        if (this->empty()) {
            throw stl::out_of_bounds();
        }
        return this->at(this->size() - 1);
    }

    const T* data() const {
        if (this->empty()) {
            return nullptr;
        }
        return this->buffer_;
    }

    iterator begin() { return iterator(this->first()); }
    iterator end() { return iterator(this->last()); }
    reverse_iterator rbegin() { return reverse_iterator(this->last()); }
    reverse_iterator rend() { return reverse_iterator(this->first()); }


   private:
    T *first() {
        if (this->empty()) {
            return nullptr;
        }
        return this->buffer_;
    }

    T *last() {
        if (this->empty()) {
            return nullptr;
        }
        return this->first() + this->size();
    }

    const size_t privGetNewCapacity() const noexcept {
        if (this->capacity() == 0) {
            return 1;
        } else {
            return this->capacity() << 1;
        }
    }

    void privResize(size_t capacity, const T &defaultVal) noexcept(false) {
        const size_t size = this->size();

        if (capacity > this->capacity()) {
            privReallocateMem(capacity);
        }

        if (capacity > size) {
            for (size_t i = size; i < capacity; i++) {
                this->buffer_[i] = defaultVal;
            }
        }
        this->size_ = capacity;
    }

    void privReallocateMem(size_t newCap) noexcept(false) {
        size_t size = sizeof(T) * newCap;
        void *tmp = std::realloc(this->buffer_, size);
        if (!tmp) {
            throw stl::bad_alloc();
        }

        this->buffer_ = (T *)(tmp);
        this->capacity_ = newCap;
    }

    T *buffer_;
    stl::size_t capacity_;
    stl::size_t size_;
};
};  // namespace stl

#endif
