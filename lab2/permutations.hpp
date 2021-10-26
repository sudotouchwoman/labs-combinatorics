#ifndef _PERMUTATIONS_HPP
#define _PERMUTATIONS_HPP
#include <iostream>

namespace utils{
    class PermutationEnumerator;
    enum D{
        LEFT = -1,
        NONE,
        RIGHT,
        CHANGE_SIGN = -1,
        DEFAULT_ITEMS = 5,
        MIN_ITEMS = 1,
        MAX_ITEMS = 10,
        BAD_ITEMS = -1
    };
};

class utils::PermutationEnumerator{
private:
    int *directions = nullptr;
    size_t *permutation = nullptr;
    size_t *reverse_permutation = nullptr;
    size_t n;

private:
    const size_t get_neighbour(const size_t j);
    const size_t get_current_m();
    int init_arrays(const size_t);
    int transpose(const size_t i, const size_t j);
    int update_directions(const size_t);

public:
    PermutationEnumerator() = delete;
    PermutationEnumerator(const size_t);
    ~PermutationEnumerator();
    void traverse();
    void print(std::ostream & out, const size_t iter);
};

#endif // _PERMUTATIONS_HPP
