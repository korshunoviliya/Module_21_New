#include <iostream>
#include <string>

struct Bath
{
    double bathArea;
    bool bathPipe{false};
};

struct Rooms
{
    std::string typeRoom{"default"};
    double roomArea;
};

struct Floors
{
    Rooms room[4];
    double ceilingHeight;
    int numberRooms;
};

struct House
{
    double houseArea;
    bool housePipe{false};
    int numberFloors;
    Floors floor[3];
};

struct Village
{
    int lotNumber;
    int totalBuildings;
    House house;
    double garageArea;
    double barnArea;
    Bath bath;
};


int main() {
    int totalPlots;
    std::cout << "How many plots are there in the village?: ";
    std::cin >> totalPlots;
    Village village[totalPlots];

    for(int i = 0; i < totalPlots; ++i)
    {
        std::cout << "input the number of plot: ";
        std::cin >> village[i].lotNumber;
        std::cout << "Input total buildings on plot: ";
        std::cin >> village[i].totalBuildings;

        std::cout << "Is there a garage on the plot?(y/n): ";
        char answer;
        std::cin >> answer;
        if (answer == 'y')
        {
            std::cout << "indicate the area of the garage: ";
            std::cin >> village[i].garageArea;
        }

        std::cout << "Is there a barn on the plot?(y/n): ";
        std::cin >> answer;
        if (answer == 'y')
        {
            std::cout << "indicate the area of the barn: ";
            std::cin >> village[i].barnArea;
        }

        std::cout << "Is there a bath on the plot?(y/n): ";
        std::cin >> answer;
        if (answer == 'y')
        {
            std::cout << "indicate the area of the bath: ";
            std::cin >> village[i].bath.bathArea;
            std::cout << "Does the sauna have a chimney?(y/n): ";
            std::cin >> answer;
            if (answer == 'y') village[i].bath.bathPipe = true;
        }

        std::cout << "Describe the house\n";

        std::cout << "indicate the area of the house: ";
        std::cin >> village[i].house.houseArea;

        std::cout << "Does the house have a chimney?(y/n): ";
        std::cin >> answer;
        if (answer == 'y') village[i].house.housePipe = true;

        std::cout << "Enter the number of floors in the house: ";
        std::cin >> village[i].house.numberFloors;
        for (int j = 0; j < village[i].house.numberFloors; ++j)
        {
            std::cout << "What is the height of the ceilings on the floor: ";
            std::cin >> village[i].house.floor[j].ceilingHeight;
            std::cout << "How many rooms are on the floor #" << j + 1 << ": ";
            std::cin >> village[i].house.floor[j].numberRooms;
            for (int k = 0; k < village[i].house.floor[j].numberRooms; ++k)
            {
                std::cout << "Specify the type of numberRooms: ";
                std::cin >> village[i].house.floor[j].room[k].typeRoom;
                std::cout << "indicate the area of the " << village[i].house.floor[j].room[k].typeRoom << ": ";
                std::cin >> village[i].house.floor[j].room[k].roomArea;
            }
        }
    }
    double totalSquareRoom;
    int totalPipe;
    double totalSquare;

    for(int i = 0; i < totalPlots; ++i)
    {
        totalPipe += village[i].bath.bathPipe + village[i].house.housePipe;
        totalSquare += village[i].house.houseArea;
        std::cout << "Total pipes in the village: " << totalPipe << std::endl;
        std::cout << "The area of all houses in the village: " << totalSquare << std::endl;

        for(int j = 0; j < village[i].house.numberFloors; ++j)
        {   for (int k = 0; k < village[i].house.floor[j].numberRooms; ++k)
            {
                totalSquareRoom += village[i].house.floor[j].room[k].roomArea;
            }
        }
        std::cout << "Total area of all rooms: " <<  totalSquareRoom << std::endl;
    }
    return 0;
}
