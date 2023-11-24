#pragma once

#include <functional>
#include <chrono>
#include <vector>
#include <string>
#include <iostream> 

class TimedEvent
{
	std::function <void()> action;
	float time;

public:

	TimedEvent(int time, std::function <void()> action) : time(time), action(action){}	
	inline float GetTime() { return time; }
	inline void Execute() {action(); }
};

class GameTimer
{
private:

		std::vector<TimedEvent*> timedEvents;
		std::vector<TimedEvent*> completedEvents;
		float currentTime = 0.0f;

public:
		GameTimer() = default;
		~GameTimer() = default;
		void AddEvent(int time, std::function <void()> action);
		void Update(float deltaTime);
		std::string GetTime();
};

