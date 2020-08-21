#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <iterator>
#include <vector>

using namespace std;

typedef struct Company;
void computeWage(Company &company);
void writeToFile(string fileName, string data);
void empWageBuilder(Company company);
void computeWageOfMultiple();
void mapToFile(map<string, int> dailyWages, string company);
list<Company> readFromFile(string fileName);
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
    list<Company> companyList;
    int choice;
    while (true)
    {
        cout << "Enter your choice: \n1. Add company\n2. Compute Wage\n3. Get Wage by company name\nChoice: ";
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
                cout << "No companies added !";
            else
            {
                string name;
                cout << "Enter name of company: ";
                cin >> name;
                for (list<Company>::iterator itr = companyList.begin(); itr != companyList.end(); itr++)
                    if (company.name == name)
                        cout << "Total wage is " << company.totalEmpWage;
            }
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
    cout << "\nComputed wages for companies and stored in files successfully!";
}

void computeWage(Company &company)
{
    int totalWorkHrs = 0;
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
            cout << totalWage << endl;
            company.totalEmpWage = totalWage;
            cout << company.totalEmpWage;
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
    cout << "\nDaily wages for " + company + " are written to file successfully!" << endl;
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

list<Company> readFromFile(string fileName)
{
    fstream file;
    list<Company> companyList;
    file.open(fileName, ios::in);
    if (file.is_open())
    {
        vector<string> row;
        string line, word, temp;
        getline(file, line);
        while (!file.eof())
        {
            getline(file, line);
            stringstream s(line);
            while (getline(s, word, ','))
            {
                removeSpacesAndCommas(word);
                row.push_back(word);
                if (row.size() > 0)
                {
                    Company company;
                    company.name = row[0];
                    company.wagePerHr = stoi(row[1]);
                    company.workDaysPerMonth = stoi(row[2]);
                    company.workHrsPerMonth = stoi(row[3]);
                    company.totalEmpWage = stoi(row[4]);
                    company.noOfEmp = stoi(row[5]);
                    company.noOfMonths = stoi(row[6]);
                    companyList.push_back(company);
                }
            }
        }
        return companyList;
    }
}

void removeSpacesAndCommas(string &str)
{
    int j = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            continue;
        }
        else
        {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}