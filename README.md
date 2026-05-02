# IMPLEMENTATION OF STL BY ALEKONG, LLC.

## Why?
> ### "If you wish to make an apple pie from scratch, you must first create the universe" - Carl
### We decided to rebuild some of the standard library from scratch to better understand C++. 

### Through our endeavours, we've made some of our own decisions for custom implementations.

## Implementation-specific behavior
- `vector.pop_back()` should indicate to its consumer which element has been removed, if any. It returns an enum `pop_back_status` with either `success` or `empty`, and it
- `vector.begin()` and `vector.end()` return `nullptr` if its size is 0.