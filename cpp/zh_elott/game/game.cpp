#include "game.h"

Game::Game() : Product(0, "Unnamed Game")
{
    license = "Unknown license";
}

Game::Game(int _price, const std::string &_name, const std::string _license) : Product(_price, _name)
{
    license = _license;
}

std::string Game::toStringOwn()
{
    std::string stringVersion;

    stringVersion = "Game\n- Name: " + name + "\n- Price: " + std::to_string(price) + "\n- License: " + license;

    return stringVersion;
}

int Game::category()
{
    return 0;
}