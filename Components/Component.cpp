#include "Component.h"


Component::Component(BaseGameObject* owner)
{
	gameObject = owner;
}

void Component::SetIsEnabled(bool isEnabled)
{
	this->isEnabled = isEnabled; 
}
