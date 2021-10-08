#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct Bill
{
    std::string name;
    std::string date;
    int salary;
};

std::string inputDate()
{
    std::string date;
    while (true) {
        date.clear();
        std::cout << "Input payment date(DD.MM.YYYY): ";
        std::cin >> date;
        bool check = true;
        for (int i = 0; i < date.length() && check; i++){
            if (i == 2 || i == 5){
                date[i] = '.';
                i++;
            }
            if (date[i] >= '0' && date[i] <= '9') check = true;
            else check = false;
        }
        if (check) {
            int day = std::stoi(date.substr(0, 2));
            int month = std::stoi(date.substr(3, 2));
            int year = std::stoi(date.substr(6, 4));

            if (date.length() == 10 && (day > 0 && day <= 31) &&
                (month > 0 && month <= 12) &&
                (year > 1900 && year <= 2021)) return date;
        }
        std::cout << "Input is not correct! Try again!!!\n";
    }
}

void listBill(std::vector <Bill> &bill)
{
    if (bill.empty()) std::cout << "the list is empty" << std::endl;
    for (int i = 0; i < bill.size(); ++i) {
        std::cout << bill[i].name << " " << bill[i].date << " " << bill[i].salary << std::endl;
    }
}

void addBill(std::vector <Bill> &bill)
{
    std::string name_temp;
    std::string data_temp;
    int salary_temp;
    std::cout << "Fill in the statement\n";
    std::cout << "Input the name: ";
    std::cin >> name_temp;
    data_temp = inputDate();
    std::cout << "Enter the payout amount: ";
    std::cin >> salary_temp;
    bill.push_back({name_temp,data_temp,salary_temp});
}

void readBill(std::vector<Bill> &bill)
{
    std::string name_temp = "default";
    std::string data_temp;
    int salary_temp;
    std::ifstream fileBill("..\\bill.txt");
    if (fileBill.is_open())
    {
        while(true)
        {
           fileBill >> name_temp >> data_temp >> salary_temp;
            if (fileBill.eof() || name_temp == "") break;
           bill.push_back({name_temp, data_temp, salary_temp});
        }
        std::cout << "The BILL is load!" << std::endl;
    }
    fileBill.close();
}

void writeBill(std::vector<Bill> &bill)
{
    std::ofstream saveBill("..\\bill.txt", std::ofstream ::trunc);
    if(saveBill.is_open()) {
        for (int i = 0; i < bill.size(); ++i) {
            saveBill << bill[i].name << " " << bill[i].date << " " << bill[i].salary << std::endl;
        }
        std::cout << "The BILL is save!" << std::endl;
    }
    else std::cout << "File is not open!!!\n";
    saveBill.close();
}

int main() {
    std::vector <Bill> bill;
    std::string command;
    do {
        std::cout << "Enter command: list, add, read, write or end: ";
        std::cin >> command;
        if (command == "list") listBill(bill);
            else if (command == "add") addBill(bill);
            else if (command == "read") readBill(bill);
            else if (command == "write") writeBill(bill);
            else if (command == "end")
                {
                    std::cout << "See you later!!!";
                    return 0;
                }
        else std::cout << "The command was entered incorrectly. Please try again" << std::endl;
    }while (true);
}
