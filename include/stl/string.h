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
    basic_string() noexcept : sBuff_{0}
    {}

    basic_string(size_t capacity, const T &o = T()) noexcept
    { 
        if (capacity >= min_cap)
        {
            this->resize(capacity, o);
        }
        else
        {
            this->create_short();
        }
    }

    basic_string(const basic_string &other) noexcept
    { 
        if (other.is_long())
        {
        }
        else
        {
            this->create_short(other.sBuff_.size_);
            std::memcpy(this->sBuff_.stackbuff_, other.sBuff_.stackbuff_, other.sBuff_.size_);
        }

    }

    basic_string& operator= (const basic_string& other) noexcept
    {
        if (this != &other)
        {
            if (this->is_long && other.is_long())
            {

            } 
            if (this->is_long)
            {

            }
            else if (other.is_long())
            {

            }
            else 
            {
                this->create_short(other.sBuff_.size_);
                std::memcpy(this->sBuff_.stackbuff_, other.sBuff_.stackbuff_, other.sBuff_.size_);
            }
        }
        return *this;
    }


    ~basic_string() noexcept
    {
        if (is_long()) 
        {
            std::free(this->lBuff_.buffer_);
        }
    }

    // EXCLUDES NULL TERMINATOR LIKE STL::STRLEN
    constexpr size_t size() const noexcept
    { 
#ifdef LITTLE_ENDIAN
        if (is_long())
        {
            // My weird trick to remove mask temporarily. Maybe a better approach out there.
            this->sBuff_.size_ = 0x0;
            size_t size = this->lBuff_.size_;
            this->sBuff_.size_ = 0x80;

            return size;
        }
        else
        {
            return this-sBuff_.size_;
        }
#else

#endif
    }

    // EXCLUDES NULL TERMINATOR LIKE STL::STRLEN
    constexpr size_t length() const noexcept { return this->size(); }

    constexpr size_t capacity() const noexcept { 
        if (is_long())
        {
            return this->lBuff_.capacity_;
        } 
        else
        {
            return (size_t) this->min_cap;
        }
    }

    void resize(size_t capacity, const T &defaultValue = T()) noexcept(false) {
        this->privResize(capacity, defaultValue);
    }

    void reserve(size_t newCap) noexcept(false) {
        if (newCap > this->capacity()) {
            privReallocateMem(newCap);
        }
    }

    constexpr bool empty() const noexcept {
        return this->size() == 0;
    }

   private:

    void create_short(size_t size = 0) noexcept 
    {
        this->sBuff_.size_ = size;
        this->stackbuff_[0] = '\0';
    }

    const size_t privGetNewCapacity() const noexcept
    {
        if (this->capacity() == 0) {
            return 1;
        } else {
            return this->capacity() << 1;
        }
    }

    void privResize(size_t capacity, const T &defaultVal) 
    {
        this->sBuff_.size_ = 0x80;
        const size_t size = this->size();
        
        if (capacity > this->capacity()) 
        {
            privReallocateMem(capacity);
        }
        
        if (capacity > size) 
        {
            for (size_t i = size; i < capacity; i++) 
            {
                this->buffer_[i] = defaultVal;
            }
        }
        this->size_ = capacity;
    }

    void privReallocateMem(size_t newCap) 
    {
        size_t size = sizeof(T) * newCap;
        void *tmp = std::realloc(this->buffer_, size);
        if (!tmp) 
        {
            throw stl::bad_alloc();
        }
        this->buffer_ = (T *)(tmp);
        this->capacity_ = newCap;
    }  

    constexpr bool is_long() noexcept
    { 
        return this->sBuff_.size_ & 0x80;
    }

     // Following the libc++ implementation for Small String Optimization
    struct sLong_{
        size_t size_;
        size_t capacity_;
        T *buffer_;
    };

    enum : uint8_t { min_cap = (sizeof(sLong_) - 1) / sizeof(T) > 2 ? 
                               (sizeof(sLong_) - 1) / sizeof(T) : 2 };

    struct sShort_
    {
        union 
        {
            // MSB is the flag for short or small string so we only get (2^7)-1 or 127 bits for size.
            unsigned char size_;
            // padding forces size_; to be the first byte.
            T padding_;
        };
        T stackbuff_[min_cap];
    };

    union{
        sShort_ sBuff_;
        sLong_ lBuff_;
    };

};

using string = basic_string<char>;


inline stl::size_t strlen(const char *str) noexcept 
{
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
