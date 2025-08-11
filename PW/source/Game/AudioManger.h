#pragma once


#define MAX_ALIAS_LENGTH            34                  //标识符长度
#define MAX_SOUNDS                  64                  //同时所能播放的音效，可以理解为播放通道

#define AUDIO_VOLUM                 200                 //音效音量大小


class AudioManger
{
public:
    static AudioManger& GetInstance()
    {
        static AudioManger instance; // 静态局部变量，确保唯一性
        return instance;
    }

    typedef struct {
        char alias[32];
        bool isLoop;
    } SoundEffect;                                          //音效结构体


    // 删除拷贝构造函数和赋值运算符
    AudioManger(const AudioManger&) = delete;
    AudioManger& operator=(const AudioManger&) = delete;


    const char* PlaySoundAudio(const char* filename, int volume = AUDIO_VOLUM, bool repeat = false);

    const char* PlaySoundAudio(const char* filename, bool repeat = false);

    void StopSound(const char* alias, bool isClear = true);

    void SetVolume(const char* alias, int volume);

    //提前加载一些比较长的音乐，保证播放不会太慢
    void LoadSoundByAlias(const char* filename, const char* alias);

    void PlaySoundByAlias(const char* alias, bool repeat = false);

    void PlaySoundByAlias(const char* alias, int volume, bool repeat = false);

private:
    AudioManger() = default;    // 私有构造函数，防止外部创建实例
    ~AudioManger() = default;

    SoundEffect soundEffects[MAX_SOUNDS] = {0};
    int pCurrent = 0;                                       //音效索引

};

