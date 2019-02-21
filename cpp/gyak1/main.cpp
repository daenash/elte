// Készítette: Gutai Dénes

#include <iostream>

// `A` névtér
namespace A
{
int x = 1;
}

// `B` névtér
namespace B
{
int x = 2;
}

// Névtér a névtérben
namespace C
{
namespace D
{
int x = 3;
}
} // namespace C

// Globális változó
int n;

// Név nélküli névtér, adattagjai globális változóként viselkednek
namespace
{
}

// Mutatókkal végzett swap
void swapPtr(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Referencia alapján végzett swap
void swapRef(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

int main()
{

    int q = 1;
    int w = 2;
    std::cout << "Eredeti: " << q << " " << w << std::endl;
    swapPtr(&q, &w); // mivel mutatókat vár a függvény, a változók referenciáját kell átadni
    std::cout << "swapPtr után: " << q << " " << w << std::endl;
    swapRef(q, w); // nem adjuk át a változót csak egy aliast, amivel hivatkozunk az eredeti változóre, nem történik másolás
    std::cout << "swapRef után: " << q << " " << w << std::endl;

    std::cout << C::D::x;

    
    // Példa a shadowing-ra
    // lokális változó a STACK-en, élettartama a deklarációtól hatókör végéig tart
    int n = 1;                              
    {
        // lokális változó a belső scope-ban                                       
        int n = 2;                          

        // eredmény: 20 - a main() elején létrehozott n az utána következő blokkban
        std::cout << n << ::n << std::endl; 
    }                                            

    int i = 0;
    int k = 0;

    // nincs szekvenciapont, így az i++ kiértékelése véletlenszerű sorrendben történik
    // warningot küld a fordítás során
    std::cout << i++ << i++ << std::endl;

    // konstans változó, az értéke nem módosulhat, mindig inicializálni kell őket
    // konstans korrektség: A változó értéke nem módosulhat
    const int j = 1; 

    // int-re mutató mutató, ami mutat az n változóra
    int *pN = &n;                               

    // az első tag a memóricíme a mutatónak, a második az integer értéke amire mutat
    std::cout << pN << " " << *pN << std::endl; 

    // konstans integerre mutató mutató                                            
    const int *cpI = &j;
    
    // integerre mutató konstans mutató
    // a mutató csak erre az integerre mutathat, nem változhat az értéke
    int *const pcI = &i;

    // integerre mutató mutatóra mutató mutató
    int **ppI;
    
    // konstans int-re mutató konstans mutatóra mutató mutató
    const int *const *b; 

    // konstans int-re mutató konstans mutatóra mutató konstans mutatóra mutató konstans mutató
    const int *const *const *const a = &b;
    
}
