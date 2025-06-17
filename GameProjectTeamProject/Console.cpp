#include "Console.h"

void SetConsoleSetting(int width, int height, bool isFullScreen, const std::wstring& title) {
    SetConsoleTitle(title.c_str());

    HWND hwnd = GetConsoleWindow(); // HWND = HANDLE WINDOW의 약자
    if (isFullScreen) {
        SetWindowLong(hwnd, GWL_STYLE, WS_POPUP);
        ShowWindow(hwnd, SW_MAXIMIZE); // 풀 스크린으로 설정함
    }
    else {
        LONG style = GetWindowLong(hwnd, GWL_STYLE);
        style &= ~WS_CAPTION; // NAND연산을 통해
        SetWindowLong(hwnd, GWL_STYLE, style);
        MoveWindow(hwnd, 0, 0, width, height, true); // 윈도우 창을 이동시킴
    }
}

void SetLockResize() {
    HWND hwnd = GetConsoleWindow();
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX & ~WS_SIZEBOX;
    SetWindowLong(hwnd, GWL_STYLE, WS_POPUP);
}

COORD GetConsoleResolution() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO buf;

    GetConsoleScreenBufferInfo(handle, &buf);
    short width = buf.srWindow.Right - buf.srWindow.Left + 1;
    short height = buf.srWindow.Bottom - buf.srWindow.Top + 1;
    return COORD { width, height };
}

void MoveCursor(int x, int y) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // GetStandHandle
    COORD cur = { x, y }; // 구조체 생성자로 생성
    SetConsoleCursorPosition(handle, cur); // 콘솔 좌표계는 0,0 에서 아래로 증가 우측으로 증가함
}

BOOL CanMoveCursor(int x, int y) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cur = { x, y };
    return SetConsoleCursorPosition(handle, cur);
}

void SetCursorVisual(bool isVisual, DWORD size) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.dwSize = size; // 1`100의 커서 크기 지정
    curInfo.bVisible = isVisual;
    SetConsoleCursorInfo(handle, &curInfo);

}

COORD GetCursorPosition() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO buf;

    GetConsoleScreenBufferInfo(handle, &buf); // buf에 값을 넣어줌
    return buf.dwCursorPosition;
}

void SetColor(COLOR textColor, COLOR backGroundColor) {
    int textColorIntiger = (int)textColor;
    int backGroundColorIntiger = (int)backGroundColor;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, (backGroundColorIntiger << 4) | textColorIntiger);
}

void FrameSync(unsigned int frame) {
    clock_t oldTime, curTime;
    oldTime = clock();
    while (true) {
        curTime = clock();
        if (curTime - oldTime > 1000 / frame) {
            oldTime = curTime;
            break;
        }
    }
}

void SetConsoleFont(LPCWSTR _fontname, COORD _size, UINT _weight) {
    // 콘솔 핸들
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // 구조체 초기화
    CONSOLE_FONT_INFOEX cf = {};
    cf.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    // 현재 폰트 정보 Get
    GetCurrentConsoleFontEx(handle, false, &cf);
    cf.dwFontSize = _size; // 폭, 높이
    cf.FontWeight = _weight; // FW~
    wcscpy_s(cf.FaceName, _fontname); // 폰트이름 복사
    // 폰트 정보 Set
    SetCurrentConsoleFontEx(handle, false, &cf);
}