#include "GameTimer.h"

void GameTimer::AddEvent(int time, std::function<void()> action)
{
	timedEvents.push_back( new TimedEvent(time, action) );
}

void GameTimer::Update(float deltaTime)
{
	currentTime += deltaTime;

	for (auto& timedEvent : timedEvents)
	{
		if (currentTime >= timedEvent->GetTime())
		{
			timedEvent->Execute();
			completedEvents.push_back(timedEvent);
			timedEvents.erase(std::remove(timedEvents.begin(), timedEvents.end(), timedEvent), timedEvents.end());
			//std::cout << "timedEvents size: " << timedEvents.size() << std::endl;
		}

		//std::cout << "currentTime: " << currentTime << std::endl;
	}

	for (auto& completedEvent : completedEvents)
	{
		delete completedEvent;
		completedEvent = nullptr;
	}
}

std::string GameTimer::GetTime()
{
	int minutes = (int)currentTime / 60;
	int seconds = (int)currentTime % 60;
	std::string time = std::to_string(minutes) +"m" + ":" + std::to_string(seconds) + "s";
	return time;
}
