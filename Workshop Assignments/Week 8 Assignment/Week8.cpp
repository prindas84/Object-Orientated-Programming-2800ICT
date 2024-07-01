#include <vector>
#include <thread>
#include <functional>
#include <iostream>
#include <chrono>
#include "classes.hpp"
using namespace std;



// MUST NOT CHANGE
int demo(int row_1, int col_1, int row_2, int col_2, int num_threads=2) {

    // Create two large matrices
    Matrix matrixA(row_1, col_1);  // Initialize with 0
    matrixA.fill_rand_value();
    Matrix matrixB(row_2, col_2);  // Initialize with 0
    matrixB.fill_rand_value();

    // Perform single-threaded matrix multiplication
    auto start = chrono::high_resolution_clock::now();
    Matrix resultSingle = matrixA.multiply(matrixB);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> singleThreadTime = end - start;
    cout << "Single-threaded multiplication took " << singleThreadTime.count() << " ms." << endl;

    // Perform multithreaded matrix multiplication
    start = chrono::high_resolution_clock::now();
    Matrix resultMulti = matrixA.multiplyParallel(matrixB, num_threads);  // Using 4 threads
    end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> multiThreadTime = end - start;
    cout << "Multithreaded multiplication took " << multiThreadTime.count() << " ms." << endl;

    // Compare results for validation purposes
    cout << "Validating results..." << endl;
    bool valid = true;
    for (int i = 0; i < row_1; i++) {
        for (int j = 0; j < col_2; j++) {
            if (resultSingle.at(i, j) != resultMulti.at(i, j)) {
                valid = false;
                break;
            }
        }
        if (!valid) break;
    }
    if (valid) {
        cout << "Results are identical!" << endl;
    } else {
        cout << "Results differ!" << endl;
    }

    return 0;
}

void SafeIntInput(int &input, const string& info)
{
    cout<<info;
    cin>>input;

    while(cin.fail() or input<1)
    {
        cout<<"Invalid input. "<<info;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin>>input;
    }
}

int main()
{
    int row_1 = 0, col_1 = 0, row_2 = 0, col_2 = 0, num_threads=2;
    char QUIT = 'N';
    while (!(tolower(QUIT) == 'y'))
    {
        SafeIntInput(row_1,"Enter the number of rows of Matrix A: ");
        SafeIntInput(col_1,"Enter the number of cols of Matrix A: ");
        SafeIntInput(row_2,"Enter the number of rows of Matrix B: ");
        SafeIntInput(col_2,"Enter the number of cols of Matrix B: ");

        SafeIntInput(num_threads,"Enter the number of threads: ");

        try
        {
            demo(row_1,col_1,row_2,col_2,num_threads);
        }
        catch(const exception &e)
        {
            cout << e.what() << endl;
        }

        cout<<"Quit (Y/N): ";
        while(!(cin>>QUIT) or !(tolower(QUIT) == 'y' or tolower(QUIT) == 'n'))
        {
            cout<<"Invalid input: the input must be either Y or N. Quit (Y/N):";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout<<endl;

    }
}