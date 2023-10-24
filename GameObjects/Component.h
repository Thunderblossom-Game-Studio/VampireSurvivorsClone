#pragma once

#include <iostream>

class BaseGameObject;

class Component
{
protected:

	BaseGameObject* gameObject;
	bool isEnabled;

public:

	Component(BaseGameObject* owner);
	virtual ~Component() = default;

	inline BaseGameObject* GetGameObject() { return gameObject; }
	inline bool GetIsEnabled() { return isEnabled; }
	virtual void SetIsEnabled(bool isEnabled);
};

