#include <ctime>
#include <cstdlib>
#include <thread>
#include <vector>
#include "classes.hpp"
#define MIN_VALUE 1
#define MAX_VALUE 100
using namespace std;

void Matrix::fill_rand_value()
{
    srand(time(nullptr));
    for (int i = 0; i < int_matrix.size(); i++)
    {
        for (int j = 0; j < int_matrix[i].size(); j++)
        {
            int_matrix[i][j] = rand() % (MAX_VALUE - MIN_VALUE) + MIN_VALUE;
        }
    }
}

Matrix Matrix::multiply(const Matrix &v2) const
{
    // Throw an error is mismatched sizes.
    if (get_col() != v2.get_row())
    {
        throw MatrixException("Matrix dimensions must match!");
    }

    // Initialise the matrix to return.
    Matrix result(row, v2.get_col());

    // Process the multiplication.
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < v2.get_col(); j++)
        {
            for (int k = 0; k < col; k++)
            {
                result.int_matrix[i][j] += int_matrix[i][k] * v2.int_matrix[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::multiplyParallel(const Matrix &v2, int num_threads) const
{
    // Throw an error is mismatched sizes.
    if (get_col() != v2.get_row())
    {
        throw MatrixException("Matrix dimensions must match!");
    }

    // Calculate the number of rows each thread will handle.
    // Equation works out larger number so integer division doesn't create an uneven distribution.
    int rows_per_thread = (row + num_threads - 1) / num_threads;

    // Create a vector to store the threads
    std::vector<std::thread> threads;

    // Initialise the matrix to return.
    Matrix result(row, v2.get_col());

    // Process the multiplication at the given start row to the given end row.
    auto calculate_rows = [&](int start_row, int end_row)
    {
        for (int i = start_row; i < end_row && i < row; i++)
        {
            for (int j = 0; j < v2.get_col(); j++)
            {
                for (int k = 0; k < col; k++)
                {
                    result.int_matrix[i][j] += int_matrix[i][k] * v2.int_matrix[k][j];
                }
            }
        }
    };

    // Create and start the threads using the correct start and end position.
    for (int i = 0; i < num_threads; i++)
    {
        int start_row = i * rows_per_thread;
        int end_row = (i + 1) * rows_per_thread;
        threads.emplace_back(calculate_rows, start_row, end_row);
    }

    // Join the threads.
    for (auto &thread : threads)
    {
        thread.join();
    }

    return result;
}