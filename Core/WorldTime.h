#pragma once
#include <chrono>
#include "Timer.h"
#include "PoolSystem.h"

class WorldTime
{

private:

    static std::chrono::steady_clock::time_point _lastTime;
    static std::chrono::steady_clock::time_point _currentTime;
    static float _deltaTime;
    static std::vector<Timer*> activeTimers;

    WorldTime() = delete;
    ~WorldTime() = delete;

    static void UpdateActiveTimers();

public:

    static float GetDeltaTime();
    static void Update();

    static void StartTimer(Timer* timer, std::function <void()> OnFinished, float duration, bool loop);
    static void PauseTimer(Timer* timer);
    static void ResumeTimer(Timer* timer);
    static void StopTimer(Timer* timer);
    static bool IsTimerRunning(Timer* timer);
};

