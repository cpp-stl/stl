#ifndef VECTOR_H
#define VECTOR_H

#include "stl/exceptions.h"
#include "types.h"
#include <cstdlib>

namespace stl {
    template <typename T>
    class vector {
        public:
            // constructors
            vector(): buffer_(nullptr), capacity_(0), size_(0)
            {
            }
            vector(size_t, T);
            vector(const vector&);
            vector& operator=(const vector&)
            {
                
            }
            ~vector() = default;

            T operator[](int index)
            {
                return this->buffer_[index];
            }

            T at(int index) const
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

            void pop_back();
            
            void insert();

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