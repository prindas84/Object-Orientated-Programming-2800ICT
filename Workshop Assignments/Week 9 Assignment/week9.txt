#include <iostream>
#include <cstring> //memset
#include <cstdlib> //rand
#include <climits>
#include <memory>

using namespace std;

template <class T>
class Node
{
private:
    T key;

public:
    // Array to hold pointers to node of different level
    std::shared_ptr<Node<T>> *forward;
    Node(T, int);
    T getKey() const { return key; }
    ~Node()
    {
        std::cout << "key " << key << " destroyed.\n";
        delete[] forward;
    }
};

template <class T>
Node<T>::Node(T key, int level)
{
    this->key = key;
    // Allocate memory to forward
    forward = new std::shared_ptr<Node<T>>[level + 1];
    // Fill forward array with 0(NULL)
    std::memset(forward, 0, sizeof(std::shared_ptr<Node<T>>) * (level + 1));
};

template <class T>
class SkipList
{
    // Maximum level for this skip list
    int MAXLVL;
    float P = 0.5;
    // current level of skip list
    int level;
    // pointer to header node
    std::shared_ptr<Node<T>> header;

public:
    SkipList(int, float);
    bool searchElement(int);
    void insertElement(int, int=-1);
    void deleteElement(int);
    void displayList();
    int randomLevel();

    ~SkipList()
    {
        std::cout << "skip list destroyed.\n";
    }
};

template <class T>
SkipList<T>::SkipList(int MAXLVL, float P)
{
    this->MAXLVL = MAXLVL;
    this->P = P;
    level = 0;
    // create header node and initialize key to -1
    header = std::make_shared<Node<T>>(INT_MIN, MAXLVL);
};

// create random level for node
template <class T>
int SkipList<T>::randomLevel()
{
    float r = (float)rand() / RAND_MAX;
    int lvl = 0;
    while (r < P && lvl < MAXLVL)
    {
        lvl++;
        r = (float)rand() / RAND_MAX;
    }
    return lvl;
};

template <class T>
bool SkipList<T>::searchElement(int key)
{
    std::shared_ptr<Node<T>> current = header;
    for (int i = MAXLVL - 1; i >= 0; i--)
    {
        std::cout << "(level:" << i << ", node:" << current->getKey() << ") -> \n";
        while (current->forward[i] && current->forward[i]->getKey() < key)
        {
            current = current->forward[i];
            std::cout << "(level:" << i << ", node:" << current->getKey() << ") -> \n";
        }
    }
    current = current->forward[0];

    if (current && current->getKey() == key)
    {
        std::cout << "(level:0, node:" << current->getKey() << ")\n";
        return true;
    }
    else
    {
        return false;
    }
};

template <class T>
void SkipList<T>::insertElement(int key, int level)
{
    std::shared_ptr<Node<T>> current = header;
    // create update array and initialize it
    std::shared_ptr<Node<T>> update[MAXLVL + 1];
    std::memset(update, 0, sizeof(std::shared_ptr<Node<T>>) * (MAXLVL + 1));
    for (int i = MAXLVL; i >= 0; i--)
    {
        while (current->forward[i] != nullptr && current->forward[i]->getKey() < key)
        {
            current = current->forward[i];
        }
        if (i < level)
            update[i] = current;
    }
    current = current->forward[0];
    if (current == nullptr || current->getKey() != key)
    {
        std::shared_ptr<Node<T>> n = std::make_shared<Node<T>>(key, level);
        for (int i = 0; i < level; i++)
        {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
        cout << "Successfully Inserted key " << key << "\n";
    }
};


template <class T>
void SkipList<T>::deleteElement(int key)
{
    std::shared_ptr<Node<T>> current = header;
    // create update array and initialize it
    std::shared_ptr<Node<T>> update[MAXLVL + 1];
    std::memset(update, 0, sizeof(std::shared_ptr<Node<T>>) * (MAXLVL + 1));
    for (int i = MAXLVL - 1; i >= 0; i--)
    {
        while (current->forward[i] != nullptr &&
               current->forward[i]->getKey() < key)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];
    if (current != nullptr and current->getKey() == key)
    {
        for (int i = 0; i <= MAXLVL - 1; i++)
        {
            if (update[i]->forward[i] != current)
            {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }
        // Remove levels having no elements
        while (level > 0 && header->forward[level] == nullptr)
        {
            level--;
        }
        cout << "Successfully deleted key " << key << "\n";
    }
};

// Display skip list level wise
template <class T>
void SkipList<T>::displayList()
{
    cout << "\n*****Skip List*****"
         << "\n";
    for (int i = 0; i < MAXLVL; i++)
    {
        std::shared_ptr<Node<T>> node = header->forward[i];
        cout << "Level " << i << ": ";
        while (node != nullptr)
        {
            cout << node->getKey() << " ";
            node = node->forward[i];
        }
        cout << "\n";
    }
};


// MUST NOT CHANGE THE MAIN FUNCTION

int main()
{
    srand(static_cast<unsigned>(time(nullptr))); // Seed random number generator

    SkipList<int> lst(3, 0.5);

    std::cout << "======== Insertion ========\n";
    lst.insertElement(5, 1);
    lst.insertElement(25, 2);
    lst.insertElement(30, 1);
    lst.insertElement(31, 3);
    lst.insertElement(42, 1);
    lst.insertElement(58, 2);
    lst.insertElement(62, 1);
    lst.insertElement(69, 3);
    lst.displayList();

    std::cout << "\n======== Search ========\n";
    int key = 31;
    if (lst.searchElement(key))
    {
        std::cout << "Found " << key << std::endl;
    }
    else
    {
        std::cout << "Key " << key << " not found.\n";
    }

    std::cout << "\n======== Deletion ========\n";
    lst.deleteElement(key);
    lst.displayList();
    
    std::cout << "\n======== Automatic Memory Management ========\n";
}
