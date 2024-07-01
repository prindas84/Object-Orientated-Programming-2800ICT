#include <ctime>
#include <iostream>
#include <limits>
#include "classes.hpp"
#include "prototypes.hpp"
using namespace std;

int main()
{
    srand(time(nullptr));
    int selection = 0;
    Decoded decoded_message;
    
    // Loop until the user selects 6 (Quit).
    while (selection != 6)
    {
        try
        {
            // Get the menu selection from the user.                                                              
            selection = display_menu();
        }
        catch (const EncoderException &msg)
        {
            cerr << "ERROR: " << msg.what() << endl;
            selection = 0;                                                            
        }
        
        // Process the user menu selection.
        switch (selection)
        {
            case 1:
                try
                {
                    // Menu option 1.
                    enter_message(decoded_message);
                }
                catch (const EncoderException &msg)
                {
                    cerr << "ERROR: " << msg.what() << endl << endl;                                                               
                }
                break;
            case 2:
                try
                {
                    // Menu option 2.
                    load_message(decoded_message);
                }
                catch (const EncoderException &msg)
                {
                    cerr << "ERROR: " << msg.what() << endl << endl;                                                               
                }
                break;
            case 3:
                try
                {
                    // Menu option 3.
                    encode_message(decoded_message);
                }
                catch (const EncoderException &msg)
                {
                    cerr << "ERROR: " << msg.what() << endl << endl;                                                               
                }
                break;
            case 4:
                try
                {
                    // Menu option 4.
                    decode_message();
                }
                catch (const EncoderException &msg)
                {
                    cerr << "ERROR: " << msg.what() << endl << endl;                                                               
                }
                break;
            case 5:
                try
                {
                    // Menu option 5.
                    save_to_file(decoded_message);
                }
                catch (const EncoderException &msg)
                {
                    cerr << "ERROR: " << msg.what() << endl << endl;                                                               
                }
                break;
            case 6:
                // Menu option 6 (QUIT). 
                break;
            default:
                cout << endl;
        }
    }
    return 0;
}