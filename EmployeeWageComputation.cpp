#include <iostream>
#include <time.h>

using namespace std;
int FULL_DAY_HRS = 8;
int PART_TIME_HRS = 4;
int WAGE_PER_HR = 20;
int computeWage();

int main(int argc, char const *argv[])
{
    srand(time(0));
    cout << "Employee Wage: " << computeWage() << endl;
    return 0;
}

int computeWage()
{
    int result = rand() % 3;
    switch (result)
    {
    case 1:
        return FULL_DAY_HRS * WAGE_PER_HR;
        break;
    case 2:
        return PART_TIME_HRS * WAGE_PER_HR;
        break;
    default:
        return 0;
        break;
    }
}
