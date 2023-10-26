#pragma once

#include <chrono>

class DeltaTime
{
private:
    static std::chrono::steady_clock::time_point _lastTime;
    static std::chrono::steady_clock::time_point _currentTime;

public:
    static float GetDeltaTime();
    static void UpdateDeltaTime();
};