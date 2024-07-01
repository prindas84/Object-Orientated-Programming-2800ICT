using namespace std;
class Point
{
private:
    double *x;
    double *y;

public:
    Point(double x = 0, double y = 0);
    ~Point();
    Point(const Point &other);
    Point(Point &&other) noexcept;
    Point &operator=(const Point &other);
    Point &operator=(Point &&other) noexcept;
    void setX(double x);
    void setY(double y);
    double getX() const { return *x; }
    double getY() const { return *y; }
};

// Constructor Function.
Point::Point(double x, double y)
{
    this->x = new double(x);
    this->y = new double(y);
}

// Destructor Function.
Point::~Point()
{
    delete x;
    delete y;
}

// Copy Constructor.
Point::Point(const Point &other)
{
    cout << "Point: Copy constructor\n";
    x = new double(*(other.x));
    y = new double(*(other.y));
}

// Move Constructor.
Point::Point(Point &&other) noexcept
{
    cout << "Point: Move constructor\n";
    x = other.x;
    y = other.y;
    other.x = nullptr;
    other.y = nullptr;
}

// Copy Assignment
Point &Point::operator=(const Point &other)
{
    cout << "Point: Copy assignment\n";
    if (this != &other)
    {
        // Release the current resources.
        delete x;
        delete y;

        // Dereference the value at other X, Y and assign it to the new object.
        x = new double(*other.x);
        y = new double(*other.y);
    }
    return *this;
}

// Move Assignment
Point &Point::operator=(Point &&other) noexcept
{
    cout << "Point: Move assignment\n";
    if (this != &other)
    {
        // Release the current resources.
        delete x;
        delete y;

        // Transfer the resource to the new object.
        x = other.x;
        y = other.y;

        // Set the original pointer to null.
        other.x = nullptr;
        other.y = nullptr;
    }
    return *this;
}

// Set the X pointer to X value.
void Point::setX(double x)
{
    *(this->x) = x;
}

// Set the Y pointer to Y value.
void Point::setY(double y)
{
    *(this->y) = y;
}
