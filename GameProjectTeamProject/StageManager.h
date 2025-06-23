#pragma once
#include<vector>
#include"IUpdate.h"
#include"IRender.h"
#include"Singletone.h"
#include"Object.h"
#include"Types.h"
#include"Constants.h"
#include"RoomGenerator.h"

using std::vector;

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
	RoomRender* _roomRender;
	RoomGenerator* _roomGenerator;
};