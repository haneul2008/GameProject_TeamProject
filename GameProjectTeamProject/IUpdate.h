#pragma once

class IUpdate
{
public:
	inline virtual void Update() abstract;
	virtual int GetUpdatePriotity() abstract; // ���� ������ ���� ����
};