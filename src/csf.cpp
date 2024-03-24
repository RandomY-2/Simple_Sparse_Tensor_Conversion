#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "utils.h"

std::string get_key(const std::vector<int> &coo_val, int start, int end) {
    std::string res;

    for (int i = start; i <= end; i++) {
        res += std::to_string(coo_val[i]) + "_";
    }

    return res;
}

void convert_coo_to_csf(
    const int n_dim,
    const std::vector<int> &dims,
    const std::vector<std::vector<int>> &coo_vals,
    std::vector<std::vector<int>> &idx,
    std::vector<std::vector<int>> &ptr,
    std::vector<double> &values
) {
    std::unordered_set<std::string> mappings;

    idx.resize(n_dim);
    ptr.resize(n_dim);

    for (size_t i = 0; i < coo_vals.size(); i++) {
        if (i == 0 || coo_vals[i][0] != coo_vals[i - 1][0]) {
            idx[0].push_back(coo_vals[i][0]);
        }

        values.push_back(coo_vals[i][coo_vals[i].size() - 1]);
    }
    ptr[0].push_back(0);
    ptr[0].push_back(idx[0].size());

    for (int d = 1; d < n_dim; d++) {
        std::string prev_key = "";
        int count = 0;

        for (size_t i = 0; i < coo_vals.size(); i++) {
            std::string cur_key = get_key(coo_vals[i], 0, d - 1);
            std::string cur_mapping = cur_key + "->" + std::to_string(coo_vals[i][d]);

            if (mappings.find(cur_mapping) == mappings.end()) {
                idx[d].push_back(coo_vals[i][d]);
                mappings.insert(cur_mapping);

                if (cur_key != prev_key) {
                    ptr[d].push_back(count);
                    prev_key = cur_key;
                }

                count++;
            }
        }

        ptr[d].push_back(count);
    }
}

void traverse_csf(
    const std::vector<std::vector<int>> &idx,
    const std::vector<std::vector<int>> &ptr,
    const std::vector<double> &values,
    size_t dim,
    int prev_pt
) {
    for (int pt = ptr[dim][prev_pt]; pt < ptr[dim][prev_pt + 1]; pt++) {
        int cur_index = idx[dim][pt];

        std::cout << cur_index << " ";

        if (dim < idx.size() - 1) {
            traverse_csf(idx, ptr, values, dim + 1, pt);
        } else {
            std::cout << values[pt] << std::endl;
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

    std::vector<std::vector<int>> ptr;
    std::vector<std::vector<int>> idx;
    std::vector<double> values;
    convert_coo_to_csf(n_dim, dims, coo_vals, idx, ptr, values);

    std::cout << "CSF Ptrs:" << std::endl;
    for (auto &ptr_i : ptr) {
        for (int p : ptr_i) {
            std::cout << p << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "CSF Idxs:" << std::endl;
    for (auto &idx_i : idx) {
        for (int p : idx_i) {
            std::cout << p << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "CSF Values:" << std::endl;
    for (int val : values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;


    std::cout << "Traverse CSF: " << std::endl;
    traverse_csf(idx, ptr, values, 0, 0);
}
