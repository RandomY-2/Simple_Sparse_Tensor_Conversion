#ifndef UTILS_H
#define UTILS_H

#include <vector>

void get_tensor_detail(int &n_dim, std::vector<int> &dims, std::vector<std::vector<int>> &coo_vals);

void print_coo(int &n_dim, std::vector<int> &dims, std::vector<std::vector<int>> &coo_vals);

#endif
