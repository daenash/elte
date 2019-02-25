#ifndef player_H
#define player_H

#include <iostream>
#include <vector>
#include "../weapon/weapon.h"

class Player
{

  public:
    static int count;
    friend int getPlayerCount();

    // Default konstruktor
    Player();
    
    // Saját konstruktor
    Player(std::string firstName_, std::string lastName_, double weight_, int height_, int inventorySize_);

    // Getterek
    std::string getName();
    double getWeight();
    int getHeight();
    int getInventorySize();

    // Fegyver hozzáadása
    void addWeapon(Weapon weapon_);

    // Fegyverek neveinek kiíratása
    void printWeapons();

  private:
    std::string firstName, lastName;
    double weight;
    int height, inventorySize;
    std::vector<Weapon> weaponSlot;
};

#endif