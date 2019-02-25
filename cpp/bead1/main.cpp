// Készítette: Gutai Dénes

#include <iostream>
#include "weapon/weapon.h"
#include "player/player.h"

// Fegyver kiírására szolgáló segédfüggvény
void printWeapon(Weapon weapon)
{
    std::cout << "Fegyver adatai: " << std::endl;
    std::cout << "- típus: " << weapon.getType() << std::endl;
    std::cout << "- sebzés: " << weapon.getDamage() << std::endl;
    std::cout << "- tár: " << weapon.getAmmo() << std::endl;
    std::cout << "- pontosság: " << weapon.getAccuracy() << std::endl
              << std::endl;
}

// Játékos kiírására szolgáló segédfüggvény
void printPlayer(Player player)
{
    std::cout << "Játékos adatai: " << std::endl;
    std::cout << "- neve: " << player.getName() << std::endl;
    std::cout << "- magassága: " << player.getHeight() << std::endl;
    std::cout << "- súlya: " << player.getWeight() << std::endl;
    std::cout << "- hány fegyvere lehet: " << player.getInventorySize() << std::endl;
    player.printWeapons();
    std::cout << std::endl;
}

int getWeaponCount()
{
    return Weapon::count;
}

int getPlayerCount()
{
    return Player::count;
}

int main()
{
    std::cout << std::endl;

    // Fegyverek inicializálása
    Weapon w1 = Weapon("Glock", 5.5);
    Weapon w2 = Weapon("AK47", 15.8, 30, 7);
    Weapon w3 = Weapon("Dragunov", 33.3, 10, 25);

    // Játékosok inicializálása
    Player p1 = Player();
    Player p2 = Player("Soap", "MacTavish", 81.2, 181, 1);
    Player p3 = Player("Johnny", "OverloadStash", 81.2, 181, 6);
    Player p4 = Player("Johnny", "NegativeStash", 81.2, 181, -1);

    // Fegyverek adása játékosoknak
    std::cout << "Fegyverek adása játékosoknak:" << std::endl;
    p1.addWeapon(w1);
    p1.addWeapon(w2);
    p1.addWeapon(w3);
    p2.addWeapon(w1);
    // Erre kiírja a hibát
    p2.addWeapon(w3);
    std::cout << std::endl;

    // Fegyverek kiírása
    printWeapon(w1);
    printWeapon(w2);

    // Játékosok kiírása
    printPlayer(p1);
    printPlayer(p2);
    printPlayer(p3);
    printPlayer(p4);

    // Létrehozott objektumok létrehozása
    std::cout << "Játékosok száma: " << getPlayerCount() << std::endl;
    std::cout << "Fegyverek száma: " << getWeaponCount() << std::endl;

    return 0;
}
