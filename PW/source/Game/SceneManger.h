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
        static SceneManger instance; // 静态局部变量，确保唯一性
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    SceneManger(const SceneManger&) = delete;
    SceneManger& operator=(const SceneManger&) = delete;
	
    enum class SceneType
    {
        Menu,
        Select,
        Level1,
    };

    //切换场景
    void switch_to(SceneType type);

    //更新当前场景游戏数据
    void on_update(int delta);

    //渲染当前场景
    void on_draw();

    //检测当前场景玩家输入状态
    void on_input(const ExMessage& msg);

    //添加场景
    void addSceneToMap(SceneType type, Scene* scene);

    //移除场景
    void removeSceneFromMap(SceneType type);

    //获取场景
    Scene* getScene(SceneType type);

    void create_main_camera();

    Camera* get_main_camera() { return main_camera; }


private:
    SceneManger() = default;    // 私有构造函数，防止外部创建实例

    Scene* current_scene = nullptr;
    std::map<SceneType, Scene*> SceneMap;
    Camera* main_camera = nullptr;


};

