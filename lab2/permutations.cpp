#include <exception>
#include "permutations.hpp"

using namespace utils;

static void swap(size_t *a, size_t *b){
    if (a == nullptr || b == nullptr) return;
    if (a == b) return;
    size_t tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

PermutationTraverser::PermutationTraverser(const size_t _n) : n(_n){
    if (n == 0) return;
    init_arrays(n);
}

PermutationTraverser::~PermutationTraverser(){
    delete [] directions;
    delete [] permutation;
    delete [] reverse_permutation;
}

int PermutationTraverser::init_arrays(const size_t n){
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

const size_t PermutationTraverser::get_neighbour(const size_t j){
    size_t i = reverse_permutation[j] + directions[j];
    return permutation[i];
}

const size_t PermutationTraverser::get_current_m(){
    for (size_t i = n; i > 1; --i){
        if ( i > get_neighbour(i) ) return i;
    }
    return 1;
}

int PermutationTraverser::transpose(const size_t i, const size_t j){
    swap(&permutation[ reverse_permutation[j] ], &permutation[ reverse_permutation[i] ]);
    swap(&reverse_permutation[j], &reverse_permutation[i]);
    return EXIT_SUCCESS;
}

int PermutationTraverser::update_directions(const size_t m){

    auto change_direction = [](int & direction){
        direction *= CHANGE_SIGN;
    };

    for (size_t i = m + 1; i < n + 1; ++i){
        change_direction(directions[i]);
    }
    return EXIT_SUCCESS;
}

void PermutationTraverser::traverse(){

    print(std::cout, 1);
    for (size_t m = get_current_m(), i = 2; m != 1; m = get_current_m(), ++i){
        transpose(m, get_neighbour(m));
        print(std::cout, i);
        update_directions(m);
    }
    return;
}

void PermutationTraverser::print(std::ostream &out, const size_t n_iter){
    
    auto equal = [&]() {
        for (size_t i = 1; i < n + 1; ++i){
            if (permutation[i] != reverse_permutation[i]) return false;
        }
        return true;
    };

    auto write = [&](const size_t *arr){
        for (size_t i = 1; i < n + 1; ++i){
            out << arr[i];
        }
        out << " ";
    };

    out << n_iter << ") P: ";
    write(permutation);
    out << "R: ";
    write(reverse_permutation);
    if (equal()) { out << "Are equal!" << '\n'; } else { out << '\n'; }
}
