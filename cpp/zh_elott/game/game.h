#ifndef game_h
#define game_h
#include "../product/product.h"

class Game : public Product
{

private:
    std::string license;

public:
    Game();
    Game(int _price, const std::string &_name, const std::string _license);
    std::string toStringOwn();
    int category();
};

#endif