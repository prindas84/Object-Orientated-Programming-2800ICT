#ifndef MESSAGE_CLASS_HPP
#define MESSAGE_CLASS_HPP
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// CUSTOM EXCEPTION CLASS
class EncoderException : public exception
{
private:
    string message;

public:
    EncoderException(const string &msg) : message(msg) {}
    // Override what() to return the custom message
    virtual const char *what() const throw()
    {
        return message.c_str();
    }
};


// MAXTIX - BASE CLASS.
class Matrix
{
private:
    vector<vector<char>> char_matrix;                                                                   // Encoded storage.
    vector<vector<bool>> bool_matrix;                                                                   // Manage random letter placement.

protected:
    vector<vector<char>> get_char_matrix() const { return char_matrix; }                                // Protected member function to access char_matrix.

public:
    Matrix(int n = 0) : char_matrix(n, vector<char>(n, 'X')), bool_matrix(n, vector<bool>(n, false)) {} // Default Constructor.
    Matrix(const string &message, int n);                                                               // Overloaded Constructor.
    virtual ~Matrix() {}                                                                                // Virtual Destructor
    void reset_matrix_size(int n);                                                                      // Function to reset the matrix sizes.
    void encode_matrix(const string &message, int n);                                                   // Function to encode a message to a matrix.
    string decode(const string &message, int n);                                                        // Function to decode a messsage from a matrix.
    virtual void print_info(bool detailed = false) const = 0;                                           // Pure virtual print function.
    friend ostream &operator<<(ostream &out, const Matrix &matrix);                                     // Overload the << functionality.
};


// DECODED MESSAGE - DERIVED CLASS.
class Decoded : public Matrix
{
private:
    string message;                                                                                     // Store the decoded message.

public:
    Decoded(const string &message = "", int n = 0) : Matrix(n), message(message) { encode_message(n); } // Default Constructor.
    void operator()(const string &message);                                                             // Overload the () functionality.                              
    void encode_message(int n);                                                                         // Function to encode a decoded message.
    string get_message() { return this->message; }                                                      // Funtion to get the stored message.
    vector<vector<char>> get_matrix() const { return get_char_matrix(); }                               // Funtion to get the stored matrix.
    void print_info(bool detailed = false) const override;                                              // Overide print function.
};


// ENCODED MESSAGE - DERIVED CLASS.
class Encoded : public Matrix
{
private:
    string message;                                                                                     // Store the decoded message.

public:
    Encoded(const string &message, int n) : Matrix(message, n), message(decode(message, n)) {}          // Default Constructor.
    string get_message() { return this->message; }                                                      // Funtion to get the stored message.
    void print_info(bool detailed = false) const override;                                              // Overide print function.
};

#endif // MESSAGE_CLASS_HPP
