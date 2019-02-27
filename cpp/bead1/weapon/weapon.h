#ifndef weapon_h
#define weapon_h
#include <iostream>


class Weapon
{

public:
  static int count;
  friend int getWeaponCount();

  // Saját konstruktor
  Weapon(const std::string& type_, double damage_, int ammo_ = 0, int accuracy_ = 0);

  // Getterek
  std::string getType() const;
  double getDamage() const;
  int getAmmo() const;
  int getAccuracy() const;

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