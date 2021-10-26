#include "permutations.hpp"
using namespace utils;

int main(int argc, char *argv[]){
    size_t n = DEFAULT_ITEMS;

    if (argc == 2){
        const int _n = atoi(argv[1]);
        if (_n >= MIN_ITEMS && _n <= MAX_ITEMS) n = (size_t) _n;
        else {
            std::cerr << "Invalid argument value. Usage: single natural number in [1;10]\n";
            return EXIT_FAILURE;
        }
    }
    
    auto Traverser = utils::PermutationTraverser(n);
    Traverser.traverse();    
    
    return EXIT_SUCCESS;
}
