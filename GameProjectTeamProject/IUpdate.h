#pragma once

class IUpdate
{
public:
	virtual void Update() abstract;
	virtual int GetPriotity() abstract; // ���� ������ ���� ����
};