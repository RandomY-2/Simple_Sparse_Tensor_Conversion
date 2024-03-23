#include <iostream>
#include <sstream>
#include <vector>
#include <limits>


void get_tensor_detail(int &n_dim, std::vector<int> &dims, std::vector<std::vector<int>> &coo_vals) {
    std::cout << "Please enter number of tensor dimensions: ";
    std::cin >> n_dim;

    dims = std::vector<int>(n_dim, 0);

    if(n_dim <= 0) {
        std::cerr << "Number of dimensions must be positive." << std::endl;
        return;
    }

    dims.resize(n_dim, 0);

    std::cout << "Please enter the size for each dimension:" << std::endl;

    for(int i = 0; i < n_dim; ++i) {
        std::cout << "Dimension " << i << ": ";
        std::cin >> dims[i];
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter the COO values for the tensor. Enter a negative index at any point to stop." << std::endl;

    while(true) {
        std::string line;
        std::vector<int> coo_entry(n_dim);
        int value;

        std::cout << "Coordinates: ";
        std::getline(std::cin, line);
        std::istringstream iss(line);
        for(int i = 0; i < n_dim; ++i) {
            if (!(iss >> coo_entry[i])) {
                std::cerr << "Error reading coordinates. Please ensure you enter the correct number of dimensions." << std::endl;
                return;
            }
            if(coo_entry[i] < 0) {
                return;
            }
        }

        std::cout << "Value: ";
        std::cin >> value;
        std::cin.ignore();

        coo_entry.push_back(value);
        coo_vals.push_back(coo_entry);
    }
}

void print_coo(int &n_dim, std::vector<int> &dims, std::vector<std::vector<int>> &coo_vals) {
    std::cout << "tensor number of dimensions: " << n_dim << std::endl;

    for (int dim : dims) {
        std::cout << dim << " ";
    }

    std::cout << std::endl;

    for (auto &coo_val : coo_vals) {
        for (int i : coo_val) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}
