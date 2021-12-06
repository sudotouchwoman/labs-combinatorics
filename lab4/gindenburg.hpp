#pragma once

#include <vector>
#include <iostream>

class Partition {
private:
    const size_t N;
    const size_t M;
    std::vector<size_t> terms;
private:
    bool end() const;
    bool must_rearrange() const;
    void expand();
public:
    Partition() = delete;
    Partition(const size_t N, const size_t M) :
        N(N), M(M) { terms.reserve(N - M + 1); terms.push_back(N); }
    Partition(const size_t N) : Partition(N, 1) {}
    ~Partition() = default;

    bool next();
    friend std::ostream & operator<<(std::ostream & out, const Partition &);
};
