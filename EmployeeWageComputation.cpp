#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;
int FULL_DAY_HRS = 8;
int PART_TIME_HRS = 4;
int WAGE_PER_HR = 20;
int DAYS_IN_MONTH = 20;
int HRS_PER_MONTH = 100;
int computeWage();
void writeToFile(string data);

int main(int argc, char const *argv[])
{
    srand(time(0));
    cout << "Employee Wage for a month is: " << computeWage() << endl;
    return 0;
}

int computeWage()
{
    int workHrs = 0;
    for (int day = 0; day < DAYS_IN_MONTH && workHrs < HRS_PER_MONTH; day++)
    {
        int result = rand() % 3;
        switch (result)
        {
        case 1:
            workHrs += FULL_DAY_HRS;
            break;
        case 2:
            workHrs += PART_TIME_HRS;
            break;
        default:
            workHrs += 0;
            break;
        }
    }
    int totalWage = workHrs * WAGE_PER_HR;
    writeToFile("Wage: " + to_string(totalWage));
    return totalWage;
}

void writeToFile(string data)
{
    fstream file;
    file.open("EmpWages.txt", ios::app);
    if (file.is_open())
    {
        file << data << endl;
        file.close();
    }
    else
        cout << "error in opening file";
}