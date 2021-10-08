#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

struct Vec
{
   double x;
   double y;

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

double inputScal()
{
    double scal;
    std::cout << "Enter the scale: ";
    std::cin >> scal;
    return scal;
}

void addVec()
{
    Vec firstVec;
    Vec secondVec;
    Vec total;
    inputCoordinateOne(firstVec);
    inputCoordinateTwo(secondVec);
    total.x = firstVec.x + secondVec.x;
    total.y = firstVec.y + secondVec.y;
    printResult(total);
}

void subtractVec()
{
    Vec firstVec;
    Vec secondVec;
    Vec total;
    inputCoordinateOne(firstVec);
    inputCoordinateTwo(secondVec);
    total.x =  secondVec.x - firstVec.x;
    total.y = secondVec.y - firstVec.y;
    printResult(total);

}

void scaleVec()
{
    Vec firstVec;
    Vec total;
    inputCoordinateOne(firstVec);
    double scal = inputScal();
    total.x = firstVec.x * scal;
    total.y = firstVec.y * scal;
    printResult(total);
}

double lenghtVec(Vec &firstVec)
{
    double lenVector = sqrt(pow(firstVec.x,2) + pow(firstVec.y,2));
    std::setprecision(5);
    std::cout << "The vector length: " << lenVector << std::endl;
    return lenVector;
}

void normVec()
{
    Vec firstVec;
    Vec total;
    inputCoordinateOne(firstVec);
    double lenVector = lenghtVec(firstVec);
    if (lenVector != 0)
    {
        total.x = firstVec.x / lenVector;
        total.y = firstVec.y / lenVector;
        std::cout << total.x << "\t" << firstVec.x << "\t" << lenVector << std::endl;
        printResult(total);
    }
    else
    {
        std::cout << " Length vector is NULL\n";
    }
}
int main() {
    std::cout << 2 / 2.82843;
   while(true)
    {
    std::cout << "Adding two vectors - add command." << std::endl;
    std::cout << "Subtracting two vectors is the subtract command." << std::endl;
    std::cout << "Multiplying a vector by a scalar is the scale command." << std::endl;
    std::cout << "Finding the length of a vector is the length command." << std::endl;
    std::cout << "Vector normalization - command normalize." << std::endl;

    std::string command;
        Vec firstVec;
        std::cout << "Enter the command: ";
        std::cin >> command;
        if (command == "add") addVec();
        else if (command == "subtract") subtractVec();
        else if (command == "scale") scaleVec();
        else if (command == "length")
        {
            inputCoordinateOne(firstVec);
            lenghtVec(firstVec);
        }
        else if (command == "normalize") normVec();
        else if (command == "end") return 0;
        else std::cout << "Command is not correct. Try again!!!" << std::endl;
    }
}
