#include "Timer.h"
#include <iostream>

void Timer::SetUp(std::function<void()> _OnFinished, float _duration, bool _loop)
{
	elapsed = duration = _duration;
	OnFinished = _OnFinished;
	loop = _loop;
}

void Timer::Update(float deltaTime)
{
	elapsed -= deltaTime;

	if (elapsed <= 0 && !triggredEvent)
	{
		triggredEvent = true;
		if (OnFinished) OnFinished();
	}
}

void Timer::ResetTimer()
{
	triggredEvent = false;
	elapsed = duration;
}