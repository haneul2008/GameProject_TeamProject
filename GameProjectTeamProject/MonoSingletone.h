#pragma once
#include<iostream>
#include"defines.h"

template<typename T>
class MonoSingleton
{
public:
	static T* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new T;
		}
		return _instance;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(_instance);
	}
private:
	static T* _instance;
};

