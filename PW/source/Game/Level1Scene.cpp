#include "Level1Scene.h"
#include <iostream>
#include "Camera.h"
#include "Character.h"
#include "CharacterManger.h"
#include "Controller.h"
#include "PlayerControllerManger.h"
#include "SceneManger.h"
#include "RenderManager.h"
#include "ResourcesManger.h"
#include "CollisionManger.h"
#include "PlatformSmall.h"
#include "PlatformLarge.h"
#include "BulletPool.h"
#include "StatusBar.h"
#include "AudioManger.h"
#include "BuffBox.h"


using namespace std;

void Level1Scene::on_enter()
{
	//std::cout << "进入关卡1" << std::endl;

	//获取主摄像机
	main_camera = SceneManger::GetInstance().get_main_camera();
	//获取角色管理器实例
	CharacterManger& character_manger = CharacterManger::GetInstance();
	//获取资源管理器实例
	ResourcesManger& res_manger = ResourcesManger::GetInstance();
	//获取渲染管理器实例
	RenderManager& render_manger = RenderManager::getInstance();
	//获取碰撞管理器实例
	CollisionManger& collision_manger = CollisionManger::GetInstance();

	collision_manger.set_enabled_debug(false);

	//播放音乐
	backgroud_music_alias = AudioManger::GetInstance().PlaySoundAudio("res/sound/bgm_game.mp3", 400, true);
	
	//获取子弹对象池
	BulletPool& bullet_pool = BulletPool::GetInstance();
	bullet_pool.InitPool(100,BulletPool::BulletTyep::PeaBullet);			//创建一百发豌豆子弹
	bullet_pool.InitPool(50, BulletPool::BulletTyep::SunBullet);			//创建50发普通太阳子弹
	bullet_pool.InitPool(10, BulletPool::BulletTyep::SunExBullet);			//创建10发特殊太阳子弹
	bullet_pool.InitPool(20, BulletPool::BulletTyep::BubbleBullet);		    //创建20发泡泡子弹
	bullet_pool.InitPool(100, BulletPool::BulletTyep::BubbleExBullet);		//创建100发特殊泡泡子弹
	bullet_pool.InitPool(10, BulletPool::BulletTyep::Explode);		//创建100发特殊泡泡子弹

	//获取玩家控制器
	play1 = PlayerControllerManger::GetInstance().get_player(PlayerControllerManger::PlayerType::Player_P1);
	play2 = PlayerControllerManger::GetInstance().get_player(PlayerControllerManger::PlayerType::Player_P2);


	//生成角色
	character1 = character_manger.create_character(play1->get_character_type(), main_camera, { 295,100});
	character2 = character_manger.create_character(play2->get_character_type(), main_camera, { 975,100 });
	character2->set_is_face_rigth(false);

	if (play1)
	{
		play1->clear_input_event_map();   //清空按键事件映射
		play1->add_input_event_map('D', "move_right", Character::KeyState::KEY_DOWN);			//按下D键执行角色中标签为move_right的函数事件	
		play1->add_input_event_map('D', "move_right", Character::KeyState::KEY_UP);

		play1->add_input_event_map('A', "move_left", Character::KeyState::KEY_DOWN);
		play1->add_input_event_map('A', "move_left", Character::KeyState::KEY_UP);

		play1->add_input_event_map('W', "jump", Character::KeyState::KEY_DOWN);

		play1->add_input_event_map('F', "attack", Character::KeyState::KEY_DOWN);
		play1->add_input_event_map('G', "attack_ex", Character::KeyState::KEY_DOWN);

		play1->Possess(character1);		//玩家控制器控制character1

		player_bar_1 = new StatusBar(play1, {200,600});

	}

	if (play2)
	{
		play2->clear_input_event_map();   //清空按键事件映射
		play2->add_input_event_map(VK_RIGHT, "move_right", Character::KeyState::KEY_DOWN);			//按下D键执行角色中标签为move_right的函数事件	
		play2->add_input_event_map(VK_RIGHT, "move_right", Character::KeyState::KEY_UP);

		play2->add_input_event_map(VK_LEFT, "move_left", Character::KeyState::KEY_DOWN);
		play2->add_input_event_map(VK_LEFT, "move_left", Character::KeyState::KEY_UP);

		play2->add_input_event_map(VK_UP, "jump", Character::KeyState::KEY_DOWN);

		play2->add_input_event_map(VK_OEM_PERIOD, "attack", Character::KeyState::KEY_DOWN);
		play2->add_input_event_map(VK_OEM_2, "attack_ex", Character::KeyState::KEY_DOWN);

		play2->Possess(character2);		//玩家控制器控制character1

		player_bar_2 = new StatusBar(play2, { 700,600 });
	}
	

	IMAGE* img_sky = res_manger.find_image("img_sky");
	render_manger.createRenderItem(img_sky, {(float)((getwidth() - img_sky->getwidth()) / 2),(float)((getheight() - img_sky->getheight()) / 2)},0);

	IMAGE* img_hills = res_manger.find_image("img_hills");
	render_manger.createRenderItem(img_hills, {(float)((getwidth() - img_hills->getwidth()) / 2) , -30 }, 1);
	

	//创建平台
	platform_small_top = new PlatformSmall({(float)(getwidth() / 2),250});
	platform_small_left = new PlatformSmall({ 295, 370 });
	platform_small_right = new PlatformSmall({ 975, 370 });
	platform_large = new PlatformLarge({(float)(getwidth() / 2) , 640 });


	IMAGE* img_1P_cursor = res_manger.find_image("img_1P_cursor");
	UI_1P_cursor = render_manger.createRenderItemUIIamge(img_1P_cursor, {-200,-200},5);

	IMAGE* img_2P_cursor = res_manger.find_image("img_2P_cursor");
	UI_2P_cursor = render_manger.createRenderItemUIIamge(img_2P_cursor, { -200,-200 }, 5);

	float offset_y = 80;

	UI_winner = nullptr;

	IMAGE* img_winner_bar = res_manger.find_image("img_winner_bar");
	UI_winner_bar = render_manger.createRenderItemUIIamge(img_winner_bar, { -(float)img_winner_bar->getwidth(), (float)getheight() / 2 - (float)img_winner_bar->getheight() / 2 - offset_y }, 6);

	IMAGE* img_1P_winner = res_manger.find_image("img_1P_winner");
	UI_1P_winner = render_manger.createRenderItemUIIamge(img_1P_winner, { -(float)img_1P_winner->getwidth(), (float)getheight() / 2 - (float)img_1P_winner->getheight() / 2 - offset_y }, 7);

	IMAGE* img_2P_winner = res_manger.find_image("img_2P_winner");
	UI_2P_winner = render_manger.createRenderItemUIIamge(img_2P_winner, {  -(float)img_2P_winner->getwidth(), (float)getheight() / 2 - (float)img_2P_winner->getheight() / 2 - offset_y }, 7);


	is_cursor_disappear = false;
	timer_cursor_disappear.set_wait_time(2000);
	timer_cursor_disappear.restart();
	timer_cursor_disappear.set_one_shot(true);
	timer_cursor_disappear.set_callback([&]() {
		this->is_cursor_disappear = true;
		this->UI_1P_cursor->setCanRender(false);
		this->UI_2P_cursor->setCanRender(false);
		});

	is_game_over = false;
	timer_winner_bar_slide_in.set_wait_time(2500);
	timer_winner_bar_slide_in.restart();
	timer_winner_bar_slide_in.set_one_shot(true);
	timer_winner_bar_slide_in.set_callback([&]() {
		this->is_winner_silde_out_start = true;
		});

	timer_game_over.set_wait_time(1500);
	timer_game_over.restart();
	timer_game_over.set_one_shot(true);
	timer_game_over.set_callback([&]() {
		this->is_winner_silde_out_start = false;
		SceneManger::GetInstance().switch_to(SceneManger::SceneType::Menu);
		});


	//BuffBox* box = new BuffBox();
	//generate_buff_box_time = rand() % 5000 + 5000;
	timer_generate_buff_box.set_wait_time(generate_buff_box_time);
	timer_generate_buff_box.restart();
	timer_generate_buff_box.set_callback([&]() {
		BuffBox* box = new BuffBox();
		this->generate_buff_box_time = rand() % 9000 + 1000;
		this->timer_generate_buff_box.set_wait_time(generate_buff_box_time);
		});

}


