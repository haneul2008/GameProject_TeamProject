#pragma once
#include<Windows.h>
#include<string>

// 오픈
bool OpenMciDevice(LPCWSTR deviceType, LPCWSTR elementName, UINT& deviceId);
// 닫기
void CloseMciDevice(UINT& deviceId);
// 재생
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
    //LPCWSTR path;     // 파일 경로
    std::wstring path; // 파일 경로
    int     volume;  // 볼륨 (0~100)  
    UINT    deviceId; // MCI 장치 ID (초기값 0)
};

// 초기화
bool InitAllSounds();
// 재생
void PlaySoundID(SOUNDID _id, bool repeat = false);
// 릴리즈 
void ReleaseAllSounds();