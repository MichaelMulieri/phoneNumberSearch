#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

// Function to generate a random phone number with specified area codes
string generatePhoneNumber() {
    vector<string> areaCodes = {"917", "212", "718", "516", "929", "347"};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> areaCodeDist(0, areaCodes.size() - 1);
    uniform_int_distribution<> numberDist(0, 9999999);

    string areaCode = areaCodes[areaCodeDist(gen)];
    string number = to_string(numberDist(gen));
    number = string(7 - number.length(), '0') + number;

    return areaCode + number;
}

int main() {
    ofstream outputFile("phone_numbers.csv");
    if (!outputFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    outputFile << "Phone Number,Times Called" << endl;

    for (int i = 0; i < 50; ++i) {
        string phoneNumber = generatePhoneNumber();
        int timesCalled = rand() % 100 + 1; // Random number of calls between 1 and 100
        outputFile << phoneNumber << "," << timesCalled << endl;
    }

    outputFile.close();
    cout << "CSV file 'phone_numbers.csv' has been created successfully." << endl;

    return 0;
}