void Level1Scene::on_update(int delta)
{
	//printf("Level1Scene执行\r\n");

	//更新玩家状态
	if (player_bar_1)
		player_bar_1->on_update(delta);
	if (player_bar_2)
		player_bar_2->on_update(delta);

	timer_cursor_disappear.on_update(delta);

	timer_generate_buff_box.on_update(delta);

	//游戏结束时执行
	if (is_game_over && UI_winner && UI_winner_bar)
	{ 
		float positionX = UI_winner_bar->getPostion().x;
		positionX += speed_winner_bar * delta;
		UI_winner_bar->setPositionX(positionX);

		positionX = UI_winner->getPostion().x;
		positionX += speed_winner_text * delta;
		UI_winner->setPositionX(positionX);

		if (!is_winner_silde_out_start)
		{
			timer_winner_bar_slide_in.on_update(delta);
			positionX = UI_winner_bar->getPostion().x;
			if (positionX >= (float)(getwidth() / 2 - UI_winner_bar->getImage()->getwidth() / 2))
			{
				positionX = (float)(getwidth() / 2 - UI_winner_bar->getImage()->getwidth() / 2);
				UI_winner_bar->setPositionX(positionX);
			}

			positionX = UI_winner->getPostion().x;
			if (positionX >= (float)(getwidth() / 2 - UI_winner->getImage()->getwidth() / 2))
			{
				positionX = (float)(getwidth() / 2 - UI_winner->getImage()->getwidth() / 2);
				UI_winner->setPositionX(positionX);
			}
		}
		else
			timer_game_over.on_update(delta);

	}

	//检查玩家1的光标
	if (UI_1P_cursor && character1 && !is_cursor_disappear)
	{
		Vector2 position_character = character1->get_current_posistion();
		Vector2 position_p1 = { position_character.x - character1->get_item_size().x, position_character.y - character1->get_item_size().y * 3};
		UI_1P_cursor->setPosition(position_p1);
	}

	//检查玩家2的光标
	if (UI_2P_cursor && character2 && !is_cursor_disappear)
	{
		Vector2 position_character = character2->get_current_posistion();
		Vector2 position_p2 = { position_character.x - character2->get_item_size().x, position_character.y - character2->get_item_size().y * 3 };
		UI_2P_cursor->setPosition(position_p2);
	}

	//判断胜负
	if (play1 && !is_game_over && play1->get_owned_character())
	{
		Vector2 position_play1 = play1->get_owned_character()->get_current_posistion();
		Vector2 size_play1 = play1->get_owned_character()->get_item_size();
		if (position_play1.y - size_play1.y >= getheight())
		{
			play1->get_owned_character()->set_hp(0);
			is_game_over = true;
			UI_winner = UI_2P_winner;
			AudioManger::GetInstance().StopSound(backgroud_music_alias);
			backgroud_music_alias = AudioManger::GetInstance().PlaySoundAudio("res/sound/ui_win1.mp3", 400, true);
		}
		else
		{
			if (play1->get_owned_character()->get_hp() <= 0)
			{
				play1->get_owned_character()->on_die();
				is_game_over = true;
				UI_winner = UI_2P_winner;
				AudioManger::GetInstance().StopSound(backgroud_music_alias);
				backgroud_music_alias = AudioManger::GetInstance().PlaySoundAudio("res/sound/ui_win1.mp3", 400, true);
			}
		}

	}
	if (play2 && !is_game_over	&& play2->get_owned_character())
	{
		Vector2 position_play2 = play2->get_owned_character()->get_current_posistion();
		Vector2 size_play2 = play2->get_owned_character()->get_item_size();
		if (position_play2.y - size_play2.y >= getheight())
		{
			play2->get_owned_character()->set_hp(0);
			is_game_over = true;
			UI_winner = UI_1P_winner;
			AudioManger::GetInstance().StopSound(backgroud_music_alias);
			backgroud_music_alias = AudioManger::GetInstance().PlaySoundAudio("res/sound/ui_win1.mp3", 400, true);
		}
		else
		{
			if (play2->get_owned_character()->get_hp() <= 0)
			{
				play2->get_owned_character()->on_die();
				is_game_over = true;
				UI_winner = UI_1P_winner;
				AudioManger::GetInstance().StopSound(backgroud_music_alias);
				backgroud_music_alias = AudioManger::GetInstance().PlaySoundAudio("res/sound/ui_win1.mp3", 400, true);
			}
		}
	}

}


void Level1Scene::on_input(const ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		if (msg.vkcode == 'Q')
		{
			CollisionManger& collision_manger = CollisionManger::GetInstance();
			if (collision_manger.get_enabled_debug())
			{
				collision_manger.set_enabled_debug(false);
			}
			else
			{
				collision_manger.set_enabled_debug(true);
			}
		}

	}
}


void Level1Scene::on_exit()
{
	//printf("Level1Scene退出\r\n");

	

	BulletPool& bullet_pool = BulletPool::GetInstance();
	bullet_pool.clear_pool();

	if (player_bar_1)
		delete player_bar_1;
	if (player_bar_2)
		delete player_bar_2;


	if(backgroud_music_alias)
		AudioManger::GetInstance().StopSound(backgroud_music_alias);

}


