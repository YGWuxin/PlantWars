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

	//������п����ٵ���Ⱦ����
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
        return it->second; // ʹ�� it->second ��ȡ Scene*
    }
    return nullptr; // ����Ҳ��������� nullptr
}

void SceneManger::on_update(int delta)
{
	if (!main_camera && current_scene == nullptr)
		return;

	main_camera->on_update(delta);

	//������Ʒ�����������Ʒ����
	ItemManger::GetInstance().on_update(delta);

	//�����ײ
	CollisionManger::GetInstance().process_collide(delta);

	//���ӹ���������
	ParticleManger::getInstance().on_update(delta);

	//���µ�ǰ����������
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
	//�����ҵ�����
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
			// �������ڣ������µļ�ֵ��
			SceneMap.insert(std::pair<SceneType, Scene*>(type, scene));
		}
		else {
			// ���Ѵ��ڣ�ִ�и��²�������������
			result->second = scene; // �������е� Scene* ָ��
			// �������������߼�
		}
	}
}

void SceneManger::removeSceneFromMap(SceneType type)
{
	auto it = SceneMap.find(type);
	if (it != SceneMap.end()) {
		// �����ڣ�ɾ����Ӧ�ļ�ֵ��
		SceneMap.erase(it);
	}
}

