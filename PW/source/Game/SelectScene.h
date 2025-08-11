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


	//��������¼�
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

	LPCTSTR str_peashooter_name = _T("������");
	LPCTSTR str_sunflower_name = _T("���տ�");
	LPCTSTR str_gloomshroom_name = _T("���繽");
	LPCTSTR str_nut_name = _T("���");

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


	Vector2 pos_img_VS = { 0,0 };								//VS ���������ͼƬλ��
	Vector2 pos_img_tip = { 0,0 };								//��ʾ��Ϣ�ı�λ��
	Vector2 pos_img_1P = { 0,0 };								//1P �ı�ͼƬλ��
	Vector2 pos_img_2P = { 0,0 };								//2P �ı�ͼƬλ��
	Vector2 pos_img_1P_desc = { 0,0 };							//1P ��λ����λ��
	Vector2 pos_img_2P_desc = { 0,0 };							//2P ��λ����λ��
	Vector2 pos_img_1P_name = { 0,0 };							//1P ��ɫ�����ı�λ��
	Vector2 pos_img_2P_name = { 0,0 };							//2P ��ɫ�����ı�λ��
	Vector2 pos_character_1P = { 0,0 };							//1P ��ɫλ��
	Vector2 pos_character_2P = { 0,0 };							//2P ��ɫλ��
	Vector2 pos_img_1P_gravestone = { 0,0 };					//1P ��ɫĹ��λ��
	Vector2 pos_img_2P_gravestone = { 0,0 };					//2P ��ɫĹ��λ��
	Vector2 pos_1P_selector_btn_left = { 0,0 };					//1P �����л���ť
	Vector2 pos_1P_selector_btn_righr = { 0,0 };				//1P �����л���ť
	Vector2 pos_2P_selector_btn_left = { 0,0 };					//2P �����л���ť
	Vector2 pos_2P_selector_btn_righr = { 0,0 };				//2P �����л���ť

	int selector_backgroud_scoll_offest_x = 0;					//�������������

	const char* backgroud_music_alias = nullptr;

	Timer timer_background_move;


};

