#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace stl {
class exception {
   public:
    exception() noexcept(true) = default;
    exception(const exception &) noexcept(true) = default;
    exception &operator=(const exception &) noexcept(true) = default;
    ~exception() noexcept(true) = default;

    virtual const char *what() const noexcept(true) = 0;
};

class out_of_bounds : public exception {
   public:
    const char *what() const noexcept(true) override { return "out of bounds"; }
};

class bad_alloc : public exception {
   public:
    const char *what() const noexcept(true) override { return "bad allocation"; }
};

class null_pointer_exception: public exception {
    public:
     const char *what() const noexcept(true) override {return "attempted to dereference null ptr"; }
};

class assertion_exception : public exception {
    public:
     const char *what() const noexcept { return "assertion exception"; }
    };
};  // namespace stl

#endif
