#pragma once
#include<iostream>
// using namespace std;를 하면 '모든 std를 사용 하겠다'라, 다른 것과 이름이 같아 충돌될 수도 있다.
using std::cout;
using std::wcout;
using std::endl;

#include<string>
using std::string;
using std::wstring;

#include<Windows.h>

#include<vector>
using std::vector;

void SetConsoleSetting(int width, int height, bool isFullScreen, const std::wstring& title);

void SetLockResize();
COORD GetConsoleResolution();

void MoveCursor(int x, int y);
BOOL CanMoveCursor(int x, int y);

COORD GetCursorPosition();

void SetCursorVisual(bool isVisual, DWORD size);

enum class COLOR
{
    BLACK, BLUE, GREEN, SKYBLUE, RED,
    VOILET, YELLOW, LIGHT_GRAY, GRAY, LIGHT_BLUE,
    LIGHT_GREEN, MINT, LIGHT_RED, LIGHT_VIOLET,
    LIGHT_YELLOW, WHITE, END
};

void SetColor(COLOR textColor = COLOR::WHITE, COLOR backGroundColor = COLOR::BLACK);

void FrameSync(unsigned int frame);
void SetConsoleFont(LPCWSTR _fontname, COORD _size, UINT _weight);