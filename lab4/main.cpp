#include <sstream>

#include "gindenburg.hpp"

int main(int argc, char* argv[]) {

    if (argc != 3 and argc != 2) {
        std::cerr << "Usage: 2 natural numbers, N and M\n";
        return EXIT_FAILURE;
    }
    
    size_t N = 0, M = 1;
    
    if (argc == 3) {
        std::istringstream ss(argv[1]);
        if (not (ss >> N)) {
            std::cerr << "Argument N provided is invalid, abort.\n";
            return EXIT_FAILURE;
        }

        std::istringstream(argv[2]).swap(ss);
        if (not (ss >> M)) {
            std::cerr << "Argument M provided is invalid, abort.\n";
            return EXIT_FAILURE;
        }
    }
    if (argc == 2) {
        std::istringstream ss(argv[1]);
        if (not (ss >> N)) {
            std::cerr << "Argument N provided is invalid, abort.\n";
            return EXIT_FAILURE;
        }
    }

    Partition p(N, M);

    do {
        std::cerr << p << '\n';
    } while (p.next());

    return EXIT_SUCCESS;
}