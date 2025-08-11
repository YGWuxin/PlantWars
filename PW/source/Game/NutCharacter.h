#pragma once
#include "Character.h"

class CharacterManger;

class NutCharacter : public Character
{
	friend class CharacterManger;

public:

	//��ɫ���ݸ���
	void on_update(float delta) override;

	//��ɫ����ʱ�ĳ�ʼ��
	void on_init() override;

	void explode();

	void on_die() override;

	void subtract_hp(int value) override;


protected:
	NutCharacter(Vector2 position, bool is_render_on_ui = false) : Character(position, is_render_on_ui) {
		on_init();
	};

	~NutCharacter() = default;


private:


	void On_Attack() override;
	void On_Attack_Ex() override;

private:
	const int explode_damge = 15;
	Timer timer_recover_hp;
	Timer timer_recover_mp;

};

