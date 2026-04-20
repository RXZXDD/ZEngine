#pragma once

#include <memory>

template<class T>
class TLazySingleton
{
public:
    static T* Get() {
        static std::unique_ptr<T> instance;
        if (!instance)
            instance = std::make_unique<T>();
        return instance.get();
    }
};