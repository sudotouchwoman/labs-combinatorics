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

unsigned TLS(unsigned BinCom);
int ContainsCycle(unsigned BinCom);
