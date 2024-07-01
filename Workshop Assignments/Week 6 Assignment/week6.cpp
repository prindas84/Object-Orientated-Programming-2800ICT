#include <iostream>
#include <cstdlib>
#include <ctime>
#include "exception_class.cpp"
#include "functions.cpp"
#include "vector_class.cpp"
using namespace std;


int main()
{
    
    srand(time(nullptr));
    bool quit = false;
    vector<NewVector> vectors;

    // Loop while the user has not quit.
    while (!quit)
    {
        
        // Get two vectors from the user. Request the size and prompt for the input method.
        for (int i = 0; i < 2; i++)
        {
            int size = process_input();
            bool manual_input = process_yes_or_no("Mannually input values of this vector (Y/N): ");

            // If the user requests manual input...
            if (manual_input) 
            {
                vector<float> input_data(size);
                get_manual_input(input_data);
                vectors.push_back(NewVector(input_data));
                cout << "Vector vec" << i + 1 << ":" << endl;
                cout << vectors[i] << endl;
            }
            // If the user requests random generation...
            else
            {
                vectors.push_back(NewVector(size));
                cout << "Vector vec" << i + 1 << ":" << endl;
                cout << vectors[i] << endl;
            }
        }

        // Try the overload operations. Display the message if error occurs.
        try
        {
            vectors[0] * vectors[1];
            vectors[0] / vectors[1];  
        }
        catch (const VectorOperationException &msg)
        {
            cerr << "Vector operation error: " << msg.what() << endl;
        }
        
        // Clear the vector of vectors and prompt user for repeat.
        vectors.clear();
        quit = process_yes_or_no("Quit (Y/N): ");
        
    }
}