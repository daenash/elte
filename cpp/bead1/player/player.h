#ifndef player_h
#define player_h
#include "../weapon/weapon.h"
#include <vector>

class Player
{

public:
  static int count;
  friend int getPlayerCount();

  // Default konstruktor
  Player();

  // Saját konstruktor
  Player(const std::string& firstName_, const std::string& lastName_, double weight_, int height_, int inventorySize_);

  // Getterek
  const std::string getName() const;
  double getWeight() const;
  int getHeight() const;
  int getInventorySize() const;

  // Fegyver hozzáadása
  void addWeapon(Weapon weapon_);

  // Fegyverek neveinek kiíratása
  void printWeapons() const;

private:
  std::string firstName, lastName;
  double weight;
  int height, inventorySize;
  std::vector<Weapon> weaponSlot;
};

#endif