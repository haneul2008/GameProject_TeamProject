#include "Mci.h"
#include<mmsyscom.h>
#include<Digitalv.h>
#include "Console.h"
#include<vector>

// mp3만 볼륨조정 가능
static std::vector<SoundEntry> Sound_Table = {
    {L"Sound\\BGM.mp3", 200, 0},
    {L"Sound\\Transition.mp3", 220, 0},
};

// 오픈
bool OpenMciDevice(LPCWSTR deviceType, LPCWSTR elementName, UINT& deviceId)
{
    MCI_OPEN_PARMS openParams = {};
    openParams.lpstrDeviceType = deviceType; // ex. mpegvideo, waveaudio
    openParams.lpstrElementName = elementName; // 파일 경로(이름)

    if (mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&openParams) != 0)
    {
        // 오류 발생 시 false 반환
        return false;
    }

    deviceId = openParams.wDeviceID; // 할당된 장치 ID 반환
    return true;
}

// 닫기
void CloseMciDevice(UINT& deviceId)
{
    if (deviceId != 0)
    {
        // RAII: 자원 해제
        // C++디자인 패턴 자원을 얻었으면 제거해라
        mciSendCommand(deviceId, MCI_CLOSE, 0, 0);
        deviceId = 0; // 중복 닫기 방지
    }
}

// 재생
void PlayMciDevice(UINT deviceId, bool repeat)
{
    MCI_PLAY_PARMS playParams = {};
    DWORD_PTR playFlags = repeat ? MCI_DGV_PLAY_REPEAT : MCI_NOTIFY; // 0은 기본 재생

    if (repeat == false && deviceId != 0)
        mciSendCommand(deviceId, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)&playParams);

    mciSendCommand(deviceId, MCI_PLAY, playFlags, (DWORD_PTR)&playParams);
}

bool InitAllSounds()
{
    for (auto it = Sound_Table.begin(); it != Sound_Table.end(); ++it)
    {
        // 경로가 비어 있으면 로드하지 않음
        if (it->path.empty())
            continue;

        // 디바이스 종류 판단         // C스타일: wcs1에서 wcs2의 첫번째 표시를 찾는다.
        //LPCWSTR devType = (wcsstr(it->path.c_str(), L".mp3") != NULL) 
        bool isMpeg = it->path.ends_with(L".mp3");
        LPCWSTR devType = isMpeg // C++20: 주어진 부분 문자열로 끝나는지 검사
            ? TEXT("mpegvideo")
            : TEXT("waveaudio");

        // 열기
        if (!OpenMciDevice(devType, it->path.c_str(), it->deviceId))
            return false;

        // 볼륨 설정 mp3만 가능
        if (isMpeg)
        {
            std::wstring volumeCommand = L"setaudio " + it->path +
                L" volume to " + std::to_wstring(it->volume);
            mciSendString(volumeCommand.c_str(), NULL, NULL, NULL);
        }
    }
    return true;
}

void PlaySoundID(SOUNDID id, bool repeat)
{
    // 확인 후 처리
    UINT devId = Sound_Table[(int)id].deviceId;
    if (devId == 0)
        return;
    // 정상 재생
    PlayMciDevice(devId, repeat);
}

void ReleaseAllSounds()
{
    for (auto& sound : Sound_Table)
    {
        CloseMciDevice(sound.deviceId);
    }
}

/*
void test()
{
    mciSendCommand();
    // 1. 디바이스 아이디
    // 2. 명령 메시지
    // => Play, Open, Seek, Pause, Close
    // 3. 플래그
    // => 추가 명령 (Open_ELEMENT, OPEN_TYPE)
    // 4. 추가 주소

    MCI_OPEN_PARMS;
    MCI_PLAY_PARMS;
}*/


