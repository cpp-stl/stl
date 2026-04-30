#ifndef VECTOR_H
#define VECTOR_H

#include "stl/exceptions.h"
#include "types.h"
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <cstdint>

namespace stl {
    
    enum class pop_back_status : uint8_t
    {
        success,
        error
    }; 

    template <typename T>
    class vector {
        public:
            // constructors
            vector() noexcept : buffer_(nullptr), capacity_(0), size_(0) 
            {
            }
            
            vector(size_t n, const T& o): vector()
            {
                this->resize(n, o);
            }

            vector(const vector& other) : buffer_(nullptr), size_(other.size()), capacity_(other.capacity())
            {
                void* tmp = (T*) realloc(this->buffer_, other.size());
                if (!tmp) {
                    throw stl::bad_realloc();
                }
                tmp = std::memcpy(this->buffer_, other.buffer_, sizeof(T) * other.size());
                this->buffer_ = (T*) tmp;
            }

            vector(std::initializer_list<T> p)
            {
                this->resize(p.size());
                std::for_each(p.begin(), p.end(), [&](auto element){
                    this->push_back(element);
                });
                
            }

            vector& operator=(const vector& other)
            {
                if (this != &other) {
                    this->size_ = other.size();
                    this->reserve(other.capacity_);
                    void* tmp = std::memcpy(this->buffer_, other.buffer_, sizeof(T) * other.size());
                }

                return *this;
            }

            ~vector()
            {
                delete this->buffer_;
            }

            T& operator[](size_t index)
            {
                return this->buffer_[index];
            }

            T& at(size_t index) const
            {
                if (index < 0 || index >= this->size())
                {
                    throw stl::out_of_bounds();
                }
                return this->buffer_[index];
            }

            void push_back(const T& object)
            {
                if (this->size() == this->capacity())
                {
                    this->reserve(this->privGetNewCapacity());
                }
                this->buffer_[this->size_] = object;
                this->size_++;
            }

            [[nodiscard("BROOOOO")]] pop_back_status pop_back(T& object) noexcept
            {
                if (!this->empty())
                {
                    object = this->buffer_[this->size_-1];
                    this->size_--;
                    return pop_back_status::success;
                }
                else
                {
                    return pop_back_status::error;
                }
            }
            
            void insert()
            {
                
            }

            constexpr size_t size() const noexcept {
                return this->size_;
            }

            constexpr size_t capacity() const noexcept {
                return this->capacity_;
            }

            void resize(size_t count)
            {
                privResize(count, T());
            }
            
            void resize(size_t count, const T& defaultValue) {
                this->privResize(count, defaultValue);
            }

            void reserve(size_t newCap) {
                if (newCap > this->capacity())
                {
                    // allocates new space
                    void* tmp = std::realloc(this->buffer_, sizeof(T) * newCap);
                    if (!tmp) {
                        throw stl::bad_realloc();
                    }

                    this->buffer_ = (T*) tmp;
                    this->capacity_ = newCap;
                }
            }

            bool empty() const
            {
                return this->buffer_ == nullptr;
            }

        private:
            const size_t privGetNewCapacity() const noexcept {
                if (this->capacity() == 0)
                {
                    return 1;
                }
                else
                {
                    return this->capacity() << 1;
                }
            }
            
            void privResize(size_t count, const T& defaultVal) {
                // enough capacity?
                const size_t size = this->size();
                const size_t cap = this->capacity();

                if (count > cap) {
                    this->reserve(count);
                }
                
                if (count > size)
                {
                    // fill in the remaining space with default
                    for(int i = size; i < cap; i++)
                    {
                        this->buffer_[i] = defaultVal;
                    }
                }
                this->size_ = count;
            }
            
            T* buffer_;
            stl::size_t capacity_;
            stl::size_t size_;
    };
};

#endif