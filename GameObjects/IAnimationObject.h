#pragma once
#include "IRenderableObject.h"

class IAnimationObject : public IRenderableObject
{
public:
	IAnimationObject();
	IAnimationObject(std::string texture, std::vector<SDL_Rect> frames, float maxTime, float animationSpeed);
	virtual ~IAnimationObject();

	SDL_Rect GetSrc() override;

	
private:
	std::vector<SDL_Rect> _frames; //Array for Animationframes
	int _currentImage = 0; //to get the current frame from the array
	float _currentTime = 0.0f;
	float _maxTime;
	float _animationSpeed;

};

