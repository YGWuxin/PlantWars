#pragma once
#include "Character.h"

class CharacterManger;

class SunflowerCharacter :
    public Character
{
	friend class CharacterManger;

public:
	
	//角色数据更新
	void on_update(float delta) override;

	//角色创建时的初始化
	void on_init() override;

protected:
	SunflowerCharacter(Vector2 position, bool is_render_on_ui = false) : Character(position, is_render_on_ui) { on_init(); };

	~SunflowerCharacter();


private:
	void On_Attack() override;
	void On_Attack_Ex() override;

public:
	

private:
	Timer timer_attack_ex;						//普通攻击冷却时间

	Animation animation_sun_text;
	RenderUI* ui_sun_text = nullptr;


};

