#include "MonoSingletone.h"

template<typename T>
T* MonoSingleton<T>::_instance = nullptr;