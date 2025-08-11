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

    //判断当前的音效是否在循环播放
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
    //如果所有音效均在循环播放中，则不进行音效生成
    if (i >= MAX_SOUNDS)    return NULL;


    // 打开并播放音效，使用定义好的别名
    char command[256];

    LoadSoundByAlias(filename, soundEffects[pCurrent].alias);

    SetVolume(soundEffects[pCurrent].alias, volume);      //对wav不生效

    // 播放音效
    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", soundEffects[pCurrent].alias);     //对wav不生效
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

    //判断当前的音效是否在循环播放
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
    //如果所有音效均在循环播放中，则不进行音效生成
    if (i >= MAX_SOUNDS)    return NULL;


    // 打开并播放音效，使用定义好的别名
    char command[256];

    LoadSoundByAlias(filename, soundEffects[pCurrent].alias);

  //  SetVolume(soundEffects[pCurrent].alias, AUDIO_VOLUM);      //对wav不生效

    // 播放音效
    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", soundEffects[pCurrent].alias);     //对wav不生效
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

    // 检查字符串是否包含特定子字符串
    if (strstr(alias, "audio") != NULL) {
        int number = 0;
        // 提取子字符串后面的部分
        const char* numStr = alias + strlen("audio");
        if (*numStr != '\0') {
            // 将字符串转换为整数
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
    // MCI 音量范围通常在 0 到 1000 之间
    char a[100];
    char command[100];
    sprintf_s(command, sizeof(command), "status %s volume", alias);
    mciSendStringA(command, a, 100, 0);//获取此时的音量数据返回到a，这里的100是表示a的长度，sizeof（a）
    int b = atoi(a);//通过atoi函数进行字符数字串转换到int类型

    sprintf_s(command, "setaudio %s volume to %d", alias, b % 1000 + volume);  //这里建议去取模，此时获得的音量加上volume，再除以1000乘上此时媒体音量就是将要播放出来的音量
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
        snprintf(command, sizeof(command), "play %s repeat", alias);     //对wav不生效
    }
    else {
        snprintf(command, sizeof(command), "play %s", alias);
    }
    mciSendStringA(command, NULL, 0, NULL);
}



void AudioManger::PlaySoundByAlias(const char* alias, int volume, bool repeat)
{
    char command[256];
    SetVolume(alias, volume);      //对wav不生效

    if (repeat) {
        snprintf(command, sizeof(command), "play %s repeat", alias);     //对wav不生效
    }
    else {
        snprintf(command, sizeof(command), "play %s", alias);
    }
    mciSendStringA(command, NULL, 0, NULL);
}





