#include "product/product.h"
#include "game/game.h"
// #include <string>
#include <sstream>
#include <fstream>

int main(int argc, char const *argv[])
{
    for (int i = 0; i < argc; i++)
    {
        std::string a(argv[i]);
        if (a == "asd")
        {
            std::cout << argv[i] << std::endl;
        }
    }

    // std::string input;
    // std::cin >> input;

    // std::cout << input << std::endl;

    Game cod1 = Game(12000, "Call of Duty", "Activision");
    Game newGame = Game();
    std::cout << cod1.toStringOwn() << std::endl;
    std::cout << newGame.toStringOwn() << std::endl;

    int cc = 3;
    int *bb = &cc;
    const int *muti = &cc;
    std::cout << muti << " " << *muti << std::endl;
    cc = 5;
    std::cout << muti << " " << *muti << std::endl;
    muti = bb;
    std::cout << muti << " " << *muti << std::endl;

    std::ifstream infile("thefile.txt");
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        int a, b;
        if (!(iss >> a >> b))
        {
            break;
        } // error

        std::cout << line << std::endl;
    }

    return 0;
}