#include <iostream>
#include <cstdlib>
#include <string>

enum WhoIsIt
        {
            ENEMY,
            PLAYER = 5
        };

struct Character
{
    std::string name;
    int life{0};
    int armor{0};
    int damage{0};
    bool is_life{true};
    int coordinateX{0};
    int coordinateY{0};
};

void saveGame();
void loadGame();

void inputEnemy(Character character[])
{
    for(int i = 0; i < 5; ++i)
    {
        character[i].name = "Enemy # " + std::to_string(i);
        character[i].life = std::rand() % 100 + 50;
        character[i].armor = std::rand() % 50;
        character[i].damage = std::rand() % 15 + 15;
        character[i].coordinateX = std::rand() % 40;
        character[i].coordinateY = std::rand() % 40;

        if (i > 0)
        {
            for (int j = 0; j < i; ++j)
            {
                if((character[i].coordinateX == character[j].coordinateX &&
                        character[i].coordinateY == character[j].coordinateY) ||
                        (character[i].coordinateX == character[PLAYER].coordinateX &&
                         character[i].coordinateY == character[PLAYER].coordinateY))
                {
                    character[i].coordinateX = std::rand() % 40;
                    character[i].coordinateY = std::rand() % 40;
                    j = 0;
                }
            }
        }
    }
}

Character inputPlayer(Character &player)
{
    std::cout << "Enter your name: ";
    std::cin >> player.name;
    std::cout << "Enter your life: ";
    std::cin >> player.life;
    std::cout << "Enter your armor: ";
    std::cin >> player.armor;
    std::cout << "Enter your damage: ";
    std::cin >> player.damage;
    player.coordinateX = 20;
    player.coordinateY = 20;
    return player;
}

void printScreen(char field[][40], Character character[])
{
    for(int i = 0; i < 6; ++i)
    {
        std::cout << character[i].name << " " << character[i].life << " " << character[i].armor
                  << " " <<character[i].damage << " " << " x:"
                  << character[i].coordinateX << " y:" << character[i].coordinateY << std::endl;
    }
    if(character[PLAYER].is_life)
    {
        field[character[PLAYER].coordinateX][(character[PLAYER].coordinateY)] = 'P';
    }
    else
    {
        std::cout << "The player is dead! game over.";
        exit(0);
    }
    for(int i = 0; i < 5; ++i)
    {
        if(character[i].is_life)
        {
            field[(character[i].coordinateX)][(character[i].coordinateY)] = 'E';
        }
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

Character fieldBoundaryCheck(Character &person)
{
    if (person.coordinateX > 40) --person.coordinateX;
    else if (person.coordinateX < 0) ++person.coordinateX;
    if (person.coordinateY > 40) --person.coordinateY;
    else if (person.coordinateY < 0) ++person.coordinateY;

    return person;
}

void attack (Character &whoShoot, Character &whoFall)
{
    whoFall.armor -= whoShoot.damage;
    if (whoFall.armor <= 0)
    {
        whoFall.life += whoFall.armor;
        whoFall.armor = 0;
    }
    if (whoFall.life < 0)
    {
        whoFall.life = 0;
        whoFall.is_life = false;
    }
}

void enemyMove(Character character[])
{
    for (int i = 0; i < 5; ++i)
    {
        bool check{false};
        int moveX;
        int moveY;
        do {
            moveX = std::rand() % 3 - 1;
            moveY = std::rand() % 3 - 1;
            if((moveX + moveY) != 0) check = true;
        } while(!check);

        character[i].coordinateX += moveX;
        character[i].coordinateY += moveY;

        if((character[i].coordinateX == character[PLAYER].coordinateX)
            && (character[i].coordinateY == character[PLAYER].coordinateY))
        {
            character[i].coordinateX -= moveX;
            character[i].coordinateY -= moveY;
            attack(character[i], character[PLAYER]);
        }

        for (int j = 0; j < i; ++j)
        {
            if(character[i].coordinateX == character[j].coordinateX &&
                character[i].coordinateY == character[j].coordinateY)
            {
                character[i].coordinateX -= moveX;
                character[i].coordinateY -= moveY;
            }
        }
        fieldBoundaryCheck(character[i]);
    }
}

int main() {
    Character character[6];
    char field[40][40]{0}; // игровое поле

    //player = inputPlayer(player); // вводим данные игрока
    character[PLAYER].name = "Ilya";
    character[PLAYER].life = 500;
    character[PLAYER].armor = 100;
    character[PLAYER].damage = 50;
    character[PLAYER].coordinateX = 20;
    character[PLAYER].coordinateY = 20;

    inputEnemy(character); // вводим данные врагов
    printScreen(field, character); // выводим игровое поле на экран

    std::string turn; // значение хода игрока
    while(true)
    {
        int saveX = character[PLAYER].coordinateX; // сохраняем координаты до хода
        int saveY = character[PLAYER].coordinateY;
        std::cout << "Enter your move: ";
        std::cin >> turn;
        if(turn == "left") --character[PLAYER].coordinateX;
        else if (turn == "right") ++character[PLAYER].coordinateX;
        else if (turn == "down") --character[PLAYER].coordinateY;
        else if (turn == "up") ++character[PLAYER].coordinateY;
        //else if (turn == "save") saveGame();
        //else if (turn == "load") loadGame();
        else if (turn == "end") return 0;
        else std::cout << "Input is not correct. Try again!!!\n";

        fieldBoundaryCheck(character[PLAYER]); //проверка не выходит ли игрок за границы поля

        for(int i = 0; i < 5; ++i)
        {
            if ((character[i].coordinateX == character[PLAYER].coordinateX)
                && (character[i].coordinateY == character[PLAYER].coordinateY)
                && (character[i].is_life))
            {
                character[PLAYER].coordinateX = saveX;
                character[PLAYER].coordinateY = saveY;
                attack(character[PLAYER], character[i]);
            }
        }

        enemyMove(character); // перемещение врагов
        printScreen(field, character);
    }
}
