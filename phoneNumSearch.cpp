
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

// function to calculate the sum of digits in a phone number
int getSum(long long phoneNumber) {
    int sum = 0;
    while (phoneNumber > 0) {
        // add last digit to the sum and remove it from the number
        sum += phoneNumber % 10;
        phoneNumber /= 10;
    }
    return sum;
    
}
// function to check if a phone number matches the user's input
bool checkForMatch(long long userInputPhoneNumber, long long phoneNumber){
    string userInput = to_string(userInputPhoneNumber);
    string csvNumber = to_string(phoneNumber);

    // check if the lengths are different
    if (userInput.length() != csvNumber.length()) {
        return false;
    }

    // check if all digits match
    for (char userDigit : userInput) {
        if (userDigit != csvNumber[0]) {
            return false;
        }
        csvNumber.erase(0, 1);  // remove the first digit from csvNumber
    }

    return true; // all digits match
}

int main() {
    long long userInputPhoneNumber;
    cout << "Enter a phone number (10 digits): ";
    cin >> userInputPhoneNumber;

    // calculate the sum of digits in the user's input number
    int userInputNumberSum = getSum(userInputPhoneNumber);

    // Open the CSV file
    ifstream inputFile("phone_numbers.csv");
    if (!inputFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string line;

    // skip the header line (csv file format)
    getline(inputFile, line);

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string phoneNumberStr;
        int timesCalled;

        // get the phone number and the number of times it was called from the CSV file
        if (getline(iss, phoneNumberStr, ',') && (iss >> timesCalled)){
        long long phoneNumber = stoll(phoneNumberStr);
        int phoneNumberSum = getSum(phoneNumber);
        // check if the sum of digits in the phone number matches the sum of digits in the user's input number,
        // and if the phone number matches the user's input number itself.  If so, display the phone number and its call count.
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
    // if no match found
    cout << "Phone number not found." << endl;
    inputFile.close();
    return 0;
    }