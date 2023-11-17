#pragma once

#include <iostream>
#include <vector>
#include <functional>

template<class T>
class Pool
{
private:

	std::vector<T*> _activePoolObject;
	std::vector<T*> _unactivePoolObjects;
	int _defaultSize;
	std::function <T* ()> _OnCreate;
	std::function <void(T*)> _OnGet;
	std::function <void(T*)> _OnReturn;

public:

	Pool() {};

	Pool(std::function <T* ()> OnCreate, std::function <void(T*)> OnGet, std::function <void(T*)> OnReturn, int defaultSize)
	{
		_OnCreate = OnCreate;
		_OnGet = OnGet;
		_OnReturn = OnReturn;

		_activePoolObject = std::vector<T*>();
		_unactivePoolObjects = std::vector<T*>();

		for (size_t i = 0; i < defaultSize; i++)
		{
			T* newObject = _OnCreate();
			_unactivePoolObjects.push_back(newObject);
		}
	}

	~Pool()
	{
		for (size_t i = 0; i < _activePoolObject.size(); i++)
		{
			delete _activePoolObject[i];
			_activePoolObject[i] = nullptr;
		}
		_activePoolObject.clear();

		for (size_t i = 0; i < _unactivePoolObjects.size(); i++)
		{
			delete _unactivePoolObjects[i];
			_unactivePoolObjects[i] = nullptr;
		}
		_unactivePoolObjects.clear();
	}

	T* Get()
	{
		T* newObject;

		if (_unactivePoolObjects.size() == 0)
		{
			newObject = _OnCreate();
		}
		else
		{
			newObject = _unactivePoolObjects.back();
			_unactivePoolObjects.pop_back();
		}

		_OnGet(newObject);
		_activePoolObject.push_back(newObject);
		return newObject;
	}

	void Return(T* toReturn)
	{
		_OnReturn(toReturn);
		_activePoolObject.erase(find(_activePoolObject.begin(), _activePoolObject.end(), toReturn));
		_unactivePoolObjects.push_back(toReturn);
	}

	bool Contains(std::vector<T*> vector, T* item)
	{
		for (size_t i = 0; i < vector.size(); i++)
		{
			if (vector[i] == item) return true;
		}
		return false;
	}

	std::vector<T*> GetActivePoolObjects()
	{
		return _activePoolObject;
	}

	std::vector<T*> GetInActivePoolObjects()
	{
		return _unactivePoolObjects;
	}
};
