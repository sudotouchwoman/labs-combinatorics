#ifndef _TRANSVERSAL_HPP
#define _TRANSVERSAL_HPP
#include <fstream>
#include <iostream>

class Matrix {
    private:
        size_t n_rows = 0;
        size_t n_cols = 0;
        size_t **mx = nullptr;
    private:
        void DeleteMX();
    public:
        Matrix() = default;
        ~Matrix() { DeleteMX(); }
        void FillFromFile(std::istream &);
        const size_t * const row(const size_t);
        size_t cols() { return n_cols; }
        size_t rows() { return n_rows; }
        void pretty_print(std::ostream &);
};

class DArray {
    private:
        size_t *internal_buffer = nullptr;
        size_t capacity = 0;
        size_t n_size = 0;
    private:
        void resize();
    public:
        DArray() = default;
        DArray(DArray &);
        DArray(const size_t);
        ~DArray() { delete [] internal_buffer; } ;
        void PushBack(const size_t);
        size_t size() { return n_size; }
        size_t & at(const size_t i)  { return internal_buffer[i]; }
        size_t & operator[](const size_t i) { return internal_buffer[i]; }
        void add_capacity(const size_t new_capacity);
        void increment_size() { ++n_size; }
};

void print_DArray(std::ostream & out, DArray & buf);

enum Hall {
    FULL_T = 1,
    INCOMPLETE_TVSL,
    OK = 0
};

class Transversal {
    private:
        const size_t total_subsets;
        const size_t total_elements;
        DArray T;
        DArray *S = nullptr;
    private:
        void InitT();
        int UpdateT();
        void ShowSubsets(std::ostream &);
    public:
        Transversal(Matrix &);
        ~Transversal();
        void DoAlgorithmVerbose(std::ostream &);
};

#endif  // _TRANSVERSAL_HPP
