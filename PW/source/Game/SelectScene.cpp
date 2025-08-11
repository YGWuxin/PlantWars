#include "SelectScene.h"
#include <iostream>
#include "Camera.h"
#include "Character.h"
#include "CharacterManger.h"
#include "Controller.h"
#include "PlayerControllerManger.h"
#include "SceneManger.h"
#include "RenderManager.h"
#include "ResourcesManger.h"
#include "../Parameter/GlobeGameParameters.h"
#include "../Res/Animation.h"
#include "AudioManger.h"


using namespace std;

void SelectScene::on_enter()
{
	//获取摄像头
	main_camera = SceneManger::GetInstance().get_main_camera();

	backgroud_music_alias = AudioManger::GetInstance().PlaySoundAudio("res/sound/bgm_game_select1.mp3", 600, true);

	ResourcesManger& res_manger = ResourcesManger::GetInstance();
	RenderManager& render_manger = RenderManager::getInstance();
	//获取角色管理器实例
	CharacterManger& character_manger = CharacterManger::GetInstance();
	PlayerControllerManger& player_manger = PlayerControllerManger::GetInstance();

	player1 = player_manger.get_player(PlayerControllerManger::PlayerType::Player_P1);
	player2 = player_manger.get_player(PlayerControllerManger::PlayerType::Player_P2);

	player1->enable_input();
	player2->enable_input();

	/* 创建动画  */
	//有关婉逗射手的待机动画
	peashooter_idle_animtaion_right = new Animation();
	peashooter_idle_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_peashooter_idle_right"));
	peashooter_idle_animtaion_right->set_interval(90);
	peashooter_idle_animtaion_right->set_loop(true);

	peashooter_idle_animtaion_left = new Animation();
	peashooter_idle_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_peashooter_idle_left"));
	peashooter_idle_animtaion_left->set_interval(90);
	peashooter_idle_animtaion_left->set_loop(true);

	//有关龙日葵的待机动画
	sunflower_idle_animtaion_right = new Animation();
	sunflower_idle_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_sunflower_idle_right"));
	sunflower_idle_animtaion_right->set_interval(90);
	sunflower_idle_animtaion_right->set_loop(true);

	sunflower_idle_animtaion_left = new Animation();
	sunflower_idle_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_sunflower_idle_left"));
	sunflower_idle_animtaion_left->set_interval(90);
	sunflower_idle_animtaion_left->set_loop(true);

	//有关大喷菇的待机动画
	gloomshroom_idle_animtaion_right = new Animation();
	gloomshroom_idle_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_gloomshroom_idle_right"));
	gloomshroom_idle_animtaion_right->set_interval(100);
	gloomshroom_idle_animtaion_right->set_loop(true);

	gloomshroom_idle_animtaion_left = new Animation();
	gloomshroom_idle_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_gloomshroom_idle_left"));
	gloomshroom_idle_animtaion_left->set_interval(100);
	gloomshroom_idle_animtaion_left->set_loop(true);

	//有关坚哥的待机动画
	nut_idle_animtaion_right = new Animation();
	nut_idle_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_nut_idle_right"));
	nut_idle_animtaion_right->set_interval(100);
	nut_idle_animtaion_right->set_loop(true);

	nut_idle_animtaion_left = new Animation();
	nut_idle_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_nut_idle_left"));
	nut_idle_animtaion_left->set_interval(100);
	nut_idle_animtaion_left->set_loop(true);


	//创建显示在UI层面上的角色
	character1 = character_manger.create_character({ 0,0 },true);
	character1->set_render_layer(8);

	character2 = character_manger.create_character({ 0,0 }, true);
	character2->set_render_layer(8);

	 //获取ui图像以及计算ui的位置
	 IMAGE* img_vs = res_manger.find_image("img_vs");
	 pos_img_VS.x = (WIN_WIDTH - img_vs->getwidth()) / 2;
	 pos_img_VS.y = (WIN_HIGH - img_vs->getheight()) / 2;
	 render_manger.createRenderItemUIIamge(img_vs, pos_img_VS, 3);

	 IMAGE* img_tip = res_manger.find_image("img_selector_tip");
	 pos_img_tip.x = (WIN_WIDTH - img_tip->getwidth()) / 2;
	 pos_img_tip.y = WIN_HIGH - 125;
	 render_manger.createRenderItemUIIamge(img_tip, pos_img_tip, 4);

	 IMAGE* img_1P = res_manger.find_image("img_1P");
	 pos_img_1P.x = (WIN_WIDTH / 2 - img_1P->getwidth()) / 2 - OFFSET_X;
	 pos_img_1P.y = 35;
	 render_manger.createRenderItemUIIamge(img_1P, pos_img_1P, 3);

	 IMAGE* img_2P = res_manger.find_image("img_2P");
	 pos_img_2P.x = WIN_WIDTH / 2 + (WIN_WIDTH / 2 - img_2P->getwidth()) / 2 + OFFSET_X;
	 pos_img_2P.y = pos_img_1P.y;
	 render_manger.createRenderItemUIIamge(img_2P, pos_img_2P, 3);

	 IMAGE* img_1P_desc = res_manger.find_image("img_1P_desc");
	 pos_img_1P_desc.x = (WIN_WIDTH / 2 - img_1P_desc->getwidth()) / 2 - OFFSET_X;
	 pos_img_1P_desc.y = WIN_HIGH - 150;
	 render_manger.createRenderItemUIIamge(img_1P_desc, pos_img_1P_desc, 3);

	 IMAGE* img_2P_desc = res_manger.find_image("img_2P_desc");
	 pos_img_2P_desc.x = WIN_WIDTH / 2 + (WIN_WIDTH / 2 - img_2P_desc->getwidth()) / 2 + OFFSET_X;
	 pos_img_2P_desc.y = pos_img_1P_desc.y;
	 render_manger.createRenderItemUIIamge(img_2P_desc, pos_img_2P_desc, 3);


	 IMAGE* img_1P_gravestone = res_manger.find_image("img_gravestone_right");
	 pos_img_1P_gravestone.x =(WIN_WIDTH / 2 - img_1P_gravestone->getwidth()) / 2 - OFFSET_X;
	 pos_img_1P_gravestone.y = pos_img_1P.y + img_1P->getheight() + 35;
	 render_manger.createRenderItemUIIamge(img_1P_gravestone, pos_img_1P_gravestone, 3);

	 IMAGE* img_2P_gravestone = res_manger.find_image("img_gravestone_left");
	 pos_img_2P_gravestone.x = WIN_WIDTH / 2 + (WIN_WIDTH / 2 - img_2P_gravestone->getwidth()) / 2 + OFFSET_X;
	 pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;
	 render_manger.createRenderItemUIIamge(img_2P_gravestone, pos_img_2P_gravestone, 3);

	 pos_character_1P.x = (WIN_WIDTH / 2 - peashooter_idle_animtaion_right->get_current_frame_image()->getwidth()) / 2 - OFFSET_X;
	 pos_character_1P.y = pos_img_1P_gravestone.y + 80;
	 character1->set_current_posistion(pos_character_1P);

	 pos_character_2P.x = WIN_WIDTH / 2 + (WIN_WIDTH / 2 - peashooter_idle_animtaion_right->get_current_frame_image()->getwidth()) / 2 + OFFSET_X;
	 pos_character_2P.y = pos_img_2P_gravestone.y + 80;
	 character2->set_current_posistion(pos_character_2P);

	 img_1P_selector_btn_idle_left = res_manger.find_image("img_1P_selector_btn_idle_left");
	 img_1P_selector_btn_down_left = res_manger.find_image("img_1P_selector_btn_down_left");
	 img_1P_selector_btn_idle_right = res_manger.find_image("img_1P_selector_btn_idle_right");
	 img_1P_selector_btn_down_right = res_manger.find_image("img_1P_selector_btn_down_right");

	 img_2P_selector_btn_idle_left = res_manger.find_image("img_2P_selector_btn_idle_left");
	 img_2P_selector_btn_down_left = res_manger.find_image("img_2P_selector_btn_down_left");
	 img_2P_selector_btn_idle_right = res_manger.find_image("img_2P_selector_btn_idle_right");
	 img_2P_selector_btn_down_right = res_manger.find_image("img_2P_selector_btn_down_right");

	 pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left->getwidth();
	 pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (img_1P_gravestone->getheight() - img_1P_selector_btn_idle_left->getwidth()) / 2;
	 pos_1P_selector_btn_righr.x = pos_img_1P_gravestone.x + img_1P_gravestone->getwidth();
	 pos_1P_selector_btn_righr.y = pos_1P_selector_btn_left.y;

	 pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left->getwidth();
	 pos_2P_selector_btn_left.y = pos_img_2P_gravestone.y + (img_2P_gravestone->getheight() - img_2P_selector_btn_idle_left->getwidth()) / 2;
	 pos_2P_selector_btn_righr.x = pos_img_2P_gravestone.x + img_2P_gravestone->getwidth();
	 pos_2P_selector_btn_righr.y = pos_2P_selector_btn_left.y;

	 btn_1P_selector_left = render_manger.createRenderItemUIIamge(img_1P_selector_btn_idle_left, pos_1P_selector_btn_left, 3);
	 btn_1P_selector_right = render_manger.createRenderItemUIIamge(img_1P_selector_btn_idle_right, pos_1P_selector_btn_righr, 3);

	 btn_2P_selector_left = render_manger.createRenderItemUIIamge(img_2P_selector_btn_idle_left, pos_2P_selector_btn_left, 3);
	 btn_2P_selector_right = render_manger.createRenderItemUIIamge(img_2P_selector_btn_idle_right, pos_2P_selector_btn_righr, 3);

	 render_manger.createRenderItemUIIamge(res_manger.find_image("img_selector_background"), { 0,0 }, 0);

	 img_peashooter_seletor_background_left = res_manger.find_image("img_peashooter_seletor_background_left");
	 img_peashooter_seletor_background_right = res_manger.find_image("img_peashooter_seletor_background_right");
	 img_sunflower_seletor_background_left = res_manger.find_image("img_sunflower_seletor_background_left");
	 img_sunflower_seletor_background_right = res_manger.find_image("img_sunflower_seletor_background_right");
	 img_gloomshroom_seletor_background_left = res_manger.find_image("img_gloomshroom_seletor_background_left");
	 img_gloomshroom_seletor_background_right = res_manger.find_image("img_gloomshroom_seletor_background_right");
	 img_nut_seletor_background_left = res_manger.find_image("img_nut_seletor_background_left");
	 img_nut_seletor_background_right = res_manger.find_image("img_nut_seletor_background_right");


	 selector_backgroud_scorll_1P_1 = render_manger.createRenderItemUIIamge(img_peashooter_seletor_background_right, { 0,0 }, 1);
	 selector_backgroud_scorll_1P_2 = render_manger.createRenderItemUIIamge(img_peashooter_seletor_background_right, { 0,0 }, 1);
	 selector_backgroud_scorll_2P_1 = render_manger.createRenderItemUIIamge(img_peashooter_seletor_background_left, { 0,0 }, 1);
	 selector_backgroud_scorll_2P_2 = render_manger.createRenderItemUIIamge(img_peashooter_seletor_background_left, { 0,0 }, 1);

	 pos_img_1P_name.x = pos_character_1P.x - 10;
	 pos_img_1P_name.y = pos_character_1P.y + 155;

	 pos_img_2P_name.x = pos_character_2P.x + 10;
	 pos_img_2P_name.y = pos_img_1P_name.y;

	 //玩家一初始化为婉逗射手
	 selector_character_1P_name = render_manger.createRenderItemUIText(_T("NULL"), pos_img_1P_name, 6);
	 player1->set_character_type(CharacterManger::CharacterType::PeashooterCharacter);
	 
	 //玩家二初始化为龙日葵
	 selector_character_2P_name = render_manger.createRenderItemUIText(_T("NULL"), pos_img_2P_name, 6);
	 player2->set_character_type(CharacterManger::CharacterType::SunflowerCharacter);
		 

	 //添加输入事件
	 player1->clear_input_event_map();
	 player1->add_input_event_map('D', Character::KeyState::KEY_DOWN, bind(&SelectScene::play1_KeyD_Down,this));
	 player1->add_input_event_map('D', Character::KeyState::KEY_UP, bind(&SelectScene::play1_KeyD_Up, this));
	 player1->add_input_event_map('A', Character::KeyState::KEY_DOWN, bind(&SelectScene::play1_KeyA_Down, this));
	 player1->add_input_event_map('A', Character::KeyState::KEY_UP, bind(&SelectScene::play1_KeyA_Up, this));

	 player2->clear_input_event_map();
	 player2->add_input_event_map(VK_RIGHT, Character::KeyState::KEY_DOWN, bind(&SelectScene::play2_KeyArrowRight_Down, this));
	 player2->add_input_event_map(VK_RIGHT, Character::KeyState::KEY_UP, bind(&SelectScene::play2_KeyArrowRight_Up, this));
	 player2->add_input_event_map(VK_LEFT, Character::KeyState::KEY_DOWN, bind(&SelectScene::play2_KeyArrowLeft_Down, this));
	 player2->add_input_event_map(VK_LEFT, Character::KeyState::KEY_UP, bind(&SelectScene::play2_KeyArrowLeft_Up, this));


	 timer_background_move.set_wait_time(10);
	 timer_background_move.set_callback([&]() {
		 this->selector_backgroud_scoll_offest_x += 6;
		 if (this->selector_backgroud_scoll_offest_x >= this->img_peashooter_seletor_background_left->getwidth())
			 this->selector_backgroud_scoll_offest_x = 0;

		 });

}

