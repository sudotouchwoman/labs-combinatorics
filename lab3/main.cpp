#include "transversal.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    std::ifstream in;
    Matrix mx;
    in.open("matrix.txt");

    if (not in.is_open()) return EXIT_FAILURE;
    
    mx.FillFromFile(in);
    in.close();
    mx.pretty_print(std::cout);

    Transversal tv(mx);
    tv.DoAlgorithmVerbose(std::cout);

    return EXIT_SUCCESS;
}
