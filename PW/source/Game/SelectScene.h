#pragma once

#include "Scene.h"
#include "Vector2.h"
#include "../Utils/Timer.h"

class Camera;
class Character;
class Controller;
class RenderItem;
class RenderUI;
class Animation;
class IMAGE;

class SelectScene : public Scene
{
public:
	SelectScene() = default;
	~SelectScene() = default;

	void on_enter() override;

	void on_update(int delta) override;

	void on_input(const ExMessage& msg) override;

	void on_exit() override;


	//玩家输入事件
	void play1_KeyD_Down();
	void play1_KeyD_Up();
	void play1_KeyA_Down();
	void play1_KeyA_Up();

	void play2_KeyArrowRight_Down();
	void play2_KeyArrowRight_Up();
	void play2_KeyArrowLeft_Down();
	void play2_KeyArrowLeft_Up();

private:
	const int OFFSET_X = 50;

	LPCTSTR str_peashooter_name = _T("婉逗射手");
	LPCTSTR str_sunflower_name = _T("龙日葵");
	LPCTSTR str_gloomshroom_name = _T("大喷菇");
	LPCTSTR str_nut_name = _T("坚哥");

	Camera* main_camera = nullptr;
	Character* character1 = nullptr;
	Character* character2 = nullptr;

	Controller* player1 = nullptr;
	Controller* player2 = nullptr;

	Animation* peashooter_idle_animtaion_right = nullptr;
	Animation* peashooter_idle_animtaion_left = nullptr;
	Animation* sunflower_idle_animtaion_right = nullptr;
	Animation* sunflower_idle_animtaion_left = nullptr;
	Animation* gloomshroom_idle_animtaion_right = nullptr;
	Animation* gloomshroom_idle_animtaion_left = nullptr;
	Animation* nut_idle_animtaion_right = nullptr;
	Animation* nut_idle_animtaion_left = nullptr;

	RenderUI* btn_1P_selector_left = nullptr;
	RenderUI* btn_1P_selector_right = nullptr;
	RenderUI* btn_2P_selector_left = nullptr;
	RenderUI* btn_2P_selector_right = nullptr;

	RenderUI* selector_character_1P_name = nullptr;
	RenderUI* selector_character_2P_name = nullptr;

	RenderUI* selector_backgroud_scorll_1P_1 = nullptr;
	RenderUI* selector_backgroud_scorll_1P_2 = nullptr;
	RenderUI* selector_backgroud_scorll_2P_1 = nullptr;
	RenderUI* selector_backgroud_scorll_2P_2 = nullptr;

	IMAGE* img_peashooter_seletor_background_left = nullptr;
	IMAGE* img_peashooter_seletor_background_right = nullptr;
	IMAGE* img_sunflower_seletor_background_left = nullptr;
	IMAGE* img_sunflower_seletor_background_right = nullptr;
	IMAGE* img_gloomshroom_seletor_background_left = nullptr;
	IMAGE* img_gloomshroom_seletor_background_right = nullptr;
	IMAGE* img_nut_seletor_background_left = nullptr;
	IMAGE* img_nut_seletor_background_right = nullptr;


	IMAGE* img_1P_selector_btn_idle_left = nullptr;
	IMAGE* img_1P_selector_btn_down_left = nullptr;
	IMAGE* img_1P_selector_btn_idle_right = nullptr;
	IMAGE* img_1P_selector_btn_down_right = nullptr;

	IMAGE* img_2P_selector_btn_idle_left = nullptr;
	IMAGE* img_2P_selector_btn_down_left = nullptr;
	IMAGE* img_2P_selector_btn_idle_right = nullptr;
	IMAGE* img_2P_selector_btn_down_right = nullptr;


	Vector2 pos_img_VS = { 0,0 };								//VS 艺术字体的图片位置
	Vector2 pos_img_tip = { 0,0 };								//提示信息文本位置
	Vector2 pos_img_1P = { 0,0 };								//1P 文本图片位置
	Vector2 pos_img_2P = { 0,0 };								//2P 文本图片位置
	Vector2 pos_img_1P_desc = { 0,0 };							//1P 键位描述位置
	Vector2 pos_img_2P_desc = { 0,0 };							//2P 键位描述位置
	Vector2 pos_img_1P_name = { 0,0 };							//1P 角色姓名文本位置
	Vector2 pos_img_2P_name = { 0,0 };							//2P 角色姓名文本位置
	Vector2 pos_character_1P = { 0,0 };							//1P 角色位置
	Vector2 pos_character_2P = { 0,0 };							//2P 角色位置
	Vector2 pos_img_1P_gravestone = { 0,0 };					//1P 角色墓碑位置
	Vector2 pos_img_2P_gravestone = { 0,0 };					//2P 角色墓碑位置
	Vector2 pos_1P_selector_btn_left = { 0,0 };					//1P 向左切换按钮
	Vector2 pos_1P_selector_btn_righr = { 0,0 };				//1P 向右切换按钮
	Vector2 pos_2P_selector_btn_left = { 0,0 };					//2P 向左切换按钮
	Vector2 pos_2P_selector_btn_righr = { 0,0 };				//2P 向右切换按钮

	int selector_backgroud_scoll_offest_x = 0;					//背景板滚动距离

	const char* backgroud_music_alias = nullptr;

	Timer timer_background_move;


};

