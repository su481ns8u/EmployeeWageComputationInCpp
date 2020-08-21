#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

typedef struct Company;
void computeWage(Company &company);
void writeToFile(string fileName, string data);
void empWageBuilder(Company company);
void computeWageOfMultiple();

const int FULL_DAY_HRS = 8;
const int PART_TIME_HRS = 4;
int companyCounter = 0;

typedef struct Company
{
    string name;
    int wagePerHr;
    int workDaysPerMonth;
    int workHrsPerMonth;
    int totalEmpWage = 0;
    int noOfEmp;
    int noOfMonths;

    string toString()
    {
        return this->name + ", " +
               to_string(this->wagePerHr) + ", " +
               to_string(this->workDaysPerMonth) + ", " +
               to_string(this->workHrsPerMonth) + "," +
               to_string(this->totalEmpWage) + ", " +
               to_string(this->noOfEmp) + ", " +
               to_string(this->noOfMonths);
    }
};

Company companies[5];

int main(int argc, char const *argv[])
{
    int noOfEmp, noOfMonths;
    Company company;
    int choice;
    while (true)
    {
        cout << "Enter your choice: \n1. Add company\n2. Compute Wage\nChoice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter name of company";
            cin >> company.name;
            cout << "Enter wage per hr for " << company.name << ": ";
            cin >> company.wagePerHr;
            cout << "Enter work days for " << company.name << ": ";
            cin >> company.workDaysPerMonth;
            cout << "Enter work hrs for " << company.name << ": ";
            cin >> company.workHrsPerMonth;
            cout << "Enter number of employees: ";
            cin >> company.noOfEmp;
            cout << "Enter number of months: ";
            cin >> company.noOfMonths;
            empWageBuilder(company);
            break;
        case 2:
            computeWageOfMultiple();
            return 0;
            break;
        default:
            cout << "Invalid choice";
            return 0;
        }
    }
}

void empWageBuilder(Company company)
{
    companies[companyCounter++] = company;
}

void computeWageOfMultiple()
{
    for (int i = 0; i < companyCounter; i++)
    {
        srand(time(0));
        computeWage(companies[i]);
    }
    cout << "Computed wages for companies and stored in files successfully!";
}

void computeWage(Company &company)
{
    for (int empNo = 1; empNo <= company.noOfEmp; empNo++)
    {
        for (int month = 1; month <= company.noOfMonths; month++)
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
            company.totalEmpWage += totalWage;
            writeToFile("EmpWages.csv", "\n" + to_string(empNo) + ", " +
                                            company.name + ", " +
                                            to_string(month) + ", " +
                                            to_string(totalWage));
        }
    }
    writeToFile("Companies.csv", "\n" + company.toString());
}

void writeToFile(string fileName, string data)
{
    fstream file;
    file.open(fileName, ios::app);
    if (file.is_open())
    {
        file << data;
        file.close();
    }
    else
        cout << "error in opening file";
}
