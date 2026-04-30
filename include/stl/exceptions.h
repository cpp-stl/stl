#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace stl
{
    class exception
    {
        public:
            exception() noexcept = default;
            exception(const exception&) noexcept = default;
            exception& operator= (const exception&) noexcept = default;
            ~exception() noexcept = default;

            virtual const char* what() const noexcept = 0;
    };

    class out_of_bounds : public exception
    {
        public:
            out_of_bounds() noexcept = default;
            out_of_bounds(const out_of_bounds&) noexcept = default;
            out_of_bounds& operator= (const out_of_bounds&) noexcept = default;
            ~out_of_bounds() noexcept = default;
            
            const char* what() const noexcept override {
                return "XD out of bounds!";
            }

    };


    class bad_realloc : public exception
    {
        public:
            bad_realloc() noexcept = default;
            bad_realloc(const bad_realloc&) noexcept = default;
            bad_realloc& operator= (const bad_realloc&) noexcept = default;
            ~bad_realloc() noexcept = default;

            const char* what() const noexcept override {
                return "dawg what are you doing 😭";
            }
    };

}; // namespace

#endif