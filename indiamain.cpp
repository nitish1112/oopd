#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;
//Financial data as a Fin_Data
struct Fin_Data {
    int year;
    double Interest_Rate;
    double Inflation_Rate;
};

int main() {
    ifstream file("india_data.csv");

    if (!file.is_open()) {
        cout << "Error opening file\n";
        return 1;
    }

    Fin_Data financial_Data[100]; // Assuming a maximum of 100 data entries
    int numDataEntries = 0;

    string line;
    // reading header file
    getline(file,line);
    while (getline(file, line) && numDataEntries < 100) {
        istringstream iss(line);
        char comma;
        int sno;
        if (iss >>sno>>comma>> financial_Data[numDataEntries].year >> comma>>financial_Data[numDataEntries].Interest_Rate >> comma>>financial_Data[numDataEntries].Inflation_Rate) 
        {
            numDataEntries++;
        } else {
            cout << "Error reading line: " << line << "\n";
        }
    }

    // Take user input for investment amount and year of investment
    double investmentAmount;
    int investedYear;

    cout << "Enter investment amount: ";
    cin >> investmentAmount;

    cout << "Enter year of investment: ";
    cin >> investedYear;

    // Search for data corresponding to the invested year
    double Interest_Rate = 0.0;
    double Inflation_Rate = 0.0;
    int index;
    for (int i = 0; i < numDataEntries; ++i) {
        if (financial_Data[i].year == investedYear) {
            index = i;
            Interest_Rate = financial_Data[i].Interest_Rate;
            Inflation_Rate = financial_Data[i].Inflation_Rate;
            break;
        }
    }

    // Calculate received money and value in invested year
    double effectiveRate = 1 + Interest_Rate - Inflation_Rate;
    double receivedMoney = investmentAmount * effectiveRate;

    for(int i=index;i<numDataEntries;i++)
    {
        investmentAmount = investmentAmount*(1.0 + financial_Data[i].Interest_Rate/100.0);
    }
    
    cout<<investmentAmount<<"\n";

    for(int i=numDataEntries-1;i>=index;i--)
    {
        investmentAmount = investmentAmount*(1.0 - financial_Data[i].Inflation_Rate/100.0);
    }
    cout<<investmentAmount<<"\n";
    return 0;
}