#include "TitleInteraction.h"
#include "Console.h"
#include "InputSystem.h"
#include "Enums.h"
#include "Core.h"
#include "SceneManager.h"
#include "Transition.h"

TitleInteraction::TitleInteraction(std::vector<Pos> posList) : _posList(), _prevPosPair(), _selectIdx(0)
{
	_posList = std::move(posList);

	RenderSword();
}

void TitleInteraction::Update()
{
	Key key = InputManager::GetInstance()->getKey();

	switch (key)
	{
	case Key::UP:
		--_selectIdx;
		if (_selectIdx < 0) _selectIdx = _posList.size() - 1;

		RenderSword();
		break;
	case Key::DOWN:
		_selectIdx = (_selectIdx + 1) % _posList.size();

		RenderSword();
		break;
	case Key::READYINPUT:
		Interact();
	}

	FrameSync(10);
}

void TitleInteraction::RenderSword()
{
	MoveCursor(_prevPosPair.first.x, _prevPosPair.first.y);
	std::cout << "       ";
	MoveCursor(_prevPosPair.second.x, _prevPosPair.second.y);
	std::cout << "       ";

	int moveX = 10;

	Pos pos = { _posList[_selectIdx].x, _posList[_selectIdx].y };
	Pos leftPos = { pos.x - moveX, pos.y };
	_prevPosPair.first = leftPos;
	MoveCursor(leftPos.x, leftPos.y);
	SetColor(COLOR::GRAY);
	std::cout << "={====-";

	Pos rightPos = { pos.x + moveX + 2, pos.y };
	_prevPosPair.second = rightPos;
	MoveCursor(rightPos.x, rightPos.y);
	std::cout << "-====}=";
	SetColor();
}

void TitleInteraction::Interact()
{
	Behavior behavior = (Behavior)_selectIdx;

	switch (behavior)
	{
	case Behavior::GameStart:
		Transition();
		SceneManager::GetInstance()->ChangeScene("GAME");
		break;
	case Behavior::Description:
		Transition();
		SceneManager::GetInstance()->ChangeScene("DESC");
		break;
	case Behavior::Quit:
		Core::GetInstance()->QuitGame();
		break;
	default:
		break;
	}
}