void SelectScene::on_update(int delta)
{
	timer_background_move.on_update(delta);

	CharacterManger::CharacterType player1_type = player1->get_character_type();
	CharacterManger::CharacterType player2_type = player2->get_character_type();
	switch (player1_type)
	{
	case CharacterManger::CharacterType::PeashooterCharacter:
		character1->set_current_animation(peashooter_idle_animtaion_right);
		selector_character_1P_name->set_text(str_peashooter_name);
		selector_backgroud_scorll_2P_1->setImage(img_peashooter_seletor_background_left);
		selector_backgroud_scorll_2P_2->setImage(img_peashooter_seletor_background_left);
		break;
	case CharacterManger::CharacterType::SunflowerCharacter:
		character1->set_current_animation(sunflower_idle_animtaion_right);
		selector_character_1P_name->set_text(str_sunflower_name);
		selector_backgroud_scorll_2P_1->setImage(img_sunflower_seletor_background_left);
		selector_backgroud_scorll_2P_2->setImage(img_sunflower_seletor_background_left);
		break;
	case CharacterManger::CharacterType::GloomshroomCharacter:
		character1->set_current_animation(gloomshroom_idle_animtaion_right);
		selector_character_1P_name->set_text(str_gloomshroom_name);
		selector_backgroud_scorll_2P_1->setImage(img_gloomshroom_seletor_background_left);
		selector_backgroud_scorll_2P_2->setImage(img_gloomshroom_seletor_background_left);
		break;
	case CharacterManger::CharacterType::NutCharacter:
		character1->set_current_animation(nut_idle_animtaion_right);
		selector_character_1P_name->set_text(str_nut_name);
		selector_backgroud_scorll_2P_1->setImage(img_nut_seletor_background_left);
		selector_backgroud_scorll_2P_2->setImage(img_nut_seletor_background_left);
		break;
	default:
		break;
	}
	
	selector_backgroud_scorll_2P_1->setPositionX(WIN_WIDTH - selector_backgroud_scoll_offest_x);
	selector_backgroud_scorll_2P_2->setPositionX((WIN_WIDTH - selector_backgroud_scorll_2P_2->getImage()->getwidth()) );
	selector_backgroud_scorll_2P_2->setRenderWidth(selector_backgroud_scorll_2P_2->getImage()->getwidth() - selector_backgroud_scoll_offest_x);
	selector_backgroud_scorll_2P_2->setRenderX(selector_backgroud_scoll_offest_x);

	switch (player2_type)
	{
	case CharacterManger::CharacterType::PeashooterCharacter:
		character2->set_current_animation(peashooter_idle_animtaion_left);
		selector_character_2P_name->set_text(str_peashooter_name);
		selector_backgroud_scorll_1P_1->setImage(img_peashooter_seletor_background_right);
		selector_backgroud_scorll_1P_2->setImage(img_peashooter_seletor_background_right);
		break;
	case CharacterManger::CharacterType::SunflowerCharacter:
		character2->set_current_animation(sunflower_idle_animtaion_left);
		selector_character_2P_name->set_text(str_sunflower_name);
		selector_backgroud_scorll_1P_1->setImage(img_sunflower_seletor_background_right);
		selector_backgroud_scorll_1P_2->setImage(img_sunflower_seletor_background_right);
		break;
	case CharacterManger::CharacterType::GloomshroomCharacter:
		character2->set_current_animation(gloomshroom_idle_animtaion_left);
		selector_character_2P_name->set_text(str_gloomshroom_name);
		selector_backgroud_scorll_1P_1->setImage(img_gloomshroom_seletor_background_right);
		selector_backgroud_scorll_1P_2->setImage(img_gloomshroom_seletor_background_right);
		break;
	case CharacterManger::CharacterType::NutCharacter:
		character2->set_current_animation(nut_idle_animtaion_left);
		selector_character_2P_name->set_text(str_nut_name);
		selector_backgroud_scorll_1P_1->setImage(img_nut_seletor_background_right);
		selector_backgroud_scorll_1P_2->setImage(img_nut_seletor_background_right);
		break;
	default:
		break;
	}

	selector_backgroud_scorll_1P_1->setPositionX(selector_backgroud_scoll_offest_x - selector_backgroud_scorll_1P_1->getImage()->getwidth());
	selector_backgroud_scorll_1P_2->setPositionX(selector_backgroud_scoll_offest_x);
	selector_backgroud_scorll_1P_2->setRenderWidth(selector_backgroud_scorll_1P_2->getImage()->getwidth() - selector_backgroud_scoll_offest_x);


}


