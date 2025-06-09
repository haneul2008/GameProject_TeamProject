#pragma once
#define SAFE_DELETE(p) if (_instance != nullptr){delete _instance;_instance = nullptr;}