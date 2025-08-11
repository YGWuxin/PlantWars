#pragma once
#include "Character.h"

class CharacterManger;

class GloomshroomCharacter : public Character
{
	friend class CharacterManger;

public:

	//��ɫ���ݸ���
	void on_update(float delta) override;

	//��ɫ����ʱ�ĳ�ʼ��
	void on_init() override;

	

protected:
	GloomshroomCharacter(Vector2 position, bool is_render_on_ui = false) : Character(position, is_render_on_ui) {
		on_init();
	};

	~GloomshroomCharacter() = default;

private:
	const int attack_ex_duration = 3000;
	bool is_attacking_ex = false;
	bool is_spwan_bubble = false;

	Timer timer_attack_ex;
	Timer timer_spwan_bubble_ex;

private:

	void On_Attack() override;
	void On_Attack_Ex() override;


};

