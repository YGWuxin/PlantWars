#pragma once


#define MAX_ALIAS_LENGTH            34                  //��ʶ������
#define MAX_SOUNDS                  64                  //ͬʱ���ܲ��ŵ���Ч���������Ϊ����ͨ��

#define AUDIO_VOLUM                 200                 //��Ч������С


class AudioManger
{
public:
    static AudioManger& GetInstance()
    {
        static AudioManger instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }

    typedef struct {
        char alias[32];
        bool isLoop;
    } SoundEffect;                                          //��Ч�ṹ��


    // ɾ���������캯���͸�ֵ�����
    AudioManger(const AudioManger&) = delete;
    AudioManger& operator=(const AudioManger&) = delete;


    const char* PlaySoundAudio(const char* filename, int volume = AUDIO_VOLUM, bool repeat = false);

    const char* PlaySoundAudio(const char* filename, bool repeat = false);

    void StopSound(const char* alias, bool isClear = true);

    void SetVolume(const char* alias, int volume);

    //��ǰ����һЩ�Ƚϳ������֣���֤���Ų���̫��
    void LoadSoundByAlias(const char* filename, const char* alias);

    void PlaySoundByAlias(const char* alias, bool repeat = false);

    void PlaySoundByAlias(const char* alias, int volume, bool repeat = false);

private:
    AudioManger() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��
    ~AudioManger() = default;

    SoundEffect soundEffects[MAX_SOUNDS] = {0};
    int pCurrent = 0;                                       //��Ч����

};

