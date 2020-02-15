#include <iostream>
#include <cmath>
#include <map>
#include <iterator>

// interface
class Interface
{
public:
    // pure virtual function
    virtual double getArea() const = 0;
};

// abstract base class
class Shape : public Interface
{
protected:
    std::string _name;

public:
    Shape(const std::string &name_)
        : _name(name_) {}
    virtual ~Shape() {}

    // setter
    inline void setName(const std::string &name_) { _name = name_; }

    // getter
    inline const std::string &getName() const { return _name; }

    // defining the virtual function from interface
    //   double getArea() const { std::cerr << "Shape has no are "; return -99; }
    virtual double getDistrict() const = 0; // now Shape is an abstract class
};

// derived class
class Circle : public Shape
{
    double _radius;

public:
    Circle(const std::string &name_, double radius_)
        : Shape(name_), _radius(radius_) {}
    ~Circle() {}

    // setter
    inline void setRadius(double radius_) { _radius = radius_; }

    // getter
    inline double getRadius() const { return _radius; }

    double getArea() const { return 3.14 * _radius * _radius; }
    double getDistrict() const { return 2 * _radius * 3.14; }
};

// derived class
class Rectangle : public Shape
{
    double _length;
    double _width;

public:
    Rectangle(const std::string &name_, double length_, double width_)
        : Shape(name_), _length(length_), _width(width_) {}
    ~Rectangle() {}

    // setters
    inline void setLength(double length_) { _length = length_; }
    inline void setWidth(double width_) { _width = width_; }

    // getters
    inline double getLength() const { return _length; }
    inline double getWidth() const { return _width; }

    double getArea() const { return _length * _width; }
    double getDistrict() const { return 2 * _length + 2 * _width; }
};

// derived class
class Triangle : public Shape
{
    double _base;
    double _width;
    double _length;

public:
    Triangle(const std::string &name_, double base_, double width_)
        : Shape(name_), _base(base_), _width(width_), _length(sqrt(pow(base_, 2) + pow(width_, 2))) {}
    ~Triangle() {}

    // setter
    inline void setBase(double base_) { _base = base_; }
    inline void setWidth(double width_) { _width = width_; }

    // getter
    inline double getBase() const { return _base; }
    inline double getWidth() const { return _width; }

    double getArea() const { return .5 * _base * _width; }
    double getDistrict() const { return _base + _length + _width; }
};

int main(int argc, char const *argv[])
{
    // cannot make an instance from abstract class
    //Shape s("Shape");
    //std::cout << s.getName() << " " << s.getArea() << std::endl;

    std::map<int, int> intMap;
    intMap.insert(std::make_pair(1, 2));
    intMap.insert(std::make_pair(2, 12));

    std::map<int, int>::iterator it = intMap.begin();
    while (it != intMap.end())
    {
        std::cout << it->first << " :: " << it->second << std::endl;
        it++;
    }

    Circle c("Circle", 3);
    std::cout << c.getName() << " " << c.getRadius() << c.getArea() << " "
              << c.getDistrict() << std::endl;

    Rectangle r("Rectangle", 4.2, 2.5);
    std::cout << r.getName() << " " << r.getWidth() << " " << r.getLength() << " "
              << r.getArea() << " " << r.getDistrict() << std::endl;

    Triangle t("Triangle", 3.2, 2.2);
    std::cout << t.getName() << " " << t.getBase() << " " << t.getWidth() << " "
              << t.getArea() << " " << t.getDistrict() << std::endl;

    Shape *shapes[3] = {&c, &r, &t};

    for (int i = 0; i < sizeof(shapes) / sizeof(shapes[0]); ++i)
    {
        std::cout << shapes[i]->getName() << " " << shapes[i]->getArea() << " "
                  << shapes[i]->getDistrict() << std::endl;
    }

    return 0;
}