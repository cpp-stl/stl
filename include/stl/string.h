#ifndef STRING_H
#define STRING_H
#include "types.h"
#include <cstring>

#include "stl/exceptions.h"
#include "stl/iterator.h"
#include "stl/reverse_iterator.h"

namespace stl 
{
template <typename T>
class basic_string{
   public:
    basic_string() : buffer_(nullptr), size_(0), capacity_(sizeof(size_t))    
    {}

    basic_string(const basic_string &other) : basic_string()
    {
        if (other.buffer_)
        {
            this->resize(other.size());
        }
    }

    basic_string& operator= (const basic_string& other)
    {
        if (this != &other)
        {
            this->size_ = other.size();
            if (other.buffer_)
            {
                this->reserve(other.capacity_);
                void *tmp = std::memcpy(this->buffer_, other.buffer_, sizeof(T) * other.size());
            } 
            else
            {
                void *tmp = std::memcpy(this->stackbuff_, other.stackbuff_, sizeof(T) * other.size());
            }

        }
        return *this;
    }


    ~basic_string() noexcept(true) 
    {
        if (this->buffer_) 
        {
            std::free(this->buffer_);
        }
    }

    constexpr size_t size() const noexcept(true) { return this->size_; }

    constexpr size_t length() const noexcept(true) { return this->size(); }

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

   private:
    T *first() noexcept(true) {
        if (this->empty()) {
            return nullptr;
        }
        return this->buffer_;
    }

    T *last() noexcept(true) {
        if (this->empty()) {
            return nullptr;
        }
        return this->first() + this->size();
    }

    const size_t privGetNewCapacity() const noexcept(true) {
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

    // For Small String Optimization
    union{
        struct{
            T *buffer_;
            size_t size_;
        };
        T stackbuff_[sizeof(size_t) * sizeof(T)];
    };

    stl::size_t capacity_;
};

using string = basic_string<char>;


inline stl::size_t strlen(const char *str) noexcept {
    stl::size_t count = 0;
    char i = str[count];
    while (i != '\0') {
        count++;
        i = str[count];
    }
    return count;
}
};  // namespace stl

#endif
