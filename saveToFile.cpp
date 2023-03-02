#include <iostream>
#include <fstream>
#include <cstdlib>

void generateNumbers(int amount, const std::string& location) {
    int module = amount * 50;

    std::ofstream file(location);
    for (int i = 0; i < amount; ++i) {
        file << rand() % module << ",";
    }
    file.close();
}

void readNumbers(int array[], int amount, const std::string& location) {
    std::ifstream file(location);
    int i = 0;

    std::string str;
    while (getline(file, str, ',') && i < amount) {
        array[i] = std::stoi(str);
        i++;
    }

    file.close();
}

void saveNumbers(int array[], int amount, const std::string& location) {
    std::ofstream file(location);
    for (int i = 0; i < amount; ++i) {
        file << array[i] << ",";
    }
    file.close();
}

void printArray(int array[], int amount) {
    std::cout << "Array = ";
    for (int i = 0; i < amount; ++i) {
        std::cout << array[i] << ", ";
    }
    std::cout << "\n";
}
