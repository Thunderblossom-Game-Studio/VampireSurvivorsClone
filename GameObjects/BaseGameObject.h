#pragma once
#include "../Vector2.h"

class Vector2;

#include <iostream>
#include <vector>

class Component;

class BaseGameObject {
protected:
    BaseGameObject() = default;

    Vector2 _position = { 0, 0 };

public:
    virtual ~BaseGameObject() = default;
	float GetY() const { return _position.y; }
	float GetX() const { return _position.x; }

protected:

	std::vector<Component*> components;

	virtual void Update(float deltaTime) {};
	virtual void LateUpdate(float deltaTime) {};

public:

	template<class T>
	T* AddComponent(T* newCom)
	{
		Component* newComponent = dynamic_cast<Component*>(newCom);

		if (CheckIfComponentExits(newComponent)) std::cout << "Already Exists" << std::endl;
		newComponent->SetGameObject(this);
		components.push_back(newComponent);
		return newCom;
	}

	template<class T>
	T* GetComponent()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			T* component = dynamic_cast<T*>(components[i]);
			if (component != nullptr) return  component;
		}
	}

	template<class T>
	bool TryGetComponent(T*& component)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			component = dynamic_cast<T*>(components[i]);
			if (component != nullptr) return true;
		}
		return false;
	}

	template<class T>
	T* RemoveComponent()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			T* component = dynamic_cast<T*>(components[i]);
			if (component != nullptr)
			{
				components.erase(components.begin() + i);
				return component;
			}
		}
	}

	template<class T>
	static T* Instantiate(T* prefab)
	{
		T* newObject = new T(*prefab);
		return newObject;
	}
};