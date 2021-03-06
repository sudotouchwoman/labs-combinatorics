#include <stdio.h>
#include <stdlib.h>

#define TOTAL_EDGES 6
#define TREE_EDGES 3

void CountSpanningTrees();
unsigned Combinations(unsigned m, unsigned n);

void PrintCombination(unsigned BinCom, unsigned n_iter);
void PrintAsBinary(unsigned number, unsigned digits);

unsigned CountLeadingOnes(unsigned BinCom);
unsigned CountZeros(unsigned BinCom);

unsigned InitCombination();
unsigned TLS(unsigned BinCom);
unsigned ContainsCycle(unsigned BinCom);
unsigned MatchesMask(unsigned number, unsigned mask);
