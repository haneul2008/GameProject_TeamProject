#pragma once

#include <unordered_map>
#include <string>

#include "Singletone.h"
#include "IRender.h"
#include "InputSystem.h"

struct UIInfo
{
    int x;
    int y;
    std::wstring value;
};

class UISupporter : public Singleton<UISupporter>, public IRender
{
public:
    UISupporter();
    ~UISupporter() override;

public:
    // IRender을(를) 통해 상속됨
    void Render() override;
    int GetRenderPriotity() override;

    void setUI(const std::string& key, const std::wstring& value);
    void setUI(const std::string& key, int x, int y);
    void removeUI(const std::string& key);
    void deleteUI();

private:
    void removeUIPosition(const std::string& key);
    UIInfo* getUI(const std::string& key);

private:
    std::unordered_map<std::string, UIInfo> _uis;
};

void pauseToWaitKeyAndPrint(Key key, std::wstring printComment, int x = 0, int y = 0, unsigned int waitFrame = 15);
std::wstring to_wstring(const std::string& str, int incode = 949);
