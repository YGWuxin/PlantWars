#include "MenuScene.h"
#include <iostream>
#include "SceneManger.h"
#include <graphics.h>	
#include "ResourcesManger.h"
#include "AudioManger.h"
#include "../Res/Animation.h"
#include "Vector2.h"
#include "../Utils/helper.h"
#include "RenderManager.h"

void MenuScene::on_enter()
{
	//≤•∑≈±≥æ∞“Ù¿÷
	backgroud_music_alias = AudioManger::GetInstance().PlaySoundAudio("res/sound/bgm_menu.mp3", true);
	
	//ªÒ»°…„œÒÕ∑
	main_camera = SceneManger::GetInstance().get_main_camera();
	main_camera->reset();

	ResourcesManger& res_manger = ResourcesManger::GetInstance();
	RenderManager& render_manger = RenderManager::getInstance();

	//‰÷»æ±≥æ∞
	render_manger.createRenderItemUIIamge(res_manger.find_image("img_menu_background"), { 0,0 }, 0);

}


void MenuScene::on_update(int delta)
{
	

}


void MenuScene::on_input(const ExMessage& msg)
{
	if (msg.message == WM_KEYUP)
	{
		SceneManger::GetInstance().switch_to(SceneManger::SceneType::Select);
	}
}


void MenuScene::on_exit()
{
	AudioManger::GetInstance().StopSound(backgroud_music_alias);
	AudioManger::GetInstance().PlaySoundAudio("res/sound/ui_confirm.mp3", 500, false);

}
