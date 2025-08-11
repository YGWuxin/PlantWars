#pragma once

#include <unordered_map>
#include <vector>
#include "Vector2.h"

class Character;
class Camera;

using namespace std;

class CharacterManger
{
public:
    enum class CharacterType
    {
        PeashooterCharacter,
        SunflowerCharacter,
        GloomshroomCharacter,
        NutCharacter,
        Invalid
    };

public:
    static CharacterManger& GetInstance()
    {
        static CharacterManger instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }

    // ɾ���������캯���͸�ֵ�����
    CharacterManger(const CharacterManger&) = delete;
    CharacterManger& operator=(const CharacterManger&) = delete;

    //������ɫ
    Character* create_character(Vector2 position,bool is_render_on_ui = false);

    Character* create_character(Camera* camera,Vector2 position, bool is_render_on_ui = false);

    Character* create_character(CharacterType type, Camera* camera, bool is_render_on_ui = false);

    Character* create_character(CharacterType type, Camera* camera, Vector2 position, bool is_render_on_ui = false);

    //ɾ����ɫ
    void destory_character(Character* character);

private:

private:
    CharacterManger() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��
    ~CharacterManger() = default;

};

