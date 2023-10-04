#pragma once

#include "../Templates/Singleton.h"
#include <iostream>

class AssetManager final : public Singleton<AssetManager> 
{
private:

public:
    AssetManager(token);
    ~AssetManager();
};