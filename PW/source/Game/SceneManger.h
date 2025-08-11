#pragma once

#include <map>
#include <utility> 
#include <graphics.h>	
#include "Scene.h"

class Camera;

class SceneManger
{
public:
    static SceneManger& GetInstance()
    {
        static SceneManger instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }

    // ɾ���������캯���͸�ֵ�����
    SceneManger(const SceneManger&) = delete;
    SceneManger& operator=(const SceneManger&) = delete;
	
    enum class SceneType
    {
        Menu,
        Select,
        Level1,
    };

    //�л�����
    void switch_to(SceneType type);

    //���µ�ǰ������Ϸ����
    void on_update(int delta);

    //��Ⱦ��ǰ����
    void on_draw();

    //��⵱ǰ�����������״̬
    void on_input(const ExMessage& msg);

    //��ӳ���
    void addSceneToMap(SceneType type, Scene* scene);

    //�Ƴ�����
    void removeSceneFromMap(SceneType type);

    //��ȡ����
    Scene* getScene(SceneType type);

    void create_main_camera();

    Camera* get_main_camera() { return main_camera; }


private:
    SceneManger() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��

    Scene* current_scene = nullptr;
    std::map<SceneType, Scene*> SceneMap;
    Camera* main_camera = nullptr;


};

