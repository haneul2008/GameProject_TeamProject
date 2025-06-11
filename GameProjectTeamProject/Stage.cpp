#include<iostream>
#include<string>
#include "Stage.h"
#include "Enums.h"
#include "Console.h"

using std::cout;
using std::endl;

void Stage::Update()
{
	MoveCursor(0, 0);
	RenderStage();
}

int Stage::GetPriotity()
{
	return 10;
}

void Stage::RenderStage()
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if (_curMap[i][j] == (char)Tile::WALL)
				cout << "¡á"; // º®
			else if (_curMap[i][j] == (char)Tile::ROAD)
				cout << "  "; // ±æ
			else if (_curMap[i][j] == (char)Tile::START)
				cout << "¡Ù"; // ½ÃÀÛ Æ÷Å»
			else if (_curMap[i][j] == (char)Tile::GOAL)
				cout << "¢Í"; // ¸ñÇ¥ Æ÷Å»
			else
				continue;
		}

		cout << endl;
	}
}

Stage::Stage()
{
	_curMap = new char[MAP_HEIGHT][MAP_WIDTH];

	//Test
	strcpy_s(_curMap[0], "21111110000000000000");
	strcpy_s(_curMap[1], "00000111111110000000");
	strcpy_s(_curMap[2], "00111100000000000000");
	strcpy_s(_curMap[3], "00000100000000000000");
	strcpy_s(_curMap[4], "00000111111111100000");
	strcpy_s(_curMap[5], "00000100000000100000");
	strcpy_s(_curMap[6], "00000100000000100000");
	strcpy_s(_curMap[7], "00000111111111100000");
	strcpy_s(_curMap[8], "00000100000000100000");
	strcpy_s(_curMap[9], "00000100000000100000");
	strcpy_s(_curMap[10],"00000100000000111100");
	strcpy_s(_curMap[11],"00000100000000000000");
	strcpy_s(_curMap[12],"00000111111111111100");
	strcpy_s(_curMap[13],"00000100000000001103");
	strcpy_s(_curMap[14],"00000100000000001001");
	strcpy_s(_curMap[15],"00000100000000001111");
	strcpy_s(_curMap[16],"00000100000000000000");
	strcpy_s(_curMap[17],"00000100000000000100");
	strcpy_s(_curMap[18],"00000111111111111100");
	strcpy_s(_curMap[19],"00000000000000000000");

	//Test
	SetConsoleSetting(0, 0, true, L"Game");
	ShowCursor(false);
}

Stage::~Stage()
{
	delete[] _curMap;
}
