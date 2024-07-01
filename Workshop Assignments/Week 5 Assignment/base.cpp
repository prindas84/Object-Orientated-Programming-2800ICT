#include <iostream>
#include <string>
using namespace std;

// Media Item base class.
class MediaItem
{
private:
    string title;
    int releaseYear;

public:
    MediaItem(string title = "", int year = 0);
    // Pure virtual function.
    virtual void display() const = 0;
    friend ostream &operator<<(ostream &out, const MediaItem &mem);
};

// Constructor function.
MediaItem::MediaItem(string title, int year) : title(title), releaseYear(year) {}

// Overloaded function
ostream &operator<<(ostream &out, const MediaItem &mem)
{
    out << "title: " << mem.title << ", releaseYear: " << mem.releaseYear;
    return out;
}



// Digital Copy abstract base class.
class DigitalCopy
{
public:
    // Pure virtual function.
    virtual void showDownloadDetails() const = 0;
};
