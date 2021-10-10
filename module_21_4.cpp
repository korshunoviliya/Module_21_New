#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

int maxField_g = 40; // размер игрового поля(на маленьком легче тестировать)

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

void saveGame(Character character[])
{
    std::ofstream file("..\\myGame.bin", std::ios::binary);
    if (file.is_open())
    {
        for(int i = 0; i < 6; ++i)
        {
            /*file << character[i].name << "\t" << character[i].life << "\t"
                    << character[i].armor << "\t" << character[i].damage << "\t"
                    << character[i].coordinateX << "\t" << character[i].coordinateY
                    << "\t" << character[i].is_life << std::endl;*/

            int len = character[i].name.length();
            file.write((char*) &len, sizeof(len));
            file.write((char*) character[i].name.c_str(), sizeof(len));
            file.write((char*) &character[i].life, sizeof(character[i].life));
            file.write((char*) &character[i].armor, sizeof(character[i].armor));
            file.write((char*) &character[i].damage, sizeof(character[i].damage));
            file.write((char*) &character[i].is_life, sizeof(character[i].is_life));
            file.write((char*) &character[i].coordinateX, sizeof(character[i].coordinateX));
            file.write((char*) &character[i].coordinateY, sizeof(character[i].coordinateY));
        }
        std::cout << "File is save!\n";
        file.close();
    }
    else std::cout << "File is not open!!! Save failed!\n";
}

void loadGame(Character character[])
{
    std::ifstream file("..\\myGame.bin", std::ios::binary);

    if (file.is_open())
    {
        for(int i = 0; i < 6; ++i)
        {
            /*file >> character[i].name  >> character[i].life >>
                  character[i].armor  >> character[i].damage >>
                  character[i].coordinateX >> character[i].coordinateY
                 >> character[i].is_life;*/
            int len;
            file.read((char*) &len, sizeof(len));
            character[i].name.resize(len);
            file.read((char*) character[i].name.c_str(), sizeof(len));
            file.read((char*) &character[i].life, sizeof(character[i].life));
            file.read((char*) &character[i].armor, sizeof(character[i].armor));
            file.read((char*) &character[i].damage, sizeof(character[i].damage));
            file.read((char*) &character[i].is_life, sizeof(character[i].is_life));
            file.read((char*) &character[i].coordinateX, sizeof(character[i].coordinateX));
            file.read((char*) &character[i].coordinateY, sizeof(character[i].coordinateY));
        }
        std::cout << "File is load!\n";
        file.close();
    }
    else std::cout << "File is not open!!! load failed!\n";
}

void inputEnemy(Character character[])
{
    for(int i = 0; i < 5; ++i)
    {
        character[i].name = "Enemy # " + std::to_string(i);
        character[i].life = std::rand() % 100 + 50;
        character[i].armor = std::rand() % 50;
        character[i].damage = std::rand() % 15 + 15;
        character[i].coordinateX = std::rand() % maxField_g;
        character[i].coordinateY = std::rand() % maxField_g;

        if (i > 0)
        {
            for (int j = 0; j < i; ++j)
            {
                if((character[i].coordinateX == character[j].coordinateX &&
                        character[i].coordinateY == character[j].coordinateY) ||
                        (character[i].coordinateX == character[PLAYER].coordinateX &&
                         character[i].coordinateY == character[PLAYER].coordinateY))
                {
                    character[i].coordinateX = std::rand() % maxField_g;
                    character[i].coordinateY = std::rand() % maxField_g;
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
    player.coordinateX = 5;
    player.coordinateY = 5;
    return player;
}

void printScreen(Character character[])
{
    char field[40][40]{0}; // игровое поле
    for(int i = 0; i < 6; ++i)
    {
        if (character[i].is_life)
        {
            std::cout << character[i].name << " " << character[i].life << " " << character[i].armor
                      << " " << character[i].damage << " " << " x:"
                      << character[i].coordinateX << " y:" << character[i].coordinateY << std::endl;
        }
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

    for(int j = 0; j < maxField_g; ++j)
    {
        for(int i = 0; i < maxField_g; ++i)
        {
        if(field[i][j] != 'E' && field[i][j] != 'P') field[i][j] = '.';
        std::cout << field[i][j];

        }
        std::cout << std::endl;
    }
}

Character fieldBoundaryCheck(Character &person)
{
    if (person.coordinateX > maxField_g) --person.coordinateX;
    else if (person.coordinateX < 0) ++person.coordinateX;
    if (person.coordinateY > maxField_g) --person.coordinateY;
    else if (person.coordinateY < 0) ++person.coordinateY;

    return person;
}

void attack (Character &whoShoot, Character &whoFall)
{
    std::cout << "ATTENTION!!! ATTACK!!!" << std::endl;
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
        std::cout << whoFall.name << " is dead!!!" << std::endl;
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


    inputPlayer(character[PLAYER]); // вводим данные игрока
    inputEnemy(character); // вводим данные врагов
    printScreen(character); // выводим игровое поле на экран

    std::string turn; // значение хода игрока
    while(true)
    {
        int saveX = character[PLAYER].coordinateX; // сохраняем координаты до хода
        int saveY = character[PLAYER].coordinateY;
        std::cout << "Enter your move: ";
        std::cin >> turn;
        if(turn == "left") --character[PLAYER].coordinateX;
        else if (turn == "right") ++character[PLAYER].coordinateX;
        else if (turn == "up") --character[PLAYER].coordinateY;
        else if (turn == "down") ++character[PLAYER].coordinateY;
        else if (turn == "save") saveGame(character);
        else if (turn == "load") loadGame(character);
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
        printScreen(character);// вывод игрового поля в консоль
    }
}
