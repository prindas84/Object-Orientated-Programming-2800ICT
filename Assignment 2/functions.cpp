#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include "classes.hpp"
#define MAX_GRID 31                             // Maximum grid size to keep the encoded message < 1000 characters.
#define DEFAULT_FILENAME "encoded-file.emf"     // Set the default filename.
#define DEFULT_EXTENSION ".emf"                 // Set the default extension.
using namespace std;

// Prompts the user to enter a filename to save file.
string get_filename()
{
    char input;
    string filename;
    string filename_clean;

    // Loop until a valid input has been received.
    while (true)
    {
        cout << "WOULD YOU LIKE TO SET A CUSTOM FILENAME? (Y/N): ";
        // If cin is not able to go into char, or it is not Y/N ...
        if (!(cin >> input) || (tolower(input) != 'y' && tolower(input) != 'n'))
        {
            cin.clear();                                                           
            cin.ignore(numeric_limits<streamsize>::max(), '\n');                    
            cout << "ERROR: Invalid input. ";
        }
        // A valid response has been inputted.
        else
        {
            if (tolower(input) == 'y')
            {
                while (true)
                {
                    cout << "FILENAME (DO NOT INCLUDE A FILE EXTENSION): ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    getline(cin, filename);
                    // If cin is not able to go into size as an int...
                    if (filename.empty())
                    {
                        throw EncoderException("Invalid filename. Please enter a valid filename."); 
                    }
                    // A valid filename has been inputted.
                    else
                    {
                        // Clean the string of special characters and spaces.
                        for (char c : filename)
                        {
                            if (c == ' ')
                            {
                                filename_clean += '-';
                            }
                            // Check if the character is alphanumeric
                            else if (isalnum(c))
                            {
                                filename_clean += c;
                            }
                        }
                        return filename_clean + DEFULT_EXTENSION;
                    }
                }
            }
            break;
        }
    }
    return DEFAULT_FILENAME;
}


// Returns the grid size of a matrix depending on default size or user input.
int get_matrix_width(string &message)
{
    // Calculate the default grid size.
    int length = message.length();
    int count = 1;
    int increase = 4;
    int steps = 0;

    while (count < length)
    {
        steps += 1;
        count += increase;
        increase += 4;
    }

    // Default grid size.
    int n = (2 * steps) + 1;

    // Once the default grid size had been calculated, prompt user to set their own size if required.
    char input;
    int size = 0;

    // Loop until a valid input has been received.
    while (true)
    {
        cout << "WOULD YOU LIKE TO SET THE MATRIX SIZE? (Y/N): ";
        // If cin is not able to go into char, or it is not Y/N ...
        if (!(cin >> input) || (tolower(input) != 'y' && tolower(input) != 'n'))
        {
            cin.clear();                                         
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "ERROR: Invalid input. ";
        }
        // A valid response has been inputted.
        else
        {
            if (tolower(input) == 'y')
            {
                while (true)
                {
                    cout << "MATRIX SIZE (RANGE: " << n << " - " << MAX_GRID << "): ";
                    // If cin is not able to go into size as an int...
                    if (!(cin >> size) || (size < n || size > MAX_GRID))
                    {
                        cin.clear();                                         
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        cout << "ERROR: Invalid input. ";
                    }
                    // A valid integer has been inputted.
                    else
                    {
                        cout << endl;
                        return size;
                    }
                }
            }
            else
            {
                cout << endl;
            }
            break;
        }
    }
    return n;
}


// Returns a random uppercase character.
char get_random_char()
{
    return 'A' + rand() % 26;
}


// Prompts the user to enter a filename to open a file.
string set_filename()
{
    char input;
    string filename;

    // Loop until a valid input has been received.
    while (true)
    {
        cout << "WOULD YOU LIKE TO OPEN A CUSTOM FILENAME? (Y/N): ";
        // If cin is not able to go into char, or it is not Y/N ...
        if (!(cin >> input) || (tolower(input) != 'y' && tolower(input) != 'n'))
        {
            cin.clear();                                                            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');                   
            cout << "ERROR: Invalid input. ";
        }
        // A valid response has been inputted.
        else
        {
            if (tolower(input) == 'y')
            {
                while (true)
                {
                    cout << "FILENAME (USAGE: filename" << DEFULT_EXTENSION << "): ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    getline(cin, filename);

                    // If cin is empty or the extension is not present, throw an error.
                    bool valid = !(filename.empty()) && (filename.length() > 4) && (filename.substr(filename.length() - 4) == DEFULT_EXTENSION);
                    if (!valid)
                    {
                        throw EncoderException("Invalid filename. Please enter a valid filename and extension."); 
                    }
                    // A valid filename has been inputted.
                    else
                    {
                        return filename;
                    }
                }
            }
            break;
        }
    }
    // Return the default filename.
    return DEFAULT_FILENAME;
}