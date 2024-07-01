#include <exception>
#include <string>
using namespace std;

// CUSTOM EXCEPTION CLASS
class DataException : public exception
{
private:
    string message;

public:
    DataException(const string &message) : message(message) {}
    virtual const char *what() const throw()
    {
        return message.c_str();
    }
};