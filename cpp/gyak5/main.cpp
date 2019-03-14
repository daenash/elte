// 5. gyakorlat

#include <iostream>
#include <memory>

// defining class Base
class Base
{
  public:
    Base() { std::cout << "Base ctor" << std::endl; }
    ~Base() { std::cout << "Base dtor" << std::endl; }
    virtual void f() = 0;
    void g() { std::cout << "function `g` called from Base" << std::endl; }
};

// defining class Derived
class Derived : public Base
{
  public:
    Derived() { std::cout << "Derived ctor" << std::endl; }
    ~Derived() { std::cout << "Derived dtor" << std::endl; }
    void f(){};
};

int main()
{
    Derived d1;
    d1.g();

    std::unique_ptr<int> ptr = std::make_unique<int>(1);
    std::cout << *ptr << std::endl;

    return 0;
}