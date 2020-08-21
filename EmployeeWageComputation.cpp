#include <iostream>
#include <time.h>
#include <fstream>
#include <list>
#include <map>
#include <iterator>

using namespace std;

typedef struct Company;
void computeWage(Company &company);
void writeToFile(string fileName, string data);
void empWageBuilder(Company company);
void computeWageOfMultiple();
void mapToFile(map<string, int> dailyWages, string company);

const int FULL_DAY_HRS = 8;
const int PART_TIME_HRS = 4;

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

list<Company> companies;

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
    companies.push_back(company);
}

void computeWageOfMultiple()
{
    list<Company>::iterator companyIterator;
    for (companyIterator = companies.begin(); companyIterator != companies.end(); companyIterator++)
    {
        srand(time(0));
        computeWage(*companyIterator);
    }
    cout << "Computed wages for companies and stored in files successfully!";
}

void computeWage(Company &company)
{
    int totalWorkHrs;
    for (int empNo = 1; empNo <= company.noOfEmp; empNo++)
    {
        for (int month = 1; month <= company.noOfMonths; month++)
        {
            int workHrs = 0;
            map<string, int> dailyWages;
            for (int day = 0; day < company.workDaysPerMonth && workHrs < company.workHrsPerMonth; day++)
            {
                int result = rand() % 3;
                switch (result)
                {
                case 1:
                    workHrs = FULL_DAY_HRS;
                    break;
                case 2:
                    workHrs = PART_TIME_HRS;
                    break;
                default:
                    workHrs = 0;
                    break;
                }
                dailyWages.insert(pair<string, int>("\nEmployee Wage for day" + to_string(day) +
                                                        " of emp " + to_string(empNo) +
                                                        " of month " + to_string(month) + " :",
                                                    workHrs * company.wagePerHr));
                totalWorkHrs += workHrs;
            }
            mapToFile(dailyWages, company.name);
            int totalWage = totalWorkHrs * company.wagePerHr;
            company.totalEmpWage += totalWage;
            writeToFile("EmpWages.csv", "\n" + to_string(empNo) + ", " +
                                            company.name + ", " +
                                            to_string(month) + ", " +
                                            to_string(totalWage));
        }
    }
    writeToFile("Companies.csv", "\n" + company.toString());
}

void mapToFile(map<string, int> dailyWages, string company)
{
    map<string, int>::iterator dailyItr;
    for (dailyItr = dailyWages.begin(); dailyItr != dailyWages.end(); dailyItr++)
        writeToFile(company + ".txt", dailyItr->first + " " + to_string(dailyItr->second));
    cout << "\nDaily wages for " + company + " are written to file successfully!";
}

void writeToFile(string fileName, string data)
{
    fstream file;
    file.open(fileName, ios::app | ios::out);
    if (file.is_open())
    {
        file << data;
        file.close();
    }
    else
        cout << "error in opening file";
}
