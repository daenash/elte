// Készítette: Gutai Dénes

#include <iostream>

/* Jegyzetek:
 *
 * OOP paradigmák:
 *  - Enkapszuláció
 *  - Absztakció
 *  - Öröklődés
 *  - Poliformizmus (override functions)
 * 
 */

/**
 * Osztály létrehozása
 * 
 * Játékos osztály
 * 
 * Tartalmazza:
 * - Játékos neve
 * - Játékos magassága
 * - Játékos súlya
*/
class Player
{

    // alapból private egy adattag
    int j;

    // bárhonnan elérhető
    // mindig öröklődik
  public:
    // Default konstruktor
    Player();

    // User defined konstruktor
    Player(std::string, int, double);

    // destruktor
    // allokált memória felszabadítása
    ~Player();

    // a `name` adattag változtatására szolgáló függvény
    void setName(std::string name_);
    std::string getName() const;

    // Egyből inicializálódik a program fordulásaokor
    // És csak egyszer
    // Csak osztályon kívül lehet neki értéket adni
    // Kivéve ha const
    static int count;

    // csak itt elérhető
    // mindig öröklődik
  private:
    // suáramztatott osztályokban is elérhető
    // mindig öröklődik

    std::string name;
    int height;
    double weight;

  protected:
    // általában az adattagok mind privátok
    // átállítani ezeket -> setterekker
    // visszanyerni a dolgaikat -> getterek
};

// konstruktor definiálása
Player::Player()
{
    name = "Gipsz Jakab";
    height = 0;
    weight = 0;
    count++;
}

// a publikus count változó inicializálása a global scopbeban
int Player::count = 0;

// user defined konstruktor
Player::Player(std::string name, int height, double weight)
{
    this->name = name;
    this->height = height;
    this->weight = weight;
}

// a setName függvény definiálása
// beállítja egy játékos nevét arra, amit paraméterként kap
void Player::setName(std::string name_)
{
    name = name_;
}

// a getName függvény definiálása
// visszaadja a játékos nevét
std::string Player::getName() const
{
    return name;
}

// destruktor definiálása
Player::~Player()
{
}

int main()
{

    // STACK-re létrehozás
    // FILO -> First in last out

    // Változók élettartama: definíciótól a scope végéig

    Player player;
    Player player2;

    std::cout << "Hello World!" << std::endl;
    player.setName("Kiss Jenő");
    std::cout << player.getName() << std::endl;
    std::cout << player2.getName() << std::endl;
    std::cout << Player::count << std::endl;
    return 0;
}
