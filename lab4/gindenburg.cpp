#include "gindenburg.hpp"

#include <algorithm>
#include <numeric>

bool Partition::end() const {
    return terms.size() == (N - M + 1);
}

bool Partition::must_rearrange() const {
    return *terms.crbegin() < M;
}

void Partition::expand() {
    const auto last_term = *terms.crbegin();
    std::fill(terms.begin(), terms.end(), 1);
    terms.push_back(N - terms.size());
}

bool Partition::next() {
    if (end()) return false;

    do {
        const auto last_term = *terms.crbegin();
        const auto pivot = std::find_if(
            terms.rbegin(),
            terms.rend(),
            [last_term](const size_t x) {
                return last_term - x >= 2;
            }
        );

        if (pivot == terms.rend()) {
            expand();
            return true;
        }

        const size_t pivot_term = *pivot + 1lu;

        std::fill(
            terms.rbegin() + 1,
            pivot + 1,
            pivot_term
        );

        const auto cum_sum = std::accumulate(
            terms.cbegin(),
            terms.cend() - 1,
            0lu
        );

        *terms.rbegin() = N - cum_sum;
    } while (must_rearrange());

    return true;
}

std::ostream & operator<<(std::ostream & out, const Partition & p) {
    out << p.terms[0];
    for (size_t i = 1; i < p.terms.size(); ++i) {
        out << '+' << p.terms[i];
    }
    return out;
}

