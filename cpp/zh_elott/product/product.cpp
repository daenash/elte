#include "product.h"

Product::Product()
{
    price = 0;
    name = "Not named yet";
}

Product::Product(int _price, const std::string &_name)
{
    price = _price;
    name = _name;
}