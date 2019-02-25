#include "weapon.h"

Weapon::Weapon(std::string type_, double damage_, int ammo_, int accuracy_)
{
    type = type_;
    damage = damage_;
    ammo = ammo_;
    accuracy = accuracy_;
    count++;
}

std::string Weapon::getType()
{
    return type;
}

double Weapon::getDamage()
{
    return damage;
}

int Weapon::getAmmo()
{
    return ammo;
}

int Weapon::getAccuracy()
{
    return accuracy;
}

void Weapon::setDamage(double damage_)
{
    if (damage_ >= 0)
    {
        damage = damage_;
    }
};

void Weapon::setAmmo(int ammo_)
{
    if (ammo_ >= 0)
    {
        damage = ammo_;
    }
};

void Weapon::setAccuracy(int accuracy_)
{
    if (accuracy_ >= 0)
    {
        damage = accuracy_;
    }
};

int Weapon::count = 0;