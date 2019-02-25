#include "player.h"

Player::Player()
{
    firstName = "Unknown";
    lastName = "Solider";
    height = 0;
    weight = 0;
    inventorySize = 3;
    count++;
}

Player::Player(std::string firstName_, std::string lastName_, double weight_, int height_, int inventorySize_)
{
    firstName = firstName_;
    lastName = lastName_;
    weight = weight_;
    height = height_;

    if (inventorySize_ < 1 || inventorySize_ > 5)
    {
        inventorySize = 3;
    }
    else
    {
        inventorySize = inventorySize_;
    }
    count++;
}

std::string Player::getName()
{
    return firstName + " " + lastName;
}
double Player::getWeight()
{
    return weight;
}

int Player::getHeight()
{
    return height;
}
int Player::getInventorySize()
{
    return inventorySize;
}

void Player::addWeapon(Weapon weapon_)
{
    if (weaponSlot.size() < inventorySize)
    {
        std::cout << "Fegyver (" << weapon_.getType() << ") hozzáadva a következő játékoshoz: " << getName() << std::endl;
        weaponSlot.push_back(weapon_);
    }
    else
    {
        std::cout << "Hiba! A következő játékos: " + getName() + " nem tud több fegyvert magánál hordozni!" << std::endl;
    }
}

void Player::printWeapons()
{
    std::string weaponNames = "";
    if (weaponSlot.size() == 0)
    {
        std::cout << "A játékosnak: " + getName() + " nincs fegyvere" << std::endl;
        return;
    }
    for (int i = 0; i < weaponSlot.size(); i++)
    {
        weaponNames += "- " + weaponSlot[i].getType() + "\n";
    }
    std::cout << "A játékos: " + getName() + " fegyverei:" << std::endl;
    std::cout << weaponNames;
}

int Player::count = 0;