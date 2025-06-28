#pragma once
#include<Windows.h>
#include<string>

// ����
bool OpenMciDevice(LPCWSTR deviceType, LPCWSTR elementName, UINT& deviceId);
// �ݱ�
void CloseMciDevice(UINT& deviceId);
// ���
void PlayMciDevice(UINT deviceId, bool repeat = false);

enum class SOUNDID
{
    BGM,
	Transition,
	PlayerAttack,
    PlayerHit,
    EnemyDead,
    PlayerDead,
    END
};

struct SoundEntry
{
    //LPCWSTR path;     // ���� ���
    std::wstring path; // ���� ���
    int     volume;  // ���� (0~100)  
    UINT    deviceId; // MCI ��ġ ID (�ʱⰪ 0)
};

// �ʱ�ȭ
bool InitAllSounds();
// ���
void PlaySoundID(SOUNDID _id, bool repeat = false);
// ������ 
void ReleaseAllSounds();