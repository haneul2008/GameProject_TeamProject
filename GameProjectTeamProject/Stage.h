#pragma once
#include<vector>
#include<Windows.h>
#include"IUpdate.h"

using std::vector;

const int MAP_WIDTH = 111;
const int MAP_HEIGHT = 60;
const int MAX_ROOM = 8;
const int MAX_ROOM_WIDTH = 12;
const int MAX_ROOM_HEIGHT = 9;
const int MIN_ROOM_WIDTH = 6;
const int MIN_ROOM_HEIGHT = 6;
const int ROOM_MINDISTANCE = 4;

typedef struct _room
{
	int x;
	int y;
	int width, height;

	COORD GetCenter() const {
		return {
			static_cast<SHORT>(x + width / 2),
			static_cast<SHORT>(y + height / 2)
		};
	}

	bool IsOverlap(const _room& other) const {
		bool noOverlapX = (x < other.x + other.width + ROOM_MINDISTANCE) &&
			(other.x < x + width + ROOM_MINDISTANCE);

		bool noOverlapY = (y < other.y + other.height + ROOM_MINDISTANCE) &&
			(other.y < y + height + ROOM_MINDISTANCE);

		return noOverlapX && noOverlapY;
	}
}ROOM, *PROOM;

typedef struct _stage
{
	char(*curMap)[MAP_WIDTH];
	COORD startPos;
}STAGE, *PSTAGE;

class RoomRender;

class Stage : public IUpdate
{
public:
	inline void Update() override;
	int GetPriotity() override;
	void RenderStage();
public:
	Stage();
	~Stage();
	PSTAGE GetStage();
private:
	void CreateMap();
private:
	PSTAGE _stage;
	vector<PROOM> _rooms;
	RoomRender* _roomRender;
};