#pragma once
#include "Character.h"

class CharacterManger;

class SunflowerCharacter :
    public Character
{
	friend class CharacterManger;

public:
	
	//��ɫ���ݸ���
	void on_update(float delta) override;

	//��ɫ����ʱ�ĳ�ʼ��
	void on_init() override;

protected:
	SunflowerCharacter(Vector2 position, bool is_render_on_ui = false) : Character(position, is_render_on_ui) { on_init(); };

	~SunflowerCharacter();


private:
	void On_Attack() override;
	void On_Attack_Ex() override;

public:
	

private:
	Timer timer_attack_ex;						//��ͨ������ȴʱ��

	Animation animation_sun_text;
	RenderUI* ui_sun_text = nullptr;


};

