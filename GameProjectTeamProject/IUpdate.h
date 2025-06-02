#pragma once

class IUpdate
{
public:
	virtual void Update() abstract;
	virtual int GetPriotity() abstract; // 높은 순으로 먼저 실행
};