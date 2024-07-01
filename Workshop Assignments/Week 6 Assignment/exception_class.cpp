#include <iostream>
#include <exception>
#include <string>
using namespace std;


// Custom exception class
class VectorOperationException : public exception
{
private:
    string message;

public:
    VectorOperationException(const string &msg) : message(msg) {}
    // Override what() to return the custom message
    virtual const char *what() const throw()
    {
        return message.c_str();
    }
};
