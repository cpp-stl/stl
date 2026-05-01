#ifndef ITERATOR_H
#define ITERATOR_H

namespace stl {
template <typename T>
class iterator {
   public:
    iterator() : begin_(nullptr), end_(nullptr) {}
    iterator(T* begin, T* end);
    iterator(const iterator &);
    iterator &operator=(const iterator &);
    ~iterator() {
        this->begin_ = nullptr;
        this->end_ = nullptr;
    };

    T* begin() const noexcept(true)
    {
        return this->begin_;
    }

    T* end() const noexcept(true) {
        return this->end_;
    };
    
    // auto& i = begin();
    // auto i = begin();
    // vector<int>::iterator
    // vector<int>::error
   private:
    const T *begin_;
    const T *end_;
};
};  // namespace stl

#endif