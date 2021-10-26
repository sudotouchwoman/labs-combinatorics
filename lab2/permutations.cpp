#include "permutations.hpp"

using namespace utils;

static void swap(size_t *a, size_t *b){
    // swap provided items, quite self-explanatory
    // just check whether they point to the same adress and pass if so
    if (a == nullptr || b == nullptr) return;
    if (a == b) return;
    size_t tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

PermutationEnumerator::PermutationEnumerator(const size_t _n) : n(_n){
    if (n == 0) {
        std::cerr << "Attempt to create traverser over empty set, abort\n";
        throw BAD_ITEMS;
    }
    init_arrays(n);
}

PermutationEnumerator::~PermutationEnumerator(){
    delete [] directions;
    delete [] permutation;
    delete [] reverse_permutation;
}

int PermutationEnumerator::init_arrays(const size_t n){
    /*
    inits arrays with accordance to the algorithm
    permutations: indices are values (except bounds, these are n + 1)
    directions: all -1 (left), once again except bounds and also 1 (these are 0, i.e. static)
    */
    directions = new int[n+2];
    permutation = new size_t[n+2];
    reverse_permutation = new size_t[n+2];

    for (size_t i = 0; i < n + 2; ++i){
        permutation[i] = reverse_permutation[i] = i;
        directions[i] = LEFT;
    }
    permutation[0] = reverse_permutation[0] = n + 1;
    directions[0] = directions[1] = directions[n+1] = NONE;
    return EXIT_SUCCESS;
}

const size_t PermutationEnumerator::get_neighbour(const size_t j){
    /*
    utilize the reverse permutation property:
    its value at specified index is index of this
    element in the original array (also vice versa, though not used)
    */
    size_t i = reverse_permutation[j] + directions[j];
    return permutation[i];
}

const size_t PermutationEnumerator::get_current_m(){
    // current m is the largest item which is greater than its 'signed' neighbour
    for (size_t i = n; i > 1; --i){
        if ( i > get_neighbour(i) ) return i;
    }
    return 1;
}

int PermutationEnumerator::transpose(const size_t i, const size_t j){
    // transposition = swap
    swap(&permutation[ reverse_permutation[j] ], &permutation[ reverse_permutation[i] ]);
    swap(&reverse_permutation[j], &reverse_permutation[i]);
    return EXIT_SUCCESS;
}

int PermutationEnumerator::update_directions(const size_t m){
    // important step is reversing directions of all items numerically greater then current m
    // e.g., if there are 7 items and current m is 5, directions of 6 and 7 should be updated
    auto change_direction = [](int & direction){
        direction *= CHANGE_SIGN;
    };

    for (size_t i = m + 1; i < n + 1; ++i)
        change_direction(directions[i]);

    return EXIT_SUCCESS;
}

void PermutationEnumerator::traverse(){
    // it merely does what its name says
    print(std::cout, 1);
    for (size_t m = get_current_m(), i = 2; m != 1; m = get_current_m(), ++i){
        transpose(m, get_neighbour(m));
        print(std::cout, i);
        update_directions(m);
    }
    return;
}

void PermutationEnumerator::print(std::ostream &out, const size_t n_iter){
    // pretty-print current state of permutations
    // the cringe here is my design where stream is provided to this method but not provided to `traverse()`
    // whatever this is not what matters
    
    auto equal = [&]() {
        for (size_t i = 1; i < n + 1; ++i){
            if (permutation[i] != reverse_permutation[i]) return false;
        }
        return true;
    };

    auto write = [&](const size_t *arr){
        for (size_t i = 1; i < n + 1; ++i)
            out << arr[i] << " ";
    };

    out << n_iter << ")\tP:  "; write(permutation);
    out << "\tR:  "; write(reverse_permutation);
    if (equal()) { out << "\tAre equal!" << '\n'; } else { out << '\n'; }
}
