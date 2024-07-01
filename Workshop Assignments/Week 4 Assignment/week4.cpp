#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath> // for std::pow and M_PI, for example M_PI * std::pow(radius, 2);
#include "point.cpp"
#include "circle.cpp"
using namespace std;

int main()
{
    Point p1(1.0, 1.0);
    Point p2(2.0, 2.0);

    cout << "output 1: " << endl;
    Circle c1(p1, 5.0);
    cout << endl;

    cout << "output 2: " << endl;
    Circle c2 = c1; // Test Point and Circle copy constructor
    cout << endl;

    cout << "output 3: " << endl;
    Circle c3(std::move(c1)); // Test Point and Circle move constructor
    cout << endl;

    cout << "output 4: " << endl;
    Circle c4(p2, 10.0);
    cout << endl;

    cout << "output 5: " << endl;
    c4 = c2; // Test copy assignment
    cout << endl;

    cout << "output 6: " << endl;
    c4 = std::move(c3); // Test move assignment
    cout << endl;

    cout << "output 7: " << endl;
    // Test friend function (addition of areas)
    double totalArea = c2 + c4;
    std::cout << "Total area of c2 and c4: " << totalArea << std::endl;

    return 0;
}
