#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

struct Fin_Data {
    int year;
    double Interest_Rate;
    double Inflation_Rate;
};

int main() {
    ifstream file("spain_data.csv"); // Replace with the actual filename

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
        if (iss >> sno >> comma >> financial_Data[numDataEntries].year >> comma >> financial_Data[numDataEntries].Interest_Rate >> comma >> financial_Data[numDataEntries].Inflation_Rate) {
            numDataEntries++;
        } else {
            cout << "Error reading line: " << line << "\n";
        }
    }

    // Take user input for investment amount and year of investment
    double investment_Amount;
    int invested_Year;

    cout << "Enter investment amount (in Peseta): ";
    cin >> investment_Amount;

    cout << "Enter year of investment: ";
    cin >> invested_Year;

    // Search for data corresponding to the invested year
    double Interest_Rate = 0.0;
    double Inflation_Rate = 0.0;
    int index;
    for (int i = 0; i < numDataEntries; ++i) {
        if (financial_Data[i].year == invested_Year) {
            index = i;
            Interest_Rate = financial_Data[i].Interest_Rate;
            Inflation_Rate = financial_Data[i].Inflation_Rate;
            break;
        }
    }

    // Calculate received money and value in invested year (Peseta)
    double effectiveRate = 1 + Interest_Rate - Inflation_Rate;
    double receivedMoneyPeseta = investment_Amount * effectiveRate;

    // Calculate investment growth considering interest rates and inflation rates
    for (int i = index; i < numDataEntries; i++) {
        investment_Amount *= (1.0 + financial_Data[i].Interest_Rate / 100.0);
    }

    // Calculate value at invested year considering inflation rates
    for (int i = numDataEntries - 1; i >= index; i--) {
        investment_Amount *= (1.0 - financial_Data[i].Inflation_Rate / 100.0);
    }

    // Convert investment amount to Euro after 2002 (1 Euro = 166 Peseta)
    if (invested_Year <= 2002) {
        investment_Amount /= 166.0;
    }

    // Compare the growth rates during dictatorial and republican eras
    double valueGrowthDictatorial = receivedMoneyPeseta;
    double valueGrowthRepublican = receivedMoneyPeseta;

    for (int i = 0; i < numDataEntries; i++) {
        if (financial_Data[i].year <= 1975) {
            valueGrowthDictatorial *= (1.0 + financial_Data[i].Interest_Rate / 100.0);
        } else {
            valueGrowthRepublican *= (1.0 + financial_Data[i].Interest_Rate / 100.0);
        }
    }

    if (valueGrowthDictatorial > valueGrowthRepublican) {
        cout << "Value of money grew faster during the dictatorial era.\n";
    } else if (valueGrowthDictatorial < valueGrowthRepublican) {
        cout << "Value of money grew faster during the republican era.\n";
    } else {
        cout << "Value of money grew at the same rate during both eras.\n";
    }

    // Print the calculated values
    cout << "Investment Value: " << investment_Amount << " Euro (or currency)\n";

    return 0;
}