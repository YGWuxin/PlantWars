#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <graphics.h>	


using namespace std;

class Controller;

class PlayerControllerManger
{
public:
    enum class PlayerType
    {
        None,
        Player_P1,
        Player_P2
    };

public:
    static PlayerControllerManger& GetInstance()
    {
        static PlayerControllerManger instance; // 静态局部变量，确保唯一性
        return instance;
    }

    //创建指定玩家
    void create_player(const PlayerType& type);

    //清除指定玩家
    void clear_player(const PlayerType& type)
    {
        if (player_list[type])
            player_list.erase(type);
    };

    //获取玩家控制器
    Controller* get_player(const PlayerType& type) {return player_list[type];};

    //更新角色管理器中的所有玩家输入更新
    void on_input(const ExMessage& msg);

    // 删除拷贝构造函数和赋值运算符
    PlayerControllerManger(const PlayerControllerManger&) = delete;
    PlayerControllerManger& operator=(const PlayerControllerManger&) = delete;

private:
    unordered_map<PlayerType,Controller*>  player_list;

private:
    PlayerControllerManger() = default;    // 私有构造函数，防止外部创建实例
    ~PlayerControllerManger() = default;


};

