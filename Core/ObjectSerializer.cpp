#include "ObjectSerializer.h"


void ObjectSerializer::Example()
{
    MyTestSaveClass object_to_save;

    object_to_save.money = 42;
    object_to_save.gem = 100;
    object_to_save.characterID = "Knight";

    SaveToFile(object_to_save, "GameData");

    MyTestSaveClass loaded_object;
    if (LoadFromFile(loaded_object, "GameData"))
    {
        std::cout << "Loaded object: " << loaded_object.money << " " << loaded_object.gem << " " << loaded_object.characterID << std::endl;
    }
    else 
    {
        std::cerr << "Failed to load GameData." << std::endl;
    }

    SaveToFile(1000, "IntData");

    int intData = 0;
    if (LoadFromFile(intData, "IntData"))
    {
        std::cout << "Loaded object: " << intData << std::endl;
    }
    else
    {
        std::cerr << "Failed to load IntData." << std::endl;
    }
}