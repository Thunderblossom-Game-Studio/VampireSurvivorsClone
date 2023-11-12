#include "WorldTime.h"
#include "DeltaTime.h"

std::chrono::steady_clock::time_point WorldTime::_lastTime = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point WorldTime::_currentTime = std::chrono::steady_clock::now();
float WorldTime::_deltaTime = 0.0f;

float WorldTime::GetDeltaTime()
{
    return _deltaTime;
}

void WorldTime::Update()
{
    _lastTime = _currentTime;
    _currentTime = std::chrono::steady_clock::now();
    _deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(_currentTime - _lastTime).count();
	UpdateActiveTimers();
}

void WorldTime::UpdateActiveTimers()
{
	for (auto timer : activeTimers)
	{
		if (!timer->IsPaused())
		{
			timer->Update(_deltaTime);

			if (timer->IsFinished())
			{
				if (timer->IsLooping())
				{
					timer->ResetTimer();
				}
				else
				{
					StopTimer(timer);
				}
			}
		}
	}
}

void WorldTime::StartTimer(Timer* timer, std::function<void()> OnFinished, float duration, bool loop)
{
    if (!IsTimerRunning(timer))
    {
        timer->SetUp(OnFinished, duration, loop);
        activeTimers.push_back(timer);
    }
}

void WorldTime::PauseTimer(Timer* timer)
{
	timer->PauseTimer();
}

void WorldTime::ResumeTimer(Timer* timer)
{
	timer->ResumeTimer();
}

void WorldTime::StopTimer(Timer* timer)
{
	activeTimers.erase(find(activeTimers.begin(), activeTimers.end(), timer));
}

bool WorldTime::IsTimerRunning(Timer* timer)
{
	return find(activeTimers.begin(), activeTimers.end(), timer) != activeTimers.end();
}