void SelectScene::on_input(const ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		//printf("vkcode:%d\r\n", msg.vkcode);
		//按下enter时加入关卡1
		if(msg.vkcode == 13)
			SceneManger::GetInstance().switch_to(SceneManger::SceneType::Level1);
	}
	
}


void SelectScene::on_exit()
{
	//清除动画资源
	if (peashooter_idle_animtaion_right)
		delete peashooter_idle_animtaion_right;
	if (peashooter_idle_animtaion_left)
		delete peashooter_idle_animtaion_left;

	if (sunflower_idle_animtaion_right)
		delete sunflower_idle_animtaion_right;
	if (sunflower_idle_animtaion_left)
		delete sunflower_idle_animtaion_left;

	if (gloomshroom_idle_animtaion_right)
		delete gloomshroom_idle_animtaion_right;
	if (gloomshroom_idle_animtaion_left)
		delete gloomshroom_idle_animtaion_left;

	if (nut_idle_animtaion_right)
		delete nut_idle_animtaion_right;
	if (nut_idle_animtaion_left)
		delete nut_idle_animtaion_left;

	AudioManger::GetInstance().StopSound(backgroud_music_alias);

}



void SelectScene::play1_KeyD_Down()
{
	CharacterManger::CharacterType type = player1->get_character_type();
	CharacterManger::CharacterType player_type = (CharacterManger::CharacterType)(((int)CharacterManger::CharacterType::Invalid + (int)type - 1)%
		(int)CharacterManger::CharacterType::Invalid
		);
	player1->set_character_type(player_type);
	btn_1P_selector_right->setImage(img_1P_selector_btn_down_right);
	AudioManger::GetInstance().PlaySoundAudio("res/sound/ui_switch.mp3", 300);
}

