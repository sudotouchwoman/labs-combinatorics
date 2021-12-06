#include "gindenburg.hpp"

#include <algorithm>
#include <numeric>

Partition::Partition(const size_t N, const size_t M) :
    N(N), M(M) {
        terms.reserve(N - M + 1);
        terms.push_back(N);
        }

// predicate to check sequence end
// (the generation stops on the item of
// shape [1, 1, ..., 1, M] as then
// the greatest value will not exceed M - 1)
bool Partition::end() const {
    return terms.size() == (N - M + 1);
}

// rearrangement should be performed
// when there are no terms greater or equal to M
// considering that the rightmost term
// is always the greatest, the checking only
// takes constant time
bool Partition::must_rearrange() const {
    return *terms.crbegin() < M;
}

// expanding means splittiing values in
// a such way that the rightmost one will
// become N - m (m represents the current partition length)
// and all preceding terms are ones
void Partition::expand() {
    const auto last_term = *terms.crbegin();
    std::fill(terms.begin(), terms.end(), 1lu);
    terms.push_back(N - terms.size());
}

// yield the next partition
// I tried to create interface usable in a cycle,
// in the way it is done it main.cpp
bool Partition::next() {
    if (end()) return false;

    do {

        // the Gindenburg's algorithm itself
        // is quite straightforward
        // first, try to locate the rightmost term
        // which differs with the last term for more than 2
        const auto last_term = *terms.crbegin();
        const auto pivot = std::find_if(
            terms.rbegin(),
            terms.rend(),
            [last_term](const size_t x) {
                return last_term - x >= 2lu;
            }
        );

        // if no such term present,
        // current partition should be expanded
        // see expand() method
        if (pivot == terms.rend()) {
            expand();
            return true;
        }

        // if such pivot was found,
        // obtain its value and increment it
        const size_t pivot_term = ++(*pivot);

        // then, fill all the terms values
        // to the right up to the last
        // pivot in this particular code is a
        // reverse iterator, so the filling
        // should start from the last element and
        // continue till we come across pivot itself
        std::fill(
            terms.rbegin() + 1,
            pivot,
            pivot_term
        );

        // to find the new value of the last item,
        // we should merely subtract the sum
        // of all terms (except the last, of course)
        // from N
        const size_t cum_sum = std::accumulate(
            terms.cbegin(),
            terms.cend() - 1,
            0lu
        );

        *terms.rbegin() = N - cum_sum;

    } while (must_rearrange());

    return true;
}

// helper operator to pretty-print the partition terms
// separated by '+' sign, as required
std::ostream & operator<<(std::ostream & out, const Partition & p) {
    out << p.terms[0];
    for (size_t i = 1; i < p.terms.size(); ++i) {
        out << '+' << p.terms[i];
    }
    return out;
}
