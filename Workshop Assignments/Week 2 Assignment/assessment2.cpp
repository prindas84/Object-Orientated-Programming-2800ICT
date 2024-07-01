#include <iostream>
using namespace std;

class Rectangle
{
private:
    int x;
    int y;
    double width;
    double length;
public:
    // Contructor Function.
    Rectangle(int px, int py, double w, double l) : x(px), y(py), width(w), length(l) {}
    // Getters and Setters.
    void setX(int);
    void setY(int);
    void setWidth(double);
    void setLength(double);
    int getX() const { return x; };
    int getY() const { return y; };
    double getWidth() const { return width; };
    double getLength() const { return length; };
    double getArea() const { return width * length; };
    // Operator Overload Functions.
    string operator<(const Rectangle &r2) const;
    string operator==(const Rectangle &r2) const;
    string operator>(const Rectangle &r2) const;
    string operator^(const Rectangle &r2) const;
    Rectangle operator+(const Rectangle &r2) const;
    // Member Function.
    double area_of_overlap(const Rectangle &r2) const;
    // Friend Function.
    friend ostream &operator<<(ostream &out, const Rectangle &r1);
};

void Rectangle::setX(int px)
{
    x = px;
}

void Rectangle::setY(int py)
{
    y = py;
}

void Rectangle::setWidth(double w)
{
    if (w > 0)
        width = w;
    else
    {
        cout << "Invalid width\n";
        exit(EXIT_FAILURE);
    }
}

void Rectangle::setLength(double l)
{
    if (l > 0)
        length = l;
    else
    {
        cout << "Invalid length\n";
        exit(EXIT_FAILURE);
    }
}

string Rectangle::operator<(const Rectangle &r2) const
{
    if (getArea() < r2.getArea())
    {
        return "true";
    }
    return "false";
}

string Rectangle::operator==(const Rectangle &r2) const
{
    if (getArea() == r2.getArea())
    {
        return "true";
    }
    return "false";
}

string Rectangle::operator>(const Rectangle &r2) const
{
    if (getArea() > r2.getArea())
    {
        return "true";
    }
    return "false";
}

string Rectangle::operator^(const Rectangle &r2) const
{
    // Get the X values, Y values, widths and lengths for each rectangle.
    int x1 = x;
    int y1 = y;
    double w1 = width;
    double l1 = length;
    int x2 = r2.getX();
    int y2 = r2.getY();
    double w2 = r2.getWidth();
    double l2 = r2.getLength();

    /*  Check if the right side of rectangle 1 is to the left of the left side of rectangle 2, and vice-versa. 
        If so, no intersection is possible */ 
    if (x1 + w1 <= x2 || x2 + w2 <= x1)
    {
        return "true";
    } 

    /*  Check if the top of rectangle 1 is above the top of rectangle 2, and vice-versa.
        If so, no intersection is possible */
    if (y1 + l1 <= y2 || y2 + l2 <= y1)
    {
        return "true";
    }

    // If the above are not true, then the rectangles must intersect.
    return "false";
}

Rectangle Rectangle::operator+(const Rectangle & r2) const
{
    // Get the X, Y values of rectangle 1.
    int x = getX();
    int y = getY();

    // Find the total area of the two rectangles combined.
    double area = getArea() + r2.getArea();

    // Find the average width of the two rectangles.
    double width = (getWidth() + r2.getWidth()) / 2;

    // Using the combined area and the average width, calculate the required length.
    double length = area / width;

    // Return a new rectangle with the above specifications.
    return Rectangle(x, y, width, length);
}

double Rectangle::area_of_overlap(const Rectangle &r2) const
{
    // If the rectangles overlap... (False means they overlap)
    if (operator^(r2) == "false") 
    {
        // Find the positions of the edges for the overlapping section.
        int left = max(x, r2.getX());
        int right = min(x + width, r2.getX() + r2.getWidth());
        int top = max(y, r2.getY());
        int bottom = min(y + length, r2.getY() + r2.getLength());

        // Calculate the width and height of the overlapping section.
        double overlap_width = right - left;
        double overlap_height = bottom - top;

        // Return the area of the overlapping section.
        return overlap_width * overlap_height;
    }
    // If the rectangles don't overlap, the area must be 0.0...
    return 0.0;
}

ostream &operator<<(ostream &out, const Rectangle &r1)
{
    // Print according to the requirements
    out << "Coordinates: " << r1.x << ", " << r1.y << endl
        << "Width: " << r1.width << endl 
        << "Length: " << r1.length << endl 
        << "Area: " << r1.width * r1.length << endl;
    return out;
}

int main(int argc, char* argv[])
{
    Rectangle r1(0, 0, 3, 4);
    cout << "Task1: rectangle r1: \n" << r1 << endl;
    Rectangle r2(1, 2, 3, 2);
    cout << "Task2: r1 < r2:" << (r1 < r2) << endl;
    cout << "Task3: r1 == r2:" << (r1 == r2) << endl;
    cout << "Task4: r1 > r2:" << (r1 > r2) << endl;
    cout << "Task5: r1 ^ r2:" << (r1 ^ r2) << endl << endl;
    cout << "Task6: r1 + r2: \n" << (r1 + r2) << endl;
    cout << "Task7: area of overlap: " << r1.area_of_overlap(r2) <<endl << endl;

    return 0;
}

