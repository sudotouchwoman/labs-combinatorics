#include "transversal.hpp"

// Matrix methods definition

void Matrix::DeleteMX() {
    if (mx == nullptr) return;
    for (size_t i = 0; i < n_rows; ++i)
        delete [] mx[i];
    delete [] mx;
    mx = nullptr;
}

void Matrix::FillFromFile(std::istream &source) {
    if (mx != nullptr) DeleteMX();
    source >> n_rows >> n_cols;

    mx = new size_t*[n_rows]();
    for (size_t i = 0; i < n_rows; ++i) {
        mx[i] = new size_t[n_cols]();
        for (size_t j = 0; j < n_cols; ++j) {
            source >> mx[i][j];
        }
    }
}

const size_t *const Matrix::row(const size_t row) {
    if (row > n_rows - 1) throw std::exception();
    return mx[row];
}

void Matrix::pretty_print(std::ostream & out) {
    if (mx == nullptr) {
        out << "Empty matrix!!!\n";
        throw std::exception();
        return;
    }
    out << "About matrix: " << n_rows << " rows, " << n_cols << " cols\n";
    for (size_t i = 0; i < n_rows; ++i) {
        out << i+1 << ") ";
        for (size_t j = 0; j < n_cols; ++j) {
            out << mx[i][j] << " ";
        }
        out << '\n';
    }
}

// DArray methods definition

DArray::DArray(DArray & other) {
    capacity = other.capacity;
    n_size = other.n_size;
    internal_buffer = new size_t[capacity]();
    for (size_t i = 0; i < n_size; ++i) {
        internal_buffer[i] = other.internal_buffer[i];
    }
} 

DArray::DArray(const size_t def_size) {
    internal_buffer = new size_t[def_size]();
    capacity = def_size;
}

void DArray::resize() {
    if (capacity == 0) {
        const size_t new_capacity = 2;
        internal_buffer = new size_t[new_capacity]();
        capacity = new_capacity;        
        return;
    }
    const size_t new_capacity = capacity * 2;
    size_t *new_buffer = new size_t[new_capacity]();
    for (size_t i = 0; i < capacity; ++i) {
        new_buffer[i] = internal_buffer[i];
    }
    delete [] internal_buffer;
    internal_buffer = new_buffer;
    capacity = new_capacity;
}

void DArray::PushBack(const size_t value) {
    if (n_size == capacity) resize();
    internal_buffer[n_size++] = value;
}

void print_DArray(std::ostream & out, DArray & buf) {    
    if (buf.size() == 0) {
        out << "Empty set!!!\n";
        return;
    }
    for (size_t i = 0; i < buf.size(); ++i) out << buf[i] << " ";
    out << "\n";
}

void DArray::add_capacity(const size_t new_capacity) {
    size_t *new_buffer = new size_t[new_capacity]();

    for (size_t i = 0; i < n_size; ++i) {
        new_buffer[i] = internal_buffer[i];
    }
    delete [] internal_buffer;
    internal_buffer = new_buffer;
    capacity = new_capacity;
}

// Transversal methods definition

Transversal::Transversal(Matrix & mx) : total_subsets(mx.rows()), total_elements(mx.cols()) {
    S   = new DArray[mx.rows()];
    T.add_capacity(mx.rows());
    for (size_t i = 0; i < mx.rows(); ++i) {
        // T.PushBack(mx.cols());  // init T with number of columns (impossible value)
        for (size_t j = 0; j < mx.cols(); ++j) {
            if (mx.row(i)[j] == 1) S[i].PushBack(j + 1);
        }
    }
}

Transversal::~Transversal() {
    delete [] S;
}

void Transversal::ShowSubsets(std::ostream & out) {
    out << "Set configurations:\n";
    for (size_t i = 0; i < total_subsets; ++i) {
        out << "S_" << i << " ";
        print_DArray(out, S[i]);
    }
}

void Transversal::InitT() {

    auto element_is_free = [&](const size_t value) {
        // check if element is free, i.e. not present in T
        for (size_t i = 0; i < T.size(); ++i)
            if (T[i] == value) return false;
        return true;
    };

    for (size_t i = 0; i < total_subsets; ++i) {
        bool found_free_element = false;
        for (size_t j = 0; j < S[i].size(); ++j)
            if (element_is_free(S[i][j])) {
                found_free_element = true;
                T.PushBack(S[i][j]);  // T holds the resulting transversal
                break;
            }
        if (not found_free_element) break;
    }
}

void Transversal::DoAlgorithmVerbose(std::ostream & out) {
    // main function: init the subsets and T, 
    // then perform Hall algo with output to spectified stream
    ShowSubsets(out);
    InitT();

    out << "T initially contains: "; print_DArray(out, T);
    
    size_t iter = 1;
    while (UpdateT() == OK) {
        out << iter <<") T:\t"; print_DArray(out, T);
    }
    out << "FINAL RESULT:\n"; print_DArray(out, T);
    out << "\nFinished\n";
}

int Transversal::UpdateT() {
    const size_t set_to_inspect = T.size();
    if (set_to_inspect == total_subsets) return FULL_T;
    
    DArray L;           // list of values
    DArray L_indices;   // list of corresponding indices
    for (size_t i = 0; i < S[set_to_inspect].size(); ++i) {
        L.PushBack(S[set_to_inspect][i]);
        L_indices.PushBack(set_to_inspect);
    }

    size_t L_start_size = L.size();
    if (L_start_size == 0) return INCOMPLETE_TVSL;  // no new items, algorithm aborted
    size_t L_counter = 0, Set_counter = 0;

    auto FindElement = [](DArray & DA, const size_t element){
        for (size_t i = 0; i < DA.size(); ++i)
            if (DA[i] == element) return i;
        return DA.size();
    };

    while ((Set_counter = FindElement(T, L[L_counter])) != T.size()) {
        // add non-representative elements of all sets (basic Hall's algorithm)
        for (size_t i = 0; i < S[Set_counter].size(); ++i) {
            if (FindElement(L, S[Set_counter][i]) == L.size()) {
                L.PushBack(S[Set_counter][i]);
                L_indices.PushBack(Set_counter);
            }
        }
        if (L_counter == L.size() - 1) {
            std::cerr << "INCOMPLETE TRANSVERSAL!!!\n";
            return INCOMPLETE_TVSL;
        }
        ++L_counter;
    }

    size_t element_to_swap = L_counter;
    // swap the representive elements
    bool flag = true;
    while (flag) {
        if (element_to_swap < L_start_size) {
            T.PushBack(L[element_to_swap]);
            flag = false;
        }
        else {
            const size_t free_element = T[L_indices[element_to_swap]];
            T[L_indices[element_to_swap]] = L[element_to_swap];
            element_to_swap = FindElement(L, free_element);
        }
    }
    return OK;
}
