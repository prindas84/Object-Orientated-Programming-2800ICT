#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;


void get_manual_input(vector<float> &input_data)
{
    // For each element in the vector, request an input from the user.
    for (int i = 0; i < input_data.size(); i++)
    {
        // Loop until a valid input has been received.
        float input;
        while (true)
        {
            cout << "Enter a number #" << i + 1 << " ";
            // If cin is not able to go into size as an int...
            if (!(cin >> input))
            {
                cin.clear();                                                // Clear the error flag.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');        // Ignore the invalid input.
                cout << "Invalid input. ";
            }
            // A valid integer has been inputted.
            else
            {
                input_data[i] = input;
                break;
            }
        }
    }
}


int process_input()
{
    // Loop until a valid input has been received.
    int size;
    while (true)
    {
        cout << "Enter the number of elements for the vector: ";
        // If cin is not able to go into size as an int...
        if (!(cin >> size))
        {
            cin.clear();                                                // Clear the error flag.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');        // Ignore the invalid input.
            cout << "Invalid input. ";
        }
        // A valid integer has been inputted.
        else
        {
            break;
        }
    }
    return size;
}


bool process_yes_or_no(string message)
{
    bool decision = false;
    char input;

    // Loop until a valid input has been received.
    while (true)
    {
        cout << message;
        // If cin is not able to go into char, or it is not Y/N ...
        if (!(cin >> input) || (tolower(input) != 'y' && tolower(input) != 'n'))
        {
            cin.clear();                                                // Clear the error flag.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');        // Ignore the invalid input.
            cout << "Invalid input. ";
        }
        // A valid response has been inputted.
        else
        { 
            if (tolower(input) == 'y')
            {
                decision = true;
            }
            break;
        }
    }
    return decision;
}







