// 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;


int getSum(long long phoneNumber) {
    int sum = 0;
    while (phoneNumber > 0) {
        sum += phoneNumber % 10;
        phoneNumber /= 10;
    }
    return sum;
    
}

bool checkForMatch(long long userInputPhoneNumber, long long phoneNumber){
    string userInput = to_string(userInputPhoneNumber);
    string csvNumber = to_string(phoneNumber);

    if (userInput.length() != csvNumber.length()) {
        return false;
    }

    for (char userDigit : userInput) {
        if (userDigit != csvNumber[0]) {
            return false;
        }
        csvNumber.erase(0, 1);
    }

    return true;
}

int main() {
    long long userInputPhoneNumber;
    cout << "Enter a phone number (10 digits): ";
    cin >> userInputPhoneNumber;

    int userInputNumberSum = getSum(userInputPhoneNumber);

    // Open the CSV file
    ifstream inputFile("phone_numbers.csv");
    if (!inputFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string line;

    getline(inputFile, line);

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string phoneNumberStr;
        int timesCalled;

        if (getline(iss, phoneNumberStr, ',') && (iss >> timesCalled)){
        long long phoneNumber = stoll(phoneNumberStr);
        int phoneNumberSum = getSum(phoneNumber);
        if (phoneNumberSum == userInputNumberSum) {
            bool isMatch = checkForMatch(userInputPhoneNumber, phoneNumber);
            if (isMatch){
                cout << "Phone number found: " << phoneNumber << endl;
                cout << "It was called " << timesCalled << " times." << endl;
                inputFile.close();
                return 0;
            }
        }
        }
    }
    cout << "Phone number not found." << endl;
    inputFile.close();
    return 0;
    }