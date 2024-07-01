using namespace std;
class Circle
{
private:
    Point center;
    double radius;

public:
    Circle(Point center, double radius) : center(center), radius(radius){};
    Circle(const Circle &other) : center(other.center), radius(other.radius) { cout << "Circle: Copy constructor\n"; };
    Circle(Circle &&other) noexcept : center(std::move(other.center)), radius(other.radius) { cout << "Circle: Move constructor\n"; };
    Circle &operator=(const Circle &other);
    Circle &operator=(Circle &&other) noexcept;
    void setCenter(const Point &newCenter);
    void setRadius(double newRadius);
    Point getCenter() const;
    double getRadius() const;
    double calculateArea() const;
    friend double operator+(const Circle &c1, const Circle &c2);
};

// Copy Assignment
Circle &Circle::operator=(const Circle &other)
{
    cout << "Circle: Copy assignment\n";
    if (this != &other)
    {
        center = other.center;
        radius = other.radius;
    }

    return *this;
}

// Move Assignment
Circle &Circle::operator=(Circle &&other) noexcept
{
    cout << "Circle: Move assignment\n";
    if (this != &other)
    {
        // Transfer the resource to the new object.
        center = std::move(other.center);
        radius = other.radius;
    }
    return *this;
}

// Set the centre of a circle to a new point.
void Circle::setCenter(const Point &newCenter)
{
    center = newCenter;
}

// Set the radius of a circle.
void Circle::setRadius(double newRadius)
{
    radius = newRadius;
}

// Get the point of a circle.
Point Circle::getCenter() const
{
    return center;
}

// Get the radius of a circle.
double Circle::getRadius() const
{
    return radius;
}

// Calculate the area of two circles.
double Circle::calculateArea() const
{
    return M_PI * std::pow(radius, 2);
}

// Calculate the combined area of two circles.
double operator+(const Circle &c1, const Circle &c2)
{
    return c1.calculateArea() + c2.calculateArea();
}
