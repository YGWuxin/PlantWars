#include "SceneManger.h"
#include "PlayerControllerManger.h"
#include "CharacterManger.h"
#include "RenderManager.h"
#include "Camera.h"
#include "CollisionManger.h"
#include "ItemManger.h"
#include "ParticleManger.h"

void SceneManger::create_main_camera()
{
	main_camera = new Camera();
}


void SceneManger::switch_to(SceneType type)
{
	if (!main_camera)
		return;
	main_camera->reset();

	//清除所有可销毁的渲染对象
	RenderManager& render_manger = RenderManager::getInstance();
	ItemManger& item_manger = ItemManger::GetInstance();

	render_manger.clearDestroyedItems();
	render_manger.clearDestroyedUI();

	item_manger.clear_items();

	Scene* temp = getScene(type);
	if (temp == nullptr)
		return;
	if (current_scene != nullptr)
		current_scene->on_exit();
	current_scene = temp;
	current_scene->on_enter();
}


Scene* SceneManger::getScene(SceneType type)
{
    auto it = SceneMap.find(type);
    if (it != SceneMap.end()) {
        return it->second; // 使用 it->second 获取 Scene*
    }
    return nullptr; // 如果找不到，返回 nullptr
}

void SceneManger::on_update(int delta)
{
	if (!main_camera && current_scene == nullptr)
		return;

	main_camera->on_update(delta);

	//更新物品管理器里的物品数据
	ItemManger::GetInstance().on_update(delta);

	//检查碰撞
	CollisionManger::GetInstance().process_collide(delta);

	//粒子管理器更新
	ParticleManger::getInstance().on_update(delta);

	//更新当前场景的数据
	current_scene->on_update(delta);

}


void SceneManger::on_draw()
{
	if (!main_camera)
		return;
	RenderManager& render_manager = RenderManager::getInstance();
	CollisionManger& collision_manger = CollisionManger::GetInstance();


	render_manager.render_object(*main_camera);
	render_manager.render_ui();
	collision_manger.on_debug_render(*main_camera);
}


void SceneManger::on_input(const ExMessage& msg)
{
	if (!main_camera)
		return;
	//检查玩家的输入
	PlayerControllerManger::GetInstance().on_input(msg);
	if (current_scene == nullptr)
		return;
	current_scene->on_input(msg);
}

void SceneManger::addSceneToMap(SceneType type, Scene* scene)
{
	if (scene != nullptr) {
		auto result = SceneMap.find(type);
		if (result == SceneMap.end()) {
			// 键不存在，插入新的键值对
			SceneMap.insert(std::pair<SceneType, Scene*>(type, scene));
		}
		else {
			// 键已存在，执行更新操作或其他处理
			result->second = scene; // 更新现有的 Scene* 指针
			// 或者其他处理逻辑
		}
	}
}

void SceneManger::removeSceneFromMap(SceneType type)
{
	auto it = SceneMap.find(type);
	if (it != SceneMap.end()) {
		// 键存在，删除对应的键值对
		SceneMap.erase(it);
	}
}

