#include "Mci.h"
#include<mmsyscom.h>
#include<Digitalv.h>
#include "Console.h"
#include<vector>

// mp3�� �������� ����
static std::vector<SoundEntry> Sound_Table = {
    {L"Sound\\BGM.mp3", 200, 0},
    {L"Sound\\Transition.mp3", 220, 0},
};

// ����
bool OpenMciDevice(LPCWSTR deviceType, LPCWSTR elementName, UINT& deviceId)
{
    MCI_OPEN_PARMS openParams = {};
    openParams.lpstrDeviceType = deviceType; // ex. mpegvideo, waveaudio
    openParams.lpstrElementName = elementName; // ���� ���(�̸�)

    if (mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&openParams) != 0)
    {
        // ���� �߻� �� false ��ȯ
        return false;
    }

    deviceId = openParams.wDeviceID; // �Ҵ�� ��ġ ID ��ȯ
    return true;
}

// �ݱ�
void CloseMciDevice(UINT& deviceId)
{
    if (deviceId != 0)
    {
        // RAII: �ڿ� ����
        // C++������ ���� �ڿ��� ������� �����ض�
        mciSendCommand(deviceId, MCI_CLOSE, 0, 0);
        deviceId = 0; // �ߺ� �ݱ� ����
    }
}

// ���
void PlayMciDevice(UINT deviceId, bool repeat)
{
    MCI_PLAY_PARMS playParams = {};
    DWORD_PTR playFlags = repeat ? MCI_DGV_PLAY_REPEAT : MCI_NOTIFY; // 0�� �⺻ ���

    if (repeat == false && deviceId != 0)
        mciSendCommand(deviceId, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)&playParams);

    mciSendCommand(deviceId, MCI_PLAY, playFlags, (DWORD_PTR)&playParams);
}

bool InitAllSounds()
{
    for (auto it = Sound_Table.begin(); it != Sound_Table.end(); ++it)
    {
        // ��ΰ� ��� ������ �ε����� ����
        if (it->path.empty())
            continue;

        // ����̽� ���� �Ǵ�         // C��Ÿ��: wcs1���� wcs2�� ù��° ǥ�ø� ã�´�.
        //LPCWSTR devType = (wcsstr(it->path.c_str(), L".mp3") != NULL) 
        bool isMpeg = it->path.ends_with(L".mp3");
        LPCWSTR devType = isMpeg // C++20: �־��� �κ� ���ڿ��� �������� �˻�
            ? TEXT("mpegvideo")
            : TEXT("waveaudio");

        // ����
        if (!OpenMciDevice(devType, it->path.c_str(), it->deviceId))
            return false;

        // ���� ���� mp3�� ����
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
    // Ȯ�� �� ó��
    UINT devId = Sound_Table[(int)id].deviceId;
    if (devId == 0)
        return;
    // ���� ���
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
    // 1. ����̽� ���̵�
    // 2. ��� �޽���
    // => Play, Open, Seek, Pause, Close
    // 3. �÷���
    // => �߰� ��� (Open_ELEMENT, OPEN_TYPE)
    // 4. �߰� �ּ�

    MCI_OPEN_PARMS;
    MCI_PLAY_PARMS;
}*/


