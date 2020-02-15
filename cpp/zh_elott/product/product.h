#ifndef product_h
#define product_h
#include <iostream>
#include "../pricecategory/pricecategory.h"

class Product : public PriceCategory
{
protected:
    std::string name;
    int price;

public:
    Product();
    Product(int _price, const std::string &_name);
};

#endif