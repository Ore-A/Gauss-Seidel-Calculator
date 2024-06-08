# Gauss-Seidel Implementation

This project contains an implementation of the Gauss-Seidel iterative method for solving systems of linear equations.

## Table of Contents
- [Description](#description)
- [Usage](#usage)
- [Input Format](#input-format)
- [Output Format](#output-format)
- [Code Structure](#code-structure)
- [Sparse Matrix Compression](#sparse-matrix-compression)
- [Author](#author)

## Description

The Gauss-Seidel method is an iterative technique for solving a system of linear equations. This particular implementation leverages the concept of sparse matrices to efficiently manage large datasets, striking a balance between computational precision and performance.

## Usage

The program supports two modes of operation:
1. **File Input Mode**: Provide a filename of a CSV file containing the augmented matrix.
2. **Interactive Mode**:  Execute the program without any arguments and manually input the number of equations along with their coefficients.

### Running the Program
1. Compile the program using `make`:
   ```bash
   make
   ```
2. Choose the desired mode of operation: 
- **With CSV File:**
    ```bash
    ./gauss_seidel input_matrix.csv
    ```
Where `input.csv` is a CSV file that contains the matrix of coefficients and the vector of constants. The first `n` columns are the coefficients and the last column is the constants.

The program will write the solution to a file named `ans.csv`.

- **Without Arguments:**
    ```bash
    ./gauss_seidel
    ```

In interactive mode, users will be prompted to enter the number of equations and the coefficients for each variable and constant.

## Input Format
The input matrix should contain `n+1` columns, where `n` is the number of variables in the system. The first `n` columns are the coefficients of the variables in each equation, and the last column is the constants. Each row represents an equation.

For example, the following matrix represents the system of equations `2x + 3y = 5` and `4x - y = 1`:
```
2,3,5
4,-1,1
```

## Output Format
The output matrix contains one column and `n` rows, where `n` is the number of variables in the system. Each row represents the value of a variable.
For example, the following matrix represents the solution `x = 1` and `y = 1`:
```
1
1
```

## Code Structure

- `main`: Contains the main function and handles command-line input.
- `get_matrix_from_csv`: Reads a matrix of doubles from a CSV file, determines the number of rows and columns, allocates memory for the matrix, and fills it with the data from the file.
- `convert_to_sparse`: Converts the given dense matrix into a sparse matrix in a Coordinate List (COO) format.
- `gauss_seidel`: Implements the Gauss-Seidel algorithm.
- `write_solution_to_csv`: Writes an array of doubles to a CSV file, iterating over the array and writing each element on a new line.

## Sparse Matrix Compression

In addition to solving systems of linear equations, this program also demonstrates the efficiency of sparse matrix representation. After converting the input matrix to a sparse format, the program calculates and reports the space savings achieved through this compression.

The space savings is calculated as the ratio of non-zero elements in the sparse matrix to the total elements in the original matrix, subtracted from 1. This value is then reported as a percentage.

For example, if there are 22 equations (with 22 unknowns), the original augmented matrix would have 22 × 23 elements. If the sparse matrix representation only contains 197 non-zero elements, the space savings would be calculated as 1 - (197 / (22 * 23)), which is approximately 61%.

The program reports this information by printing to standard error (not standard out) in the following format:
```
Compressed matrix contains 197 elements, compressed by 61%
```
This feature provides a clear demonstration of the efficiency benefits of sparse matrix representation, particularly for large systems of equations where the majority of elements may be zero.

## Author
- Oreoluwa Abejide

