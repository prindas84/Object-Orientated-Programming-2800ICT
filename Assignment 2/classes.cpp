#include "classes.hpp"
#include "prototypes.hpp"
using namespace std;

// MATRIX METHODS
// Overloaded Constructor.
Matrix::Matrix(const string &message, int n)
{
    // Initialise the char and bool matrices.
    char_matrix.resize(n, vector<char>(n));
    bool_matrix.resize(n, vector<bool>(n, true));

    // Populate the char matrix with the encoded message.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // Keeps track of the correct index of the message string.
            int index = (i * n + j) % message.length();
            char_matrix[i][j] = message[index];
        }
    }
}

// Reset Function to resize and initialise the char and bool matrices.
void Matrix::reset_matrix_size(int n)
{
    char_matrix.resize(n);
    for (auto &row : char_matrix)
    {
        row.clear();
        row.resize(n, 'X');
    }

    bool_matrix.resize(n);
    for (auto &row : bool_matrix)
    {
        row.clear();
        row.resize(n, false);
    }
}

// Function to encode a message to a matrix.
void Matrix::encode_matrix(const string &message, int n)
{
    // Set variables required for the encoding loop.
    int temp_n = n;
    int length = message.length();
    int count = 0;
    int start_row = (n - 1) / 2;
    int second_row = 1;
    int end_row = 0;
    int start_col = 0;
    int second_col = n - 2;
    int iteration = 0;

    // While there are letters in the message that need to be encoded, loop and set them in the char matrix following the diamond pattern.
    while (count < length)
    {
        for (int i = start_row; i >= end_row; i--)
        {
            if (count < length)
            {
                char_matrix[i][start_col] = message[count];
                bool_matrix[i][start_col] = true;
                count += 1;
                start_col += 1;
            }
            else
            {
                break;
            }
        }
        for (int i = second_row; i <= start_row; i++)
        {
            if (count < length)
            {
                char_matrix[i][start_col] = message[count];
                bool_matrix[i][start_col] = true;
                count += 1;
                start_col += 1;
            }
            else
            {
                break;
            }
        }
        for (int i = start_row + 1; i <= temp_n - 1; i++)
        {
            if (count < length)
            {
                char_matrix[i][second_col] = message[count];
                bool_matrix[i][second_col] = true;
                count += 1;
                second_col -= 1;
            }
            else
            {
                break;
            }
        }
        for (int i = temp_n - 2; i > start_row; i--)
        {
            if (count < length)
            {
                char_matrix[i][second_col] = message[count];
                bool_matrix[i][second_col] = true;
                count += 1;
                second_col -= 1;
            }
            else
            {
                break;
            }
        }
        start_col += 1;
        second_row += 1;
        end_row += 1;
        temp_n -= 1;
        iteration += 1;
        start_col = 0 + iteration;
        second_col = n - 2 - iteration;
    }

    // Loop through the bool matrix to find which positions require a random letter. Set each position to a random letter.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (bool_matrix[i][j] == false)
            {
                char_matrix[i][j] = get_random_char();
            }
        }
    }
}

// Function to decode a messsage from a matrix.
string Matrix::decode(const string &message, int n)
{
    // Set variables required for the decoding loop.
    string output;
    int temp_n = n;
    int start_row = (n - 1) / 2;
    int second_row = 1;
    int end_row = 0;
    int start_col = 0;
    int second_col = n - 2;
    int iteration = 0;

    // Follow the diamond pattern until the middle sqaure has been reached. Push each required character to the output string.
    while (iteration <= (n - 1) / 2)
    {
        for (int i = start_row; i >= end_row; i--)
        {
            output.push_back(char_matrix[i][start_col]);
            start_col += 1;
        }
        for (int i = second_row; i <= start_row; i++)
        {
            output.push_back(char_matrix[i][start_col]);
            start_col += 1;
        }
        for (int i = start_row + 1; i <= temp_n - 1; i++)
        {
            output.push_back(char_matrix[i][second_col]);
            second_col -= 1;
        }
        for (int i = temp_n - 2; i > start_row; i--)
        {
            output.push_back(char_matrix[i][second_col]);
            second_col -= 1;
        }
        start_col += 1;
        second_row += 1;
        end_row += 1;
        temp_n -= 1;
        iteration += 1;
        start_col = 0 + iteration;
        second_col = n - 2 - iteration;
    }
    return output;
}

// Overloaded function to print the encoded message.
ostream &operator<<(ostream &out, const Matrix &matrix)
{
    // Loop over the entire char matrix to print the encoded message.
    for (const auto &row : matrix.char_matrix)
    {
        for (char ch : row)
        {
            out << ch;
        }
    }
    return out;
}


// DECODED MESSAGE METHODS
// Overload the () functionality.
void Decoded::operator()(const string &message)
{
    this->message = message;
    int n = get_matrix_width(this->message);
    this->encode_message(n);
}

// Function to encode a decoded message.
void Decoded::encode_message(int n)
{
    this->reset_matrix_size(n);
    this->encode_matrix(this->message, n);
}

// Overide print function.
void Decoded::print_info(bool detailed) const
{
    if (detailed)
    {
        cout << "Stored Message: " << message << endl;
    }
    cout << "Encoded Message: " << *this << endl << endl;
}


// ENCODED MESSAGE METHODS
// Overide print function.
void Encoded::print_info(bool detailed) const
{
    cout << "Decoded Message: " << message << endl << endl;
}