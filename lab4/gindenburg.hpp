#pragma once

#include <vector>
#include <iostream>

// implements Gindenberg's algorithm for
// partition enumeration. Stores unsigned numbers in a vector. The size of
// the vector can be computed from provided M and N. If no M specified, 
// the default value of 1 is used (which implies that all partitions 
// should be yield and enumerated, obviously)
// @param N: the natural number to partize
// @param M: the lower threshold for greatest partition term, i.e.
// it is guaranteed that enumeration skips terms where each term is < M
class Partition {
private:
    const size_t N;  // initital number to partize
    const size_t M;  // lower threshold for max term
    std::vector<size_t> terms;
private:
    bool end() const;
    bool must_rearrange() const;
    void expand();
public:
    Partition(const size_t N = 1, const size_t M = 1);
    Partition(const size_t N) : Partition(N, 1) {}
    ~Partition() = default;

    bool next();
    const std::vector<size_t> & get_terms() const { return terms; }
    friend std::ostream & operator<<(std::ostream & out, const Partition &);
};
