#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H
#include <cstddef>
#include <istream>
#include <ostream>
#include <string>
#include "stl/exceptions.h"
namespace stl {
template <typename T>
class reverse_iterator {
   public:
    reverse_iterator() : ptr_(nullptr) {}
    reverse_iterator(T *ptr) : ptr_(ptr) {}
    reverse_iterator(const reverse_iterator &rhs) : ptr_(rhs.ptr_) {}
    reverse_iterator &operator=(const reverse_iterator &rhs) { 
        if(this != &rhs)
        {
            this->ptr_ = rhs.ptr_; 
        }
        return *this;
    }
    ~reverse_iterator() { this->ptr_ = nullptr; };

    [[nodiscard("LOOK AT IT!")]] constexpr T* base() const noexcept(true) {
        return this->ptr_;
    }
    
    bool operator==(reverse_iterator &rhs) noexcept(true) { return this->ptr_ == rhs.ptr_; }
    bool operator==(std::nullptr_t) noexcept(true) { return this->ptr_ == nullptr; }
    
    reverse_iterator operator++(int unused) noexcept(true) {
        reverse_iterator tmp = this->ptr_;
        this->ptr_ = this->ptr_ - 1;
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