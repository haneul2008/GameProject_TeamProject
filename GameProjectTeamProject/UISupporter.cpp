#include "UISupporter.h"

#include<io.h>  
#include<fcntl.h>
#include <Windows.h>

#include "Console.h"
#include "Core.h"

UISupporter::UISupporter() {
    Core::GetInstance()->AddRender(this);
}

UISupporter::~UISupporter() {
    Core::GetInstance()->RemoveRender(this);
}

void UISupporter::Render() {
    int coutMode = _setmode(_fileno(stdout), _O_U16TEXT);
    SetColor();

    for (const std::pair<std::string, UIInfo>& pair : _uis) {
        MoveCursor(pair.second.x, pair.second.y);
        std::wcout << pair.second.value;
    }

    int wcoutMode = _setmode(_fileno(stdout), coutMode);
}

int UISupporter::GetRenderPriotity() {
    // 항상 마지막에 실행 시켜야함
    return -10e8;
}

void UISupporter::setUI(const std::string& key, const std::wstring& value) {
    removeUIPosition(key);
    getUI(key)->value = value;
}

void UISupporter::setUI(const std::string& key, int x, int y) {
    removeUIPosition(key);

    UIInfo* uiInfo = getUI(key);
    uiInfo->x = x;
    uiInfo->y = y;
}

void UISupporter::removeUI(const std::string& key) {
    removeUIPosition(key);
    _uis.erase(key);
}

void UISupporter::removeUIPosition(const std::string& key) {
    UIInfo* info = getUI(key);
    MoveCursor(info->x, info->y);
    for (int i = 0; i < info->value.size(); ++i)
        std::cout << "  ";
}

UIInfo* UISupporter::getUI(const std::string& key) {
    if (!_uis.contains(key))
        _uis[key] = UIInfo();

    return &_uis[key];
}

void pauseToWaitKeyAndPrint(Key key, std::wstring printComment, int x, int y, unsigned int waitFrame) {
    MoveCursor(x, y);

    int coutMode = _setmode(_fileno(stdout), _O_U16TEXT);
    std::wcout << printComment;
    int wcoutMode = _setmode(_fileno(stdout), coutMode);

    pauseToWaitInputKey(key);

    MoveCursor(x, y);
    for (int i = 0; i < printComment.size(); ++i)
        std::cout << "  ";
}

// 현재 인코딩을 UTF-16으로 면환하는 함수. 주의 string이 반드시 UTF-8이여야함. // 비쥬얼 스튜디오가 CP_949라서 UTF-8을 못씀 CP_949를 기본값으로 함
std::wstring to_wstring(const std::string& str, int incode) {
    // 비어있으면 공백 반환
    if (str.empty())
        return L"";

    // multibyte = 문자를 여러 바이트로 표현 ASCII로 표현되면 1개..등
    // multibyte문자열을 UTF-8로 변환 해 주는 Windows함수.
    int size_needed = MultiByteToWideChar(incode, 0, str.c_str(), -1, nullptr, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(incode, 0, str.c_str(), -1, &wstr[0], size_needed);

    // 제거된 null 문자 포함될 수 있음
    wstr.pop_back(); // 제거

    return wstr;
}