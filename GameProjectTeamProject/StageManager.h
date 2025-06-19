#pragma once
#include<vector>
#include<Windows.h>
#include"IUpdate.h"
#include"IRender.h"
#include"Singletone.h"
#include"Object.h"

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
}ROOM, * PROOM;

typedef struct _stage
{
	char(*curMap)[MAP_WIDTH];
	COORD startPos;
	COORD endPos;
}STAGE, * PSTAGE;

class RoomRender;

class StageManager : public Singleton<StageManager>, public IUpdate, public IRender
{
public:
	inline void Update() override;
	inline void Render() override;
	int GetUpdatePriotity() override;
	int GetRenderPriotity() override;
	void RenderStage();
public:
	StageManager();
	~StageManager();
	PSTAGE GetStage();
private:
	void CreateMap();
private:
	PSTAGE _stage;
	vector<PROOM> _rooms;
	RoomRender* _roomRender;
};