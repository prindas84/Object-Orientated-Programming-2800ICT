#ifndef CLASSES_HPP
#define CLASSES_HPP
#include <vector>
#include <string>
using namespace std;

// CUSTOM EXCEPTION CLASS
class MatrixException : public exception
{
private:
    string message;

public:
    MatrixException(const string &msg) : message(msg) {}
    // Override what() to return the custom message
    virtual const char *what() const throw()
    {
        return message.c_str();
    }
};

// MAXTIX CLASS.
class Matrix
{
private:
    int row;
    int col;
    vector<vector<int>> int_matrix;

public:
    Matrix(int row = 0, int col = 0) : row(row), col(col), int_matrix(row, std::vector<int>(col, 0)) {} // Default Constructor.
    ~Matrix() {}                                                                                        // Destructor
    int get_row() const { return row; }                                                                 // Get the number of rows
    int get_col() const { return col; }                                                                 // Get the number of cols
    int at(int row, int col) const { return int_matrix[row][col]; }                                     // Get the value of the matrix at (i, j)
    void fill_rand_value();                                                                             // Fill matrix with random values.
    Matrix multiply(const Matrix &v2) const;                                                            // Multiply - single thread.
    Matrix multiplyParallel(const Matrix &v2, int num_threads) const;                                   // Multiply - multi thread.
};

#endif