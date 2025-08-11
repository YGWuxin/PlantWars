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
        static CharacterManger instance; // 静态局部变量，确保唯一性
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    CharacterManger(const CharacterManger&) = delete;
    CharacterManger& operator=(const CharacterManger&) = delete;

    //创建角色
    Character* create_character(Vector2 position,bool is_render_on_ui = false);

    Character* create_character(Camera* camera,Vector2 position, bool is_render_on_ui = false);

    Character* create_character(CharacterType type, Camera* camera, bool is_render_on_ui = false);

    Character* create_character(CharacterType type, Camera* camera, Vector2 position, bool is_render_on_ui = false);

    //删除角色
    void destory_character(Character* character);

private:

private:
    CharacterManger() = default;    // 私有构造函数，防止外部创建实例
    ~CharacterManger() = default;

};

