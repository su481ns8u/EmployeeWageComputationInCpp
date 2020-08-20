#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

typedef struct Company;
void computeWage(int noOfEmp, int noOfMonths, Company company);
void writeToFile(string data);

const int FULL_DAY_HRS = 8;
const int PART_TIME_HRS = 4;

typedef struct Company
{
    string name;
    int wagePerHr;
    int workDaysPerMonth;
    int workHrsPerMonth;
};

int main(int argc, char const *argv[])
{
    int noOfEmp, noOfMonths;
    Company company;

    cout << "Enter name of company";
    cin >> company.name;
    cout << "Enter wage per hr for " << company.name << ": ";
    cin >> company.wagePerHr;
    cout << "Enter work days for " << company.name << ": ";
    cin >> company.workDaysPerMonth;
    cout << "Enter work hrs for " << company.name << ": ";
    cin >> company.workHrsPerMonth;
    cout << "Enter number of employees: ";
    cin >> noOfEmp;
    cout << "Enter number of months: ";
    cin >> noOfMonths;

    srand(time(0));
    computeWage(noOfEmp, noOfMonths, company);

    return 0;
}

void computeWage(int noOfEmp, int noOfMonths, Company company)
{
    cout << company.name << " " << company.wagePerHr << " " << company.workDaysPerMonth << " " << company.workHrsPerMonth;
    for (int empNo = 1; empNo <= noOfEmp; empNo++)
    {
        for (int month = 1; month <= noOfMonths; month++)
        {
            int workHrs = 0;
            for (int day = 0; day < company.workDaysPerMonth && workHrs < company.workHrsPerMonth; day++)
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
            int totalWage = workHrs * company.wagePerHr;
            writeToFile(to_string(empNo) + ", " +
                        company.name + ", " +
                        to_string(month) + ", " +
                        to_string(totalWage));
        }
    }
}

void writeToFile(string data)
{
    fstream file;
    file.open("EmpWages.csv", ios::app);
    if (file.is_open())
    {
        file << data << endl;
        file.close();
    }
    else
        cout << "error in opening file";
}
