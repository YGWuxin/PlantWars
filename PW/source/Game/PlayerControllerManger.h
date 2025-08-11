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
        static PlayerControllerManger instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }

    //����ָ�����
    void create_player(const PlayerType& type);

    //���ָ�����
    void clear_player(const PlayerType& type)
    {
        if (player_list[type])
            player_list.erase(type);
    };

    //��ȡ��ҿ�����
    Controller* get_player(const PlayerType& type) {return player_list[type];};

    //���½�ɫ�������е���������������
    void on_input(const ExMessage& msg);

    // ɾ���������캯���͸�ֵ�����
    PlayerControllerManger(const PlayerControllerManger&) = delete;
    PlayerControllerManger& operator=(const PlayerControllerManger&) = delete;

private:
    unordered_map<PlayerType,Controller*>  player_list;

private:
    PlayerControllerManger() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��
    ~PlayerControllerManger() = default;


};

