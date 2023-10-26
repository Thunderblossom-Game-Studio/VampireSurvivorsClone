#include "DeltaTime.h"

std::chrono::steady_clock::time_point DeltaTime::_lastTime = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point DeltaTime::_currentTime = std::chrono::steady_clock::now();

float DeltaTime::GetDeltaTime()
{
    return std::chrono::duration_cast<std::chrono::duration<float>>(_currentTime - _lastTime).count();
}

void DeltaTime::UpdateDeltaTime()
{
    _lastTime = _currentTime;
    _currentTime = std::chrono::steady_clock::now();
}