#include "TitleInteraction.h"
#include "Console.h"
#include "InputSystem.h"
#include "Enums.h"
#include "Core.h"

TitleInteraction::TitleInteraction(std::vector<Pos> posList) : _posList(), _prevPos(), _selectIdx(0)
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
}

void TitleInteraction::RenderSword()
{
	MoveCursor(_prevPos.x, _prevPos.y);
	std::cout << "         ";

	Pos pos = { _posList[_selectIdx].x - 10, _posList[_selectIdx].y };
	_prevPos = pos;
	MoveCursor(pos.x, pos.y);
	SetColor(COLOR::GRAY);
	std::cout << "={====-";
	SetColor();
}

void TitleInteraction::Interact()
{
	Behavior behavior = (Behavior)_selectIdx;

	switch (behavior)
	{
	case Behavior::GameStart:

		break;
	case Behavior::Description:
		break;
	case Behavior::Quit:
		Core::GetInstance()->QuitGame();
		break;
	default:
		break;
	}
}
