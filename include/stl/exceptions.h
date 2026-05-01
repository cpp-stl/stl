#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace stl {
class exception {
   public:
    exception() noexcept = default;
    exception(const exception &) noexcept = default;
    exception &operator=(const exception &) noexcept = default;
    ~exception() noexcept = default;

    virtual const char *what() const noexcept = 0;
};

class out_of_bounds : public exception {
   public:
    const char *what() const noexcept override { return "out of bounds"; }
};

class bad_alloc : public exception {
   public:
    const char *what() const noexcept override { return "bad allocation"; }
};

};  // namespace stl

#endif
