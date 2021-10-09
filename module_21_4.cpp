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

void inputCoordinates(Character enemy[], int i)
{
    enemy[i].coordinate.x = std::rand() % 40;
    enemy[i].coordinate.y = std::rand() % 40;
}

void inputEnemy(Character enemy[], Character &player)
{
    for(int i = 0; i < 5; ++i)
    {
        enemy[i].name = "Enemy # " + std::to_string(i);
        enemy[i].life = std::rand() % 100 + 50;
        enemy[i].armor = std::rand() % 50;
        enemy[i].damage = std::rand() % 15 + 15;
        inputCoordinates(enemy, i);
        if (i > 0)
        {
            for (int j = 0; j < i; ++j)
            {
                if((enemy[i].coordinate.x == enemy[j].coordinate.x &&
                        enemy[i].coordinate.y == enemy[j].coordinate.y) &&
                        (enemy[i].coordinate.x == player.coordinate.x &&
                         enemy[i].coordinate.x == player.coordinate.x))
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
    player.coordinate.x = 20;
    player.coordinate.y = 20;
}

void printScreen(char field[][40], Character enemy[], Character &player)
{
    for(int i = 0; i < 5; ++i)
    {
        std::cout << enemy[i].name << " " << enemy[i].life << " " << enemy[i].armor
                  << " " <<enemy[i].damage << " " << enemy[i].whoIsIt << " x:"
                  << enemy[i].coordinate.x << " y:" << enemy[i].coordinate.y << std::endl;
    }
    std::cout << player.name << " " << player.life << " " << player.armor
              << " " << player.damage << " " << player.whoIsIt << " x:"
              << player.coordinate.x << " y:" << player.coordinate.y << std::endl;
    field[(player.coordinate.x)][(player.coordinate.y)] = 'P';

    for(int i = 0; i < 5; ++i)
    {
        field[(enemy[i].coordinate.x)][(enemy[i].coordinate.y)] = 'E';
    }

    for(int j = 0; j < 40; ++j)
    {
        for(int i = 0; i < 40; ++i)
        {
        if(field[i][j] != 'E' && field[i][j] != 'P') field[i][j] = '.';
        std::cout << field[i][j];

        }
        std::cout << std::endl;
    }
}
int main() {
    Character enemy[5]; // массив структуры врагов
    Character player; // игрок
    char field[40][40]{0}; // игровое поле

    //inputPlayer(player); // вводим данные игрока
    player.name = "Ilya";
    player.life = 500;
    player.armor = 100;
    player.damage = 50;
    player.coordinate.x = 20;
    player.coordinate.y = 20;

    inputEnemy(enemy, player); // вводим данные врагов
    printScreen(field, enemy, player); // выводим игровое поле на экран

    std::string turn; // значение хода игрока
    while(true)
    {
        std::cout << "Enter your move: ";
        std::cin >> turn;
        if(turn == "left") --player.coordinate.x;
            else if (turn == "right") ++player.coordinate.x;
            else if (turn == "down") --player.coordinate.y;
            else if (turn == "up") ++player.coordinate.y;
        else std::cout << "Input is not correct. Try again!!!\n";
        fieldBoundaryCheck(); //проверка не выходит ли игрок за границы поля
    }
}
