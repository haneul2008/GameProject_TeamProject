#include "Console.h"

void SetConsoleSetting(int width, int height, bool isFullScreen, const std::wstring& title) {
    SetConsoleTitle(title.c_str());

    HWND hwnd = GetConsoleWindow(); // HWND = HANDLE WINDOW�� ����
    if (isFullScreen) {
        SetWindowLong(hwnd, GWL_STYLE, WS_POPUP);
        ShowWindow(hwnd, SW_MAXIMIZE); // Ǯ ��ũ������ ������
    }
    else {
        LONG style = GetWindowLong(hwnd, GWL_STYLE);
        style &= ~WS_CAPTION; // NAND������ ����
        SetWindowLong(hwnd, GWL_STYLE, style);
        MoveWindow(hwnd, 0, 0, width, height, true); // ������ â�� �̵���Ŵ
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
    COORD cur = { x, y }; // ����ü �����ڷ� ����
    SetConsoleCursorPosition(handle, cur); // �ܼ� ��ǥ��� 0,0 ���� �Ʒ��� ���� �������� ������
}

BOOL CanMoveCursor(int x, int y) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cur = { x, y };
    return SetConsoleCursorPosition(handle, cur);
}

void SetCursorVisual(bool isVisual, DWORD size) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.dwSize = size; // 1`100�� Ŀ�� ũ�� ����
    curInfo.bVisible = isVisual;
    SetConsoleCursorInfo(handle, &curInfo);

}

COORD GetCursorPosition() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO buf;

    GetConsoleScreenBufferInfo(handle, &buf); // buf�� ���� �־���
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
    // �ܼ� �ڵ�
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // ����ü �ʱ�ȭ
    CONSOLE_FONT_INFOEX cf = {};
    cf.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    // ���� ��Ʈ ���� Get
    GetCurrentConsoleFontEx(handle, false, &cf);
    cf.dwFontSize = _size; // ��, ����
    cf.FontWeight = _weight; // FW~
    wcscpy_s(cf.FaceName, _fontname); // ��Ʈ�̸� ����
    // ��Ʈ ���� Set
    SetCurrentConsoleFontEx(handle, false, &cf);
}