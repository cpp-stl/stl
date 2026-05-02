#ifndef ITERATOR_H
#define ITERATOR_H

namespace stl {
template <typename T>
class iterator {
   public:
    iterator() : ptr_(nullptr){}
    iterator(T* ptr): ptr_(ptr){}
    iterator(const iterator &rhs): ptr_(rhs.ptr_){}
    iterator &operator=(const iterator &rhs)
    {
        this->ptr_ = rhs.ptr_;
    }
    ~iterator() {
        this->ptr_ = nullptr;
    };

    bool operator==(iterator& rhs) noexcept(true)
    {
        return *(this->ptr_) == *(rhs.ptr_);
    }

    iterator operator++(int unused) noexcept(true)
    {
        iterator tmp = this->ptr_;
        this->ptr_ = this->ptr_ + 1;
        return tmp;
    }

    T operator*() noexcept(true)
    {
        return *(this->ptr_);
    }

   private:
    T *ptr_;
};
};  // namespace stl

#endif