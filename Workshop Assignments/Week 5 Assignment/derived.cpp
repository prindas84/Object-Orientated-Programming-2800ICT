#include <string>
using namespace std;

// Book derived class.
class Book : public MediaItem
{
private:
    string author;
    int pageCount;

public:
    Book(string title = "", int year = 0, string author = "", int page = 0);
    void display() const override;
};

// Constructor function.
Book::Book(string title, int year, string author, int page) : MediaItem(title, year), author(author), pageCount(page) {}

// Call the base class to print, then print from the dervied class.
void Book::display() const
{
    cout << "Book: " << *this << ", Pages: " << this->pageCount << endl;
}



// Movie derived class. Derived from multiple base classes.
class Movie : public MediaItem, public DigitalCopy
{
private:
    string director;
    int duration;

public:
    Movie(string title = "", int year = 0, string director = "", int duration = 0);
    void display() const override;
    void showDownloadDetails() const override;
};

// Constructor function.
Movie::Movie(string title, int year, string director, int duration) : MediaItem(title, year), director(director), duration(duration) {}

// Call the base class to print, then print from the dervied class.
void Movie::display() const
{
    cout << "Movie: " << *this << ", Duration: " << this->duration << endl;
}

// Call the abstract base class, pure virtual function.
void Movie::showDownloadDetails() const
{
    cout << "Download available at [URL]" << endl;
}



// Music Album derived class. Derived from multiple base classes.
class MusicAlbum : public MediaItem, public DigitalCopy
{
private:
    string artist;
    int trackCount;

public:
    MusicAlbum(string title = "", int year = 0, string artist = "", int trackCount = 0);
    void display() const override;
    void showDownloadDetails() const override;
};

// Constructor function.
MusicAlbum::MusicAlbum(string title, int year, string artist, int trackCount) : MediaItem(title, year), artist(artist), trackCount(trackCount) {}

// Call the base class to print, then print from the dervied class.
void MusicAlbum::display() const
{
    cout << "Music Album: " << *this << ", Tracks: " << this->trackCount << endl;
}

// Call the abstract base class, pure virtual function.
void MusicAlbum::showDownloadDetails() const
{
    cout << "Music album download details: [URL]" << endl;
}