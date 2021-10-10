#include <iostream>
#include <string>
#include <vector>

enum TYPE_ROOM
        {
                BEDROOM,
                KITCHEN,
                BATHROOM,
                CHILDREN_ROOM,
                LIVING_ROOM
        };

struct Bath
{
    double bathArea{0};
    bool bathPipe{false};
};

struct Rooms
{
    TYPE_ROOM type_room;
    double roomArea;
};

struct Floors
{
    std::vector <Rooms> room;
    double ceilingHeight;
    int numberRooms;
};

struct House
{
    double houseArea;
    bool housePipe{false};
    int numberFloors;
    std::vector <Floors> floor;
};

struct Village
{
    int lotNumber{0};
    int totalBuildings{0};
    House house;
    double garageArea{0};
    double barnArea{0};
    Bath bath;
};

std::string typeRoom(int tr)
{
    if (tr == BEDROOM) return "bedroom";
    else if (tr == KITCHEN) return "kitchen";
    else if (tr == BATHROOM) return "bathroom";
    else if (tr == CHILDREN_ROOM) return "children`s room";
    else if (tr == LIVING_ROOM) return "living room";
    else return "unknown room type";
}

int main() {
    int totalPlots;
    std::cout << "How many plots are there in the village?: ";
    std::cin >> totalPlots;

    std::vector <Village> village;
    village.resize(totalPlots);

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

        village[i].house.floor.resize(village[i].house.numberFloors);

        for (int j = 0; j < village[i].house.numberFloors; ++j)
        {
            std::cout << "What is the height of the ceilings on the floor: ";
            std::cin >> village[i].house.floor[j].ceilingHeight;
            std::cout << "How many rooms are on the floor #" << j + 1 << ": ";
            std::cin >> village[i].house.floor[j].numberRooms;

            village[i].house.floor[j].room.resize(village[i].house.floor[j].numberRooms);
            
            for (int k = 0; k < village[i].house.floor[j].numberRooms; ++k)
            {
                int t_room;
                std::cout << "Specify the type of rooms: ";
                std::cout << "Input 0 for BEDROOM,\n"
                             "Input 1 for KITCHEN,\n"
                             "Input 2 for BATHROOM,\n"
                             "Input 3 for CHILDREN`s ROOM,\n"
                             "Input 4 for LIVING ROOM\n";
                std::cin >> t_room;
                village[i].house.floor[j].room[k].type_room = (TYPE_ROOM)t_room;
                std::cout << "indicate the area of the " << typeRoom(t_room) << ": ";
                std::cin >> village[i].house.floor[j].room[k].roomArea;
            }
        }
    }
    double totalSquareRoom{0};
    int totalPipe{0};
    double totalSquare{0};

    for(int i = 0; i < totalPlots; ++i)
    {
        totalPipe += village[i].bath.bathPipe + village[i].house.housePipe;
        totalSquare += village[i].house.houseArea;

        for(int j = 0; j < village[i].house.numberFloors; ++j)
        {   for (int k = 0; k < village[i].house.floor[j].numberRooms; ++k)
            {
                totalSquareRoom += village[i].house.floor[j].room[k].roomArea;
            }
        }
    }
    std::cout << "Total pipes in the village: " << totalPipe << std::endl;
    std::cout << "The area of all houses in the village: " << totalSquare << std::endl;
    std::cout << "Total area of all rooms: " <<  totalSquareRoom << std::endl;
    return 0;
}