void SelectScene::play1_KeyD_Up()
{
	btn_1P_selector_right->setImage(img_1P_selector_btn_idle_right);
}


void SelectScene::play1_KeyA_Down()
{
	CharacterManger::CharacterType type = player1->get_character_type();

	CharacterManger::CharacterType player_type = (CharacterManger::CharacterType)(((int)CharacterManger::CharacterType::Invalid + (int)type - 1) %
		(int)CharacterManger::CharacterType::Invalid
		);
	player1->set_character_type(player_type);
	btn_1P_selector_left->setImage(img_1P_selector_btn_down_left);
	AudioManger::GetInstance().PlaySoundAudio("res/sound/ui_switch.mp3", 300);
}

void SelectScene::play1_KeyA_Up()
{
	btn_1P_selector_left->setImage(img_1P_selector_btn_idle_left);
}



void SelectScene::play2_KeyArrowRight_Down()
{
	CharacterManger::CharacterType type = player2->get_character_type();

	CharacterManger::CharacterType player_type = (CharacterManger::CharacterType)(((int)CharacterManger::CharacterType::Invalid + (int)type - 1) %
		(int)CharacterManger::CharacterType::Invalid
		);
	player2->set_character_type(player_type);
	btn_2P_selector_right->setImage(img_2P_selector_btn_down_right);
	AudioManger::GetInstance().PlaySoundAudio("res/sound/ui_switch.mp3", 300);
}

void SelectScene::play2_KeyArrowRight_Up()
{
	btn_2P_selector_right->setImage(img_2P_selector_btn_idle_right);
}


void SelectScene::play2_KeyArrowLeft_Down()
{
	CharacterManger::CharacterType type = player2->get_character_type();

	CharacterManger::CharacterType player_type = (CharacterManger::CharacterType)(((int)CharacterManger::CharacterType::Invalid + (int)type - 1) %
		(int)CharacterManger::CharacterType::Invalid
		);
	player2->set_character_type(player_type);
	btn_2P_selector_left->setImage(img_2P_selector_btn_down_left);
	AudioManger::GetInstance().PlaySoundAudio("res/sound/ui_switch.mp3", 300);
}

void SelectScene::play2_KeyArrowLeft_Up()
{
	btn_2P_selector_left->setImage(img_2P_selector_btn_idle_left);
}


