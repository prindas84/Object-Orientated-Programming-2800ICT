#include <iostream>
#include <vector>
#include "base.cpp"
#include "derived.cpp"
using namespace std;

int main()
{
    vector<MediaItem *> items;
    items.push_back(new Book("1984", 1949, "George Orwell", 328));
    items.push_back(new Movie("Inception", 2010, "Christopher Nolan", 148));
    items.push_back(new MusicAlbum("Thriller", 1982, "Michael Jackson", 9));

    int idx = 1;
    for (auto item : items)
    {
        cout << "Task " << idx++ << ": ";
        item->display();

        DigitalCopy *digital = dynamic_cast<DigitalCopy *>(item);
        if (digital)
        {
            cout << "Task " << idx++ << ": ";
            digital->showDownloadDetails();
        }
    }
    for (auto item : items)
        delete item;

    items.clear();

    return 0;
}
