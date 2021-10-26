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
/*
    utils namespace contains enum for codes used later in code
    and the very enumerator class
    latter wraps 3 arrays and implements the transposition algorithm

    the attributes are quite self-explanatory:
    + directions: array of encoded directions of corresponding elements,
        -1 stands for left, 1 for right, 0 is assigned to 0 and fake bounding elements
    + permutation: array containing the current permutation. size is n + 2 (n plus two fake items)
    + reverse permutation: array containing the current reverse permutation. same size with others,
        indices of this array correspond to values of the previous one while values correspond to
        indices of ordinary permutations array and vice versa
    + n: the number of items (natural number)

    I explicitly delete the default init constructor
    in order to prohibit user creating enumerator on empty set
    the constructor will also throw exception if the n given is 0

    traverse() method is the interface of enumerator, 
    it iterates over permutations and prints current one

    comments on other methods are in the source file
*/

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
    void print(std::ostream & out, const size_t iter);

public:
    PermutationEnumerator() = delete;
    PermutationEnumerator(const size_t);
    ~PermutationEnumerator();
    void traverse();
};

#endif // _PERMUTATIONS_HPP
