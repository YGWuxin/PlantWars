#include "AudioManger.h"
#include <cstdio>
#include <windows.h>
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib") 


const char* AudioManger::PlaySoundAudio(const char* filename,int volume, bool repeat)
{

    static bool initialized = FALSE;

    if (!initialized) {
        for (int i = 0; i < MAX_SOUNDS; i++)
        {
            snprintf(soundEffects[i].alias, sizeof(soundEffects[i].alias), "audio%d", i);
        }
        initialized = TRUE;
    }

    //�жϵ�ǰ����Ч�Ƿ���ѭ������
    int i;
    for (i = 0; i < MAX_SOUNDS; i++)
    {
        if (!soundEffects[pCurrent].isLoop) {
            break;
        }
        pCurrent++;
        if (pCurrent >= MAX_SOUNDS) {
            pCurrent = 0;
        }
    }
    //���������Ч����ѭ�������У��򲻽�����Ч����
    if (i >= MAX_SOUNDS)    return NULL;


    // �򿪲�������Ч��ʹ�ö���õı���
    char command[256];

    LoadSoundByAlias(filename, soundEffects[pCurrent].alias);

    SetVolume(soundEffects[pCurrent].alias, volume);      //��wav����Ч

    // ������Ч
    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", soundEffects[pCurrent].alias);     //��wav����Ч
    }
    else {
        snprintf(command, sizeof(command), "play %s", soundEffects[pCurrent].alias);
    }
    mciSendStringA(command, NULL, 0, NULL);

    soundEffects[pCurrent].isLoop = repeat;
    int index = pCurrent;
    pCurrent = (pCurrent + 1) % MAX_SOUNDS;

    return soundEffects[index].alias;

}


const char* AudioManger::PlaySoundAudio(const char* filename, bool repeat)
{

    static bool initialized = FALSE;

    if (!initialized) {
        for (int i = 0; i < MAX_SOUNDS; i++)
        {
            snprintf(soundEffects[i].alias, sizeof(soundEffects[i].alias), "audio%d", i);
        }
        initialized = TRUE;
    }

    //�жϵ�ǰ����Ч�Ƿ���ѭ������
    int i;
    for (i = 0; i < MAX_SOUNDS; i++)
    {
        if (!soundEffects[pCurrent].isLoop) {
            break;
        }
        pCurrent++;
        if (pCurrent >= MAX_SOUNDS) {
            pCurrent = 0;
        }
    }
    //���������Ч����ѭ�������У��򲻽�����Ч����
    if (i >= MAX_SOUNDS)    return NULL;


    // �򿪲�������Ч��ʹ�ö���õı���
    char command[256];

    LoadSoundByAlias(filename, soundEffects[pCurrent].alias);

  //  SetVolume(soundEffects[pCurrent].alias, AUDIO_VOLUM);      //��wav����Ч

    // ������Ч
    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", soundEffects[pCurrent].alias);     //��wav����Ч
    }
    else {
        snprintf(command, sizeof(command), "play %s", soundEffects[pCurrent].alias);
    }
    mciSendStringA(command, NULL, 0, NULL);

    soundEffects[pCurrent].isLoop = repeat;
    int index = pCurrent;
    pCurrent = (pCurrent + 1) % MAX_SOUNDS;

    return soundEffects[index].alias;

}


void AudioManger::StopSound(const char* alias,bool isClear)
{
    char command[256];

    // ����ַ����Ƿ�����ض����ַ���
    if (strstr(alias, "audio") != NULL) {
        int number = 0;
        // ��ȡ���ַ�������Ĳ���
        const char* numStr = alias + strlen("audio");
        if (*numStr != '\0') {
            // ���ַ���ת��Ϊ����
            number = atoi(numStr);
            if (soundEffects[number].isLoop)
                soundEffects[number].isLoop = false;
        }
    }

    snprintf(command, sizeof(command), "stop %s", alias);
    mciSendStringA(command, NULL, 0, NULL);

    if (isClear)
    {
        snprintf(command, sizeof(command), "close %s", alias);
        printf("%s\r\n", command);
        mciSendStringA(command, NULL, 0, NULL);
    }

}


void AudioManger::SetVolume(const char* alias, int volume)
{
    // MCI ������Χͨ���� 0 �� 1000 ֮��
    char a[100];
    char command[100];
    sprintf_s(command, sizeof(command), "status %s volume", alias);
    mciSendStringA(command, a, 100, 0);//��ȡ��ʱ���������ݷ��ص�a�������100�Ǳ�ʾa�ĳ��ȣ�sizeof��a��
    int b = atoi(a);//ͨ��atoi���������ַ����ִ�ת����int����

    sprintf_s(command, "setaudio %s volume to %d", alias, b % 1000 + volume);  //���ｨ��ȥȡģ����ʱ��õ���������volume���ٳ���1000���ϴ�ʱý���������ǽ�Ҫ���ų���������
    mciSendStringA(command, 0, 0, 0);
}


void AudioManger::LoadSoundByAlias(const char* filename, const char* alias)
{
    char command[256];

    snprintf(command, sizeof(command), "stop %s", alias);
    mciSendStringA(command, NULL, 0, NULL);

    snprintf(command, sizeof(command), "close %s", alias);
    mciSendStringA(command, NULL, 0, NULL);

    snprintf(command, sizeof(command), "open %s alias %s", filename, alias);
    MCIERROR ret = mciSendStringA(command, NULL, 0, NULL);
    if (ret != 0)
    {
        TCHAR err[100] = { 0 };
        mciGetErrorString(ret, err, sizeof(err));
        printf("[open]:%s\r\n", err);
    }
}


void AudioManger::PlaySoundByAlias(const char* alias, bool repeat)
{
    char command[256];
    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", alias);     //��wav����Ч
    }
    else {
        snprintf(command, sizeof(command), "play %s", alias);
    }
    mciSendStringA(command, NULL, 0, NULL);
}



void AudioManger::PlaySoundByAlias(const char* alias, int volume, bool repeat)
{
    char command[256];
    SetVolume(alias, volume);      //��wav����Ч

    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", alias);     //��wav����Ч
    }
    else {
        snprintf(command, sizeof(command), "play %s", alias);
    }
    mciSendStringA(command, NULL, 0, NULL);
}





