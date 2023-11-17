#pragma once
#include <functional>

class Timer
{
private:

	bool loop;
	bool paused;
	std::function <void()> OnFinished;
	float elapsed;
	float duration;
	bool triggredEvent;

public:

	void SetUp(std::function <void()> _OnFinished,float _duration, bool _loop);
	void Update(float deltaTime);
	void ResetTimer();

	inline float GetDuration() { return duration; }
	inline bool IsLooping() { return loop; }
	inline bool IsPaused() { return paused; }
	inline bool IsFinished() { return elapsed <= 0; }
	inline void PauseTimer() { paused = true; }
	inline void ResumeTimer() { paused = false; }
};

