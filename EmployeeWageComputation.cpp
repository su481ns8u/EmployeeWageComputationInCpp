#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Company;
void computeWage(Company &company);
void writeToFile(string fileName, list<string> &data, bool isCompFile);
void empWageBuilder(Company company);
void computeWageOfMultiple();
list<vector<string>> readFromFile(string fileName);
void removeSpacesAndCommas(string &str);

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
        return "\n" + this->name + "," +
               to_string(this->wagePerHr) + "," +
               to_string(this->workDaysPerMonth) + "," +
               to_string(this->workHrsPerMonth) + "," +
               to_string(this->totalEmpWage) + "," +
               to_string(this->noOfEmp) + "," +
               to_string(this->noOfMonths);
    }
};

list<Company> companies;

bool comparator(const vector<string> &arg1, const vector<string> &arg2)
{
    return arg1[3] < arg2[3];
}

int main(int argc, char const *argv[])
{
    int noOfEmp, noOfMonths;
    Company company;
    list<vector<string>> companyList;
    int choice;
    while (true)
    {
        cout << "\nEnter your choice: \n1. Add company\n2. Compute Wage and exit\n3. Get Wage by company name\n4. Sort by monthly wage\nChoice: ";
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
        case 3:
            companyList = readFromFile("Companies.csv");
            if (companyList.size() == 0)
                cout << "\nNo companies added !";
            else
            {
                string name;
                cout << "Enter name of company: ";
                cin >> name;
                for (list<vector<string>>::iterator itr = companyList.begin(); itr != companyList.end(); itr++)
                    if ((*itr)[0] == name)
                        cout << "\nTotal wage is " << (*itr)[4];
            }
            companyList.clear();
            return 0;
            break;
        case 4:
            companyList = readFromFile("EmpWages.csv");
            vector<vector<string>> companyVector(companyList.begin(), companyList.end());
            list<string> companyString;
            sort(companyVector.begin(), companyVector.end(), &comparator);
            for (vector<string> comp : companyVector)
                companyString.push_back("\n" + comp[0] + "," + comp[1] + "," + comp[2] + "," + comp[3]);
            writeToFile("SortedEmpWages.csv", companyString, false);
            break;
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
    list<string> str;
    for (companyIterator = companies.begin(); companyIterator != companies.end(); companyIterator++)
    {
        srand(time(0));
        computeWage(*companyIterator);
        str.push_back((*companyIterator).toString());
    }
    writeToFile("Companies.csv", str, false);
    cout << "\nComputed wages for companies and stored in files successfully!";
}

void computeWage(Company &company)
{
    list<string> dailyWages;
    list<string> monthlyWages;
    int totalWorkHrs = 0;
    for (int empNo = 1; empNo <= company.noOfEmp; empNo++)
    {
        for (int month = 1; month <= company.noOfMonths; month++)
        {
            int workHrs = 0;
            int monthlyWage = 0;
            for (int day = 0; day < company.workDaysPerMonth && workHrs < company.workHrsPerMonth; day++)
            {
                int dailyWage = 0;
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
                dailyWage = workHrs * company.wagePerHr;
                monthlyWage += dailyWage;
                dailyWages.push_back("\n" +
                                     to_string(empNo) + "," +
                                     to_string(month) + "," +
                                     to_string(day) + "," +
                                     to_string(dailyWage));
            }
            company.totalEmpWage += monthlyWage;
            monthlyWages.push_back("\n" +
                                   to_string(empNo) + "," +
                                   company.name + "," +
                                   to_string(month) + "," +
                                   to_string(monthlyWage));
        }
    }
    writeToFile(company.name + ".csv", dailyWages, true);
    writeToFile("EmpWages.csv", monthlyWages, false);
}

void writeToFile(string fileName, list<string> &data, bool isCompFile)
{
    fstream file;
    file.open(fileName, ios::app | ios::out);
    if (file.is_open())
    {
        if (isCompFile)
            file << "empNo,month,day,dailyWage";
        list<string>::iterator itr;
        for (itr = data.begin(); itr != data.end(); itr++)
            file << *itr;
        file.close();
    }
    else
        cout << "error in opening file";
}

list<vector<string>> readFromFile(string fileName)
{
    fstream file;
    list<vector<string>> compList;
    file.open(fileName, ios::in);
    if (file.is_open())
    {
        string line, word, temp;
        getline(file, line);
        while (!file.eof())
        {
            vector<string> row;
            getline(file, line);
            stringstream s(line);
            while (getline(s, word, ','))
                row.push_back(word);
            compList.push_back(row);
        }
        file.close();
        return compList;
    }
}

void sortByMonthlyWage()
{
}