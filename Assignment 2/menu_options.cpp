#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include "classes.hpp"
#include "prototypes.hpp"
#define MAX_DECODED 481         // Maximum decoded string length to set max grid 31 x 31, to keep the encoded message < 1000 characters.
#define MAX_ENCODED 961         // Maximum possible encoded string length to fit in grid 31 x 31.
using namespace std;

// Displays the main menu. Prompts for selection.
int display_menu() {

    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "* 1. Enter a message                                *" << endl;
    cout << "* 2. Load an encoded message from a file            *" << endl;
    cout << "* 3. Encode a message                               *" << endl;
    cout << "* 4. Decode a message                               *" << endl;
    cout << "* 5. Save the encoded & decoded message to a file   *" << endl;
    cout << "* 6. Quit                                           *" << endl;
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
    cout << "ENTER YOUR SELECTION: ";
    int input;

    while (true)
    {
        // If cin is not able to go into size as an int...
        if (!(cin >> input) || !(input >= 1 && input <= 6))
        {
            cin.clear();                                                                
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw EncoderException("Invalid selection. Please select from the menu above.");                        
        }

        // A valid integer has been inputted.
        else
        {
            break;
        }
    }
    return input;
}


// Menu option 1.
void enter_message(Decoded &decoded_message)
{
    // Get the user input.
    string user_input = "";

    while(user_input == "")
    {
        cout << "ENTER MESSAGE (TYPE 'QUIT' TO RETURN TO MENU): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, user_input);

        // Convert the input to uppercase and remove spaces.
        string output;
        for (char c : user_input) {
            if (c != ' ')
            {
                output.push_back(toupper(c));
            }
        }

        // Process the message.
        if (!(output == "QUIT") && user_input != "" && user_input.length() <= MAX_DECODED)
        {
            decoded_message(output);
            decoded_message.print_info();
        }
        else if (user_input == "")
        {
            throw EncoderException("No message entered. Please enter a valid message.");
        }
        else if (user_input.length() > MAX_DECODED)
        {
            throw EncoderException("Message too long. (MAX LENGTH: " + to_string(MAX_DECODED) + " - EXCLUDING WHITESPACE).");
        }
        else
        {
            cout << endl;
        }
    }
}


// Menu option 2.
void load_message(Decoded &decoded_message)
{
    try
    {
        // Prompt the user for the file they want to open.
        string filename = set_filename();
        ifstream infile(filename);
        if (!infile.is_open()) 
        {
            throw EncoderException("Unable to open file. Please try again.");
        }

        // Get the first line of the file, which is the encoded message to load.
        string message;
        getline(infile, message);

        // Close the file
        infile.close();

        // If the message is too long, throw an error.
        if (message.length() > MAX_ENCODED)
        {
            throw EncoderException("Message too long. (MAX LENGTH: " + to_string(MAX_ENCODED) + " - EXCLUDING WHITESPACE).");
        }

        // Decode the encoded message then upload it to memory and print it.
        int length = message.length();
        int square = sqrt(length);
        if (length > MAX_ENCODED)
        {
            throw EncoderException("Invalid message length. (MAX LENGTH: " + to_string(MAX_ENCODED) + ").");
        }
        else if ((square * square == length) && (square % 2 != 0))
        {
            Encoded encoded_message(message, square);
            decoded_message(encoded_message.get_message());
            encoded_message.print_info();
        }
        else
        {
            throw EncoderException("Invalid message length. Encoded messages must be an the square of an odd number.");
        }
    }
    catch (const EncoderException &msg)
    {
        cerr << "ERROR: " << msg.what() << endl << endl;                                                               
    }
}


// Menu option 3.
void encode_message(Decoded &decoded_message)
{
    string message = decoded_message.get_message();

    // If there is no message set in memory, throw an error.
    if (message == "")
    {
        throw EncoderException("There is no message currently stored in memory.");
    }
    else
    {
        // Encode the message and print it.
        int n = get_matrix_width(message);
        decoded_message.encode_message(n);
        decoded_message.print_info(true);
    } 
}


// Menu option 4.
void decode_message()
{
    // Get the user input.
    string user_input = "";

    while(user_input == "")
    {                                                              
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ENTER MESSAGE TO DECODE (TYPE 'QUIT' TO RETURN TO MENU): ";
        getline(cin, user_input);

        // Convert the input to uppercase and remove spaces.
        string output;
        for (char c : user_input) {
            if (c != ' ')
            {
                output.push_back(toupper(c));
            }
        }

        // Process the decoded message.
        if (!(output == "QUIT"))
        {
            int length = output.length();
            int square = sqrt(length);
            if (length > MAX_ENCODED)
            {
                throw EncoderException("Invalid message length. (MAX LENGTH: " + to_string(MAX_ENCODED) + ").");
            }
            else if ((square * square == length) && (square % 2 != 0))
            {
                Encoded encoded_message(output, square);
                cout << endl;
                encoded_message.print_info();
            }
            else
            {
                throw EncoderException("Invalid message length. Encoded messages must be an the square of an odd number.");
            }
        }
        else
        {
            cout << endl;
        }
    }
}


// Menu option 5.
void save_to_file(Decoded &decoded_message)
{
    // Get the information stored in memory.
    string message = decoded_message.get_message();
    vector<vector<char>> matrix = decoded_message.get_matrix();
    string matrix_string;

    // Concatenate the matrix to a string for saving.
    for (const auto &row : matrix)
    {
        for (char ch : row)
        {
            matrix_string += ch;
        }
    }

    // If there is no message set in memory, throw an error.
    if (message == "")
    {
        throw EncoderException("There is no message currently stored in memory.");
    }
    else
    {
        try
        {
            // Prompt the user for the filename they want to use to save.
            string filename = get_filename();
            ofstream outfile(filename);
            if (outfile.is_open())
            {
                // Write data to the file.
                outfile << matrix_string << endl;
                outfile << message << endl;
                
                // Close the file.
                outfile.close();
                
                cout << "YOUR FILE HAS BEEN SAVED: " << filename << endl << endl;
            }
            else 
            {
                throw EncoderException("Unable to open file for writing. Please try again.");
            }
        }
        catch (const EncoderException &msg)
        {
            cerr << "ERROR: " << msg.what() << endl << endl;                                                               
        }
    
    }
}