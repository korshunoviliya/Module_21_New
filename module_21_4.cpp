#include <iostream>
#include <cstdlib>
#include <string>

struct Coordinates
{
    int x;
    int y;
};

struct Character
{
    std::string name;
    int life;
    int armor;
    int damage;
    bool whoIsIt = false;
    Coordinates coordinate;
};

void inputCoordinates(Character coord[], int i)
{
    coord[i].coordinate.x = std::rand() % 40;
    coord[i].coordinate.y = std::rand() % 40;
}

void inputEnemy(Character enemy[])
{
    for(int i = 0; i < 5; ++i)
    {
        enemy[i].name = "Enemy #" + i;
        enemy[i].life = std::rand() % 100 + 50;
        enemy[i].armor = std::rand() % 50;
        enemy[i].damage = std::rand() % 15 + 15;
        inputCoordinates(enemy, i);
        if (i > 0)
        {
            for (int j = 0; j < i; ++j)
            {
                if(enemy[i].coordinate.x == enemy[j].coordinate.x ||
                        enemy[i].coordinate.y == enemy[j].coordinate.y)
                {
                    inputCoordinates(enemy, i);
                    j = 0;
                }
            }
        }
    }
}

void inputPlayer(Character &player)
{
    player.whoIsIt = true;
    std::cout << "Enter your name: ";
    std::cin >> player.name;
    std::cout << "Enter your life: ";
    std::cin >> player.life;
    std::cout << "Enter your armor: ";
    std::cin >> player.armor;
    std::cout << "Enter your damage: ";
    std::cin >> player.damage;
}

int main() {
    Character enemy[5];
    Character player;

    char field[40][40];

}
