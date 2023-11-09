#pragma once

#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

class ObjectSerializer
{
public:

	ObjectSerializer() = delete;
	~ObjectSerializer() = delete;

    /// <summary>
    /// Example for saving and loading
    /// </summary>
    static void Example();

    template <typename T>
    static void SaveToFile(const T& data, std::string filename)
    {
        std::string completeFilename = "SavedData/" + filename + ".txt";
        std::ofstream file(completeFilename, std::ios::out | std::ios::binary);
        if (!file.is_open()) 
        {
            std::cerr << "Error: Unable to open the file for writing." << std::endl;
            return;
        }

        file << data; // Use stream operator to save the data
        file.close();
    }

    template <typename T>
    static bool LoadFromFile(T& data, std::string filename)
    {


        std::string completeFilename = "SavedData/" + filename + ".txt";
        std::ifstream file(completeFilename, std::ios::in | std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "Error: Unable to open the file for reading." << std::endl;
            return false;
        }

        file >> data; // Use stream operator to load the data
        file.close();

        return true;
    }
};

/// <summary>
/// Example of verload the stream operators for saving and saving
/// </summary>
class MyTestSaveClass 
{

public:
    int money; 
    int gem;
    std::string characterID;

    // Overload the stream operators for saving
    friend std::ostream& operator<<(std::ostream& out, const MyTestSaveClass& obj)
    {
        out << obj.money << " " << obj.gem << " " << obj.characterID;
        return out;
    }

    // Overload the stream operators for loading
    friend std::istream& operator>>(std::istream& in, MyTestSaveClass& obj)
    {
        in >> obj.money >> obj.gem >> obj.characterID;
        return in;
    }
};
