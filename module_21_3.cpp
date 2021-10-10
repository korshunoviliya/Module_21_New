#include <iostream>
#include <string>
#include <cmath>

struct Vec
{
   double x{0};
   double y{0};

};

void printResult (Vec &total)
{
    std::cout << "Result: (" << total.x << "," << total.y << ")" << std::endl;
}

void inputCoordinateOne(Vec &firstVec)
{
    std::cout << "Enter the coordinates of the vector: ";
    std::cin >> firstVec.x >> firstVec.y;
}

void inputCoordinateTwo(Vec &secondVec)
{
    std::cout << "Enter the coordinates of the second vector: ";
    std::cin >> secondVec.x >> secondVec.y;
}

Vec addVec(Vec &firstVec, Vec &secondVec)
{
    Vec total;
    total.x = firstVec.x + secondVec.x;
    total.y = firstVec.y + secondVec.y;
    return total;
}

 Vec subtractVec(Vec &firstVec, Vec &secondVec)
{
    Vec total;
    total.x =  secondVec.x - firstVec.x;
    total.y = secondVec.y - firstVec.y;
    return total;
}

Vec scaleVec(Vec &firstVec, double scalar)
{
    Vec total;
    total.x = firstVec.x * scalar;
    total.y = firstVec.y * scalar;
    return total;
}

double lengthVec(Vec &firstVec)
{
    return sqrt(pow(firstVec.x,2) + pow(firstVec.y,2));
}

Vec normVec(Vec &firstVec)
{
    Vec total;
    double lenVector = lengthVec(firstVec);
    if (lenVector != 0)
    {
        total.x = firstVec.x / lenVector;
        total.y = firstVec.y / lenVector;
    }
    else
    {
        total.x = 0;
        total.y = 0;
    }
    return total;
}

int main() {

    Vec firstVec;
    Vec secondVec;
    Vec total;

    while(true)
    {
    std::cout << "Adding two vectors - add command." << std::endl;
    std::cout << "Subtracting two vectors is the subtract command." << std::endl;
    std::cout << "Multiplying a vector by a scalar is the scale command." << std::endl;
    std::cout << "Finding the length of a vector is the length command." << std::endl;
    std::cout << "Vector normalization - command normalize." << std::endl;

    std::string command;

        std::cout << "Enter the command: ";
        std::cin >> command;
        if (command == "add")
        {
            inputCoordinateOne(firstVec);
            inputCoordinateTwo(secondVec);
            total = addVec(firstVec, secondVec);
            printResult(total);
        }
        else if (command == "subtract")
        {
            inputCoordinateOne(firstVec);
            inputCoordinateTwo(secondVec);
            total = subtractVec(firstVec, secondVec);
            printResult(total);
        }
        else if (command == "scale")
        {
            inputCoordinateOne(firstVec);
            double scalar;
            std::cout << "Enter the scale: ";
            std::cin >> scalar;
            scaleVec(firstVec, scalar);
            printResult(total);
        }
        else if (command == "length")
        {
            inputCoordinateOne(firstVec);
            std::cout << "The length of the vector is: " << lengthVec(firstVec) << std::endl;
        }
        else if (command == "normalize")
        {
            inputCoordinateOne(firstVec);
            normVec(firstVec);
            printResult(total);
        }
        else if (command == "end")
        {
            std::cout << "See your later!!! Good by!\n";
            return 0;
        }
        else std::cout << "Command is not correct. Try again!!!" << std::endl;
    }
}
