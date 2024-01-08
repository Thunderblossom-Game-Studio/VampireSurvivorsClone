#pragma once

#include <iostream>

class BaseGameObject;

class Component
{
protected:

	BaseGameObject* gameObject;
	bool isEnabled;

public:

	Component();
	virtual ~Component() = default;

	inline BaseGameObject* GetGameObject() { return gameObject; }
	inline void SetGameObject(BaseGameObject* gameObject) { this->gameObject = gameObject; }
	inline bool GetIsEnabled() { return isEnabled; }
	virtual void SetIsEnabled(bool isEnabled);
};

