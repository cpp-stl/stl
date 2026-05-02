// Class made for testing stl containers
#ifndef DOG_H
#define DOG_H
#include <cstring>
#include "stl/types.h"
#include "stl/vector.h"
class Dog
{
    public:
        Dog() noexcept(true): name_(), age_(7), barks_(true)
        {
            this->junk_ = new float[5];
        };
        
        Dog(const Dog &rhs) noexcept(true): name_(rhs.name_), age_(rhs.age_), barks_(rhs.barks_)
        {
        this->junk_ = new float[5];
        stl::size_t junkSize = sizeof(float) * 5;
#if WINDOWS
            // ik it's a const and frankly I don't care.
            strcpy_s(padding_, 3,  rhs.padding_);
            memcpy_s(this->junk_, junkSize, rhs.junk_, junkSize);
#else
            strcpy(padding_, rhs.padding_);
            memcpy(this->junk_, rhs.junk_, junkSize);
#endif
            this->junk_ = new float[5];
        }
        Dog &operator=(const Dog &rhs) noexcept(true)
        {
            if (this != &rhs)
            {
                delete this->junk_;
                this->junk_ = new float[5];
                stl::size_t junkSize = sizeof(float) * 5;
#if WINDOWS
                // ik it's a const and frankly I don't care.
                strcpy_s(padding_, 3,  rhs.padding_);
                memcpy_s(this->junk_, junkSize, rhs.junk_, junkSize);
#else
                strcpy(padding_, rhs.padding_);
                memcpy(this->junk_, rhs.junk_, junkSize);
#endif
                this->junk_ = new float[5];
            }
            return *this;
        }
        ~Dog()
        {
            delete[] this->junk_;
        }

        stl::vector<unsigned char> name_;
        float* junk_;
        int age_;
        bool barks_;
        char padding_[3];
};
#endif