#ifndef ITERATOR_H
#define ITERATOR_H

#include <cstddef>
#include <istream>
#include <ostream>
#include <string>
#include "stl/exceptions.h"
namespace stl {
template <typename T>
class iterator {
   public:
    iterator() : ptr_(nullptr) {}
    iterator(T *ptr) : ptr_(ptr) {}
    iterator(const iterator &rhs) : ptr_(rhs.ptr_) {}
    iterator &operator=(const iterator &rhs) { 
        if(this != &rhs)
        {
            this->ptr_ = rhs.ptr_; 
        }
        return *this;
    }
    ~iterator() { this->ptr_ = nullptr; };

    [[nodiscard("LOOK AT IT!")]] constexpr T* base() const noexcept(true) {
        return this->ptr_;
    }
    
    bool operator==(iterator &rhs) noexcept(true) { return this->ptr_ == rhs.ptr_; }
    bool operator==(std::nullptr_t) noexcept(true) { return this->ptr_ == nullptr; }
    
    iterator operator++(int unused) noexcept(true) {
        iterator tmp = this->ptr_;
        this->ptr_ = this->ptr_ + 1;
        return tmp;
    }

    T operator*() noexcept(false) {
        if(!this->ptr_)
        {
            throw stl::null_pointer_exception();
        }
        return *(this->ptr_);
    }

    std::ostream& operator<<(std::iostream &stream) {
        return stream << std::to_string(*this->ptr_);
    }

   private:
    T *ptr_;
};
};  // namespace stl

#endif