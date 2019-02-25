#ifndef weapon_H
#define weapon_H

#include <iostream>

class Weapon
{

public:
  static int count;
  friend int getWeaponCount();

  // Saját konstruktor
  Weapon(std::string type_, double damage_, int ammo_ = 0, int accuracy_ = 0);

  // Getterek
  std::string getType();
  double getDamage();
  int getAmmo();
  int getAccuracy();

  // Setterek
  void setDamage(double damage_);
  void setAmmo(int ammo_);
  void setAccuracy(int accuracy_);

private:
  std::string type;
  double damage;
  int ammo, accuracy;
};

#endif