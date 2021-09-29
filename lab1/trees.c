#include "trees.h"

void CountSpanningTrees(){
    /*
    Main function iterates over all combinations and passes to console acyclic ones
    
    On each iteration, new binary combination (representing tree nodes in the graph) is produced
    via TLS (stands for Transposiotion with left shift)
    This algorithm iterates over set of all combinations for (m,n), where m is total number of digits, n is number of non-zero digits
    */
    unsigned BinaryCombination = InitCombination(); // initial binary (000111), 3 out of 6

    for (unsigned i = 0; i < Combinations(TREE_EDGES, TOTAL_EDGES); ++i){
        if (!ContainsCycle(BinaryCombination)) PrintCombination(BinaryCombination, i+1);
        BinaryCombination = TLS(BinaryCombination);
    }
    return;
}

unsigned Combinations(unsigned m, unsigned n){
    /*
    Recursively compute number of combinations for given m and n
    This algorithm makes use of identity for combinations to compute latter only by using addition

    Identity itself can be worded as follows:
        C(m,n) = C(m,n-1) + C(m-1,n-1)
    */
    if ((m == 0) || (n == 0) || (m == n)) return 1;
    if (m > n) return 0;
    if ( m == 1 ) return n;

    return Combinations(m, n - 1) + Combinations(m - 1, n - 1);
}

void PrintCombination(unsigned BinCom, unsigned n_iter){
    /*
    Pretty print given binary sequence (with leading zeros, if needed)
    also write no. of iteration
    */
    fprintf(stdout, "%2d ", n_iter);
    PrintAsBinary(BinCom, TOTAL_EDGES - 1);
    fprintf(stdout, "\n");
}

void PrintAsBinary(unsigned number, unsigned digits){
    /*
    Recursively print binary representation of a given number (add leading zeros if needed)
    */
        if ( number >> 1 || digits) PrintAsBinary( number >> 1, --digits);
    putc( (number & 1) ? '1' : '0', stdout );
}

unsigned CountLeadingOnes(unsigned BinCom){
    /*
    Count leading ones of a given binary combination
    Perform bitwise AND (&) and increment counter while got true

    e.g.
        (11000101) -> has 2 leading ones in a row
    */
    unsigned i = 1 << (TOTAL_EDGES - 1);
    unsigned ones = 0;
    for ( ; i > 0 && (BinCom & i); i >>= 1){
        ++ones;
    }
    return ones;
}

unsigned CountZeros(unsigned BinCom){
    /*
    Count length of sequence of zeros which follows leading ones (needed to shift those ones later)
    see CountLeadingOnes above

    e.g.
        (11000101) -> has 3 zeros in a row following 2 leading ones
    */
    unsigned i = 1 << ( TOTAL_EDGES - CountLeadingOnes(BinCom) - 1);
    unsigned zeros = 0;
    for ( ; i > 0 && (~BinCom & i); i >>= 1) {
        ++zeros;
    }
    return zeros;
}

unsigned InitCombination(){
    unsigned combination = 0;
    for (unsigned i = 0; i < TREE_EDGES; ++i)
        combination |= (1 << i);
    return combination;
}

unsigned TLS(unsigned BinCom){
    /*
    Return the next binary combination for a given one

    The formula is as follows:
        B' = B + (2^(n-E) - 2^n) + (2^(n-N+1) - 2^(n-N-E+1)) + 2^(n-N-E-1)

    The first bracket removes leading ones, the second one adds them in the right place (does shift)
    the last term performs transposition
    */
    unsigned E = CountLeadingOnes(BinCom);
    unsigned N = CountZeros(BinCom);
    unsigned n = TOTAL_EDGES;

    unsigned NewBinCom = BinCom + (1 << (n - E)) - (1 << n) + (1 << (n - N + 1)) - (1 << (n - N - E + 1)) + (1 << (n - N - E - 1));
    return NewBinCom;
}

unsigned ContainsCycle(unsigned BinCom){
    /*
    Check if given binary combination contains cycle
    (In my problem the cycle represents cycle in a graph)
    */
    return ( MatchesMask(BinCom, 19) || MatchesMask(BinCom, 41) || MatchesMask(BinCom, 22) || MatchesMask(BinCom, 44) );
}

unsigned MatchesMask(unsigned number, unsigned mask){
    return (number & mask) == mask;
}
