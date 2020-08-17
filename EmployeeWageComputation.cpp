#include <iostream>
#include <time.h>

using namespace std;
int FULL_DAY_HRS = 8;
int PART_TIME_HRS = 4;
int WAGE_PER_HR = 20;
int DAYS_IN_MONTH = 20;
int HRS_PER_MONTH = 100;
int computeWage();

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
    return workHrs * WAGE_PER_HR;
}