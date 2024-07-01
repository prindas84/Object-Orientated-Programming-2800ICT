#include <iostream>
#include <string>
using namespace std;

// DATA VERSION CLASS - BASE CLASS
class DataVersion
{
private:
    string version;

public:
    DataVersion(const string &version = "v1.0.0") : version(version){};
    friend ostream &operator<<(ostream &out, const DataVersion &other);
    virtual void print_info() const = 0;
    void set_version(const string &version) { this->version = version; }
};

ostream &operator<<(ostream &out, const DataVersion &other)
{
    out << "Data Version: " << other.version;
    return out;
}