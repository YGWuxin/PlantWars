#pragma once
#include "Character.h"

class CharacterManger;

class PeashooterCharacter
	: public Character
{
	friend class CharacterManger;

public:
	
	//角色数据更新
	void on_update(float delta) override;

	//角色创建时的初始化
	void on_init() override;

	void set_right_key(bool val) { is_right_key_down = val; }

	bool get_is_attacking_ex() { return is_attacking_ex; }

protected:
	PeashooterCharacter(Vector2 position, bool is_render_on_ui = false) : Character(position, is_render_on_ui) {
		on_init();
	};

	~PeashooterCharacter() = default;


private:
	const float speed_pea = 0.7f;
	const float speed_pea_ex = 1.4f;
	const int attack_ex_duration = 2500;

	
	bool is_attacking_ex = false;
	bool is_spwan_pea = false;

	Timer timer_attack_ex;
	Timer timer_spwan_pea_ex;
	Timer timer_spwan_pea_delay;

	void On_Attack() override;
	void On_Attack_Ex() override;

public:

};

