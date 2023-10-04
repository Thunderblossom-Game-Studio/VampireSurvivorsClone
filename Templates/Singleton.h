#pragma once

#include <memory>

template<typename T>
class Singleton {
protected:
    struct token {};
    Singleton() {}

public:
    static T& instance();

    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;
};

template<typename T>
T& Singleton<T>::instance()
{
    static const std::unique_ptr<T> instance{new T{token{}}};
    return *instance;
}