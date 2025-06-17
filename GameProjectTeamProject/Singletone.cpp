#include "Singletone.h"

template<typename T>
inline Singleton<T>::~Singleton() {
	DestroyInst();
}
