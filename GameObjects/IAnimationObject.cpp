
#include "../Core/DeltaTime.h"
#include "IAnimationObject.h"


//void IAnimationObject::PlayerIdleAnimation()
//{
//		_frames[0] = { 129, 45, 14, 19 };
//		_frames[1] = { 144, 45, 15, 19 };
//		_frames[2] = { 161, 45, 15, 19 };
//		_frames[3] = { 177, 45, 15, 19 };
//
//
//}
//
//IAnimationObject::IAnimationObject(std::vector<SDL_Rect> frames, float animationSpeed, bool loop)
//{
//	this->_frames = frames;
//	this->_animationSpeed = animationSpeed;
//	this->_loop = loop;
//
//}
//
//void IAnimationObject::Animate()
//{
//	while(_isAnimated == true)
//	{
//		
//	}
//}



IAnimationObject::IAnimationObject(std::string texture, std::vector<SDL_Rect> frames, float maxTime, float animationSpeed)
{
	SetTexture(texture, frames[0]);
	_frames = frames;
	_maxTime = maxTime;
	_animationSpeed = animationSpeed;


}

IAnimationObject::~IAnimationObject()
{
}

SDL_Rect IAnimationObject::GetSrc()
{
	_currentTime += DeltaTime::GetDeltaTime() * _animationSpeed;

	if (_currentTime > (_currentImage + 1) * (_maxTime / _frames.size()))
	{
		_currentImage++;
	}

	if (_currentImage >= _frames.size())
	{
		_currentImage = 0;
	}

	if (_currentTime > _maxTime)
	{
		_currentTime = 0;
	}

	return _frames[_currentImage];
}
