# Simple Sparse Tensor Conversion Methods

This repository contains implementations for converting sparse tensors between different storage formats, specifically COO (Coordinate List), CSR (Compressed Sparse Row), and CSF (Compressed Sparse Fiber).

## Features

- **COO to CSR Conversion:** Transforms a tensor from Coordinate List format to Compressed Sparse Row format. This is useful for matrices (2D tensors).

- **COO to CSF Conversion:** Converts a tensor from Coordinate List format to Compressed Sparse Fiber format. CSF is advantageous for higher-dimensional tensors, providing a more compact representation and facilitating operations like tensor slicing and element-wise operations.
