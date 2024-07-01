#ifndef MENU_OPTIONS_HPP
#define MENU_OPTIONS_HPP
#include "classes.hpp"

// FUNCTION PROTOTYPE DECLARATIONS.
int display_menu();
void enter_message(Decoded &decoded_message);
void load_message(Decoded &decoded_message);
void encode_message(Decoded &decoded_message);
void decode_message();
void save_to_file(Decoded &decoded_message);
string get_filename();
int get_matrix_width(string &message);
char get_random_char();
string set_filename();

#endif // MENU_OPTIONS_HPP