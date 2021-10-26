#include "permutations.hpp"

int main(int argc, char *argv[]){
    size_t n = 5;

    if (argc == 2){
        size_t _n = (size_t)atoi(argv[1]);
        if (_n > 0 && _n <= utils::D::MAX_ITEMS) n = _n;
    }
    
    auto Traverser = utils::PermutationTraverser(n);
    Traverser.traverse();    
    
    return EXIT_SUCCESS;
}