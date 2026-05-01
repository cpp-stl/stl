#ifndef VECTOR_H
#define VECTOR_H

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <initializer_list>

#include "stl/exceptions.h"
#include "stl/iterator.h"
#include "types.h"

namespace stl {

enum class pop_back_status : uint8_t { success, error };

template <typename T>
class vector {
   public:
    using iterator = stl::iterator<T>;
    iterator itr;
    // constructors
    vector() noexcept(true) : buffer_(nullptr), capacity_(0), size_(0) {}
    vector(size_t n, const T &o = T()) noexcept(false) : vector() { this->resize(n, o); }

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

    ~vector() noexcept(true) { std::free(this->buffer_); }

    T &operator[](size_t index) noexcept(true) { return this->buffer_[index]; }

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

    [[nodiscard("BROOOO")]] pop_back_status pop_back(T &object) noexcept(true) {
        if (!this->empty()) {
            object = this->buffer_[this->size_ - 1];
            this->size_--;
            return pop_back_status::success;
        } else {
            return pop_back_status::error;
        }
    }

    void shrink_to_fit() { privReallocateMem(this->size_); }

    void clear() { this->size_ = 0; }

    constexpr size_t size() const noexcept(true) { return this->size_; }

    constexpr size_t capacity() const noexcept(true) { return this->capacity_; }

    void resize(size_t count, const T &defaultValue = T()) noexcept(false) {
        this->privResize(count, defaultValue);
    }

    void reserve(size_t newCap) noexcept(false) {
        if (newCap > this->capacity()) {
            privReallocateMem(newCap);
        }
    }

    bool empty() const noexcept(true) { return this->buffer_ == nullptr; }

    iterator begin() const { return itr ; }
    iterator end() const { return itr; }


   private:
    const size_t privGetNewCapacity() const noexcept {
        if (this->capacity() == 0) {
            return 1;
        } else {
            return this->capacity() << 1;
        }
    }

    void privResize(size_t count, const T &defaultVal) {
        const size_t size = this->size();

        if (count > this->capacity()) {
            privReallocateMem(count);
        }

        if (count > size) {
            for (size_t i = size; i < count; i++) {
                this->buffer_[i] = defaultVal;
            }
        }
        this->size_ = count;
    }

    void privReallocateMem(size_t newCap) {
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
