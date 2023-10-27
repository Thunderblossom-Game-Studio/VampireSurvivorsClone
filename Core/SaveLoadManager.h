#pragma once

#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

class SaveLoadManager
{
public:

	SaveLoadManager() = delete;
	~SaveLoadManager() = delete;

    void Test();

	static void Save(std::string filePath);

	static void Load(std::string filePath);

    template <typename T>
    void SaveToFile(const T& data, const std::string& filename)
    {
        std::ofstream file(filename, std::ios::out | std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open the file for writing." << std::endl;
            return;
        }

        file << data; // Use stream operator to save the data
        file.close();
    }

    template <typename T>
    bool LoadFromFile(T& data, const std::string& filename)
    {
        std::ifstream file(filename, std::ios::in | std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open the file for reading." << std::endl;
            return false;
        }

        file >> data; // Use stream operator to load the data
        file.close();

        return true;
    }
};

class MyTestSaveClass {
public:
    int x;
    std::string str;

    // Overload the stream operators for saving and loading
    friend std::ostream& operator<<(std::ostream& out, const MyTestSaveClass& obj) {
        out << obj.x << " " << obj.str;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, MyTestSaveClass& obj) {
        in >> obj.x >> obj.str;
        return in;
    }
};
