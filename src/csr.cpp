#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include "utils.h"

void coo_to_csr(
    const int n_dim,
    const std::vector<int> &dims,
    const std::vector<std::vector<int>> &coo_vals,
    std::vector<int>& csr_row_ptr,
    std::vector<int>& csr_col_ind,
    std::vector<double>& csr_values
) {
    assert(n_dim == 2 && dims.size() == 2);

    // compress row indices to only have n_rows + 1 elements
    // the number of elements at row i would be (csr_row_ptr[i + 1] - csr_row_ptr[i])
    int max_row_i = 0;
    for (auto &coo_val : coo_vals) {
        max_row_i = std::max(coo_val[0], max_row_i);
    }
    csr_row_ptr.resize(max_row_i + 2, 0); // row_size = max_row_i + 1, ptr_size = row_size + 1

    for (auto &coo_val : coo_vals) {
        assert(coo_val.size() == 3);

        int r = coo_val[0], c = coo_val[1], v = coo_val[2];
        csr_row_ptr[r + 1] += 1;

        // uncompressed col indices and values in row sorted order
        csr_col_ind.push_back(c);
        csr_values.push_back(v);
    }

    for (size_t i = 1; i < csr_row_ptr.size(); i++) {
        csr_row_ptr[i] += csr_row_ptr[i - 1];
    }
}

void traverse_csr(
    const std::vector<int>& csr_row_ptr,
    const std::vector<int>& csr_col_ind,
    const std::vector<double>& csr_values
) {
    for (size_t i = 0; i < csr_row_ptr.size() - 1; i++) {
        int r = i, c_start = csr_row_ptr[i], c_end = csr_row_ptr[i + 1];

        for (int j = c_start; j < c_end; j++) {
            std::cout << r << " " << csr_col_ind[j] << " " << csr_values[j] << std::endl;
        }
    }
}

int main() {
    int n_dim = -1;
    std::vector<int> dims;
    std::vector<std::vector<int>> coo_vals;

    get_tensor_detail(n_dim, dims, coo_vals);

    // compressed format need sorted order
    sort(coo_vals.begin(), coo_vals.end());

    print_coo(n_dim, dims, coo_vals);

    std::vector<int> csr_row_ptr;
    std::vector<int> csr_col_ind;
    std::vector<double> csr_values;

    coo_to_csr(n_dim, dims, coo_vals, csr_row_ptr, csr_col_ind, csr_values);

    std::cout << "CSR Row Ptr: ";
    for (int i : csr_row_ptr) std::cout << i << " ";
    std::cout << "\nCSR Col Ind: ";
    for (int i : csr_col_ind) std::cout << i << " ";
    std::cout << "\nCSR Values: ";
    for (double v : csr_values) std::cout << v << " ";
    std::cout << std::endl;

    std::cout << "Traverse CSR: " << std::endl;
    traverse_csr(csr_row_ptr, csr_col_ind, csr_values);
}
