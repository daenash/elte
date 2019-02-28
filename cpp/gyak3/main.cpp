// Készítette: Gutai Dénes

#include <iostream>
#include <vector>

/* Jegyzetek:
 *
 * HEAP: "végtelen virtuális memóriatér"
 * 
 * Memóriaszivárgás elkerülése
 * 
 * User defined class object copying
 * Shallow copy jön létre default esetben (int-re jó, de heapes pointerhez semmiképp)
 * Ezért kell a saját copy konstruktor
 * 
 * 
 */

class A
{
  public:
    // : a(a_), b(b_) egyből létrehozza az a-t és a b-t;
    A(int a_, int b_) : a(a_), b(b_), p(new int(1)){};

    // másoló konstruktor
    A(const A &o) : a(o.a), b(o.b)
    {
        p = new int;
        *p = *o.p;
    };

    // Értékadó operátor felülírása
    A &operator=(const A &o)
    {
        if (this != &o)
        {
            *this = A(o);
        }
        else
        {
            return *this;
        }
        return *this;
    };

    // << operátor felülírása
    friend std::ostream &operator<<(std::ostream &os, const A &o)
    {
        return os << o.getA() << " " << o.getB() << " " << *o.getP();
    };

    // destruktor
    ~A() { delete p; };

    // getterek
    int getA() const { return a; };
    int getB() const { return b; };
    int *getP() const { return p; };

  private:
    int a, b;
    int *p;
};

int main()
{
    {
        // new -> létrehozza a heapen
        int *i = new int(123);

        // delete -> kitörli a heapről. SCOPE VÉGÉN KÖTELEZŐ!
        delete i;
    }

    {
        // tömb a heapen, mutató az első elemre
        int *arr = new int[5];

        // delete [] -> indexelőoperátor törli az egész listát.
        delete[] arr;
    }

    A a1 = A(1, 2);
    A a2 = A(3, 4);
    A a3 = A(a2);
    A a4 = a3;

    std::cout << a1 << std::endl;
    std::cout << a2 << std::endl;
    std::cout << a3 << std::endl;
    std::cout << a4 << std::endl;

    return 0;
}
