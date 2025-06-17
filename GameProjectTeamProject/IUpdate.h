#pragma once

class IUpdate
{
public:
	inline virtual void Update() abstract;
	virtual int GetUpdatePriotity() abstract; // 높은 순으로 먼저 실행
};