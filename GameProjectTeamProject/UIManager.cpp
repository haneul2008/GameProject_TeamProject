#include "UIManager.h"

#include<string>

#include "UISupporter.h"

constexpr std::string INVEN(int i) { return "INVEN" + std::to_string(i); }

UIManager::UIManager() {
    UISupporter::GetInstance()->setUI(INVEN(1), L"1 :Test");
    UISupporter::GetInstance()->setUI(INVEN(2), L"Test");
}
