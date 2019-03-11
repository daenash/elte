#include <iostream>

// Operátor túlterhelés

class A
{
  private:
    int *num;

  public:
    A() : num(new int(1)) {}
    ~A() { delete num; }

    // copy ctor
    A(const A &rhs)
    {
        num = new int;
        *num = *rhs.num;
    }

    // assingment operator
    A &operator=(const A &rhs)
    {
        if (this != &rhs)
        {
            num = new int;
            *num = *rhs.num;
        }
        return *this;
    }

    A &operator+(const A &rhs)
    {
        *num += *rhs.num;
        return *this;
    }

    int *getNumRef() { return num; }
};

int main(int argc, char const *argv[])
{
    A a1;
    A a2(a1);  //cctor
    A a3 = a2; // cctor
    A a4;
    a4 = a3; // assignment op

    std::cout << a1.getNumRef() << std::endl;
    std::cout << a2.getNumRef() << std::endl;

    a1 = a2 + a2;

    std::cout << *a2.getNumRef() << std::endl;

    return 0;
}
