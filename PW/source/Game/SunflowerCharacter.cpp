#include "SunflowerCharacter.h"
#include "StateMachine.h"
#include <iostream>
#include "StateNode.h"
#include "SunflowerState.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "ResourcesManger.h"
#include "RenderManager.h"
#include "RenderItem.h"
#include <graphics.h>	
#include "AudioManger.h"

typedef Character Super;

SunflowerCharacter::~SunflowerCharacter()
{
	if (ui_sun_text)
		RenderManager::getInstance().destroyRenderItemUI(ui_sun_text);
}


void SunflowerCharacter::on_init()
{
	Super::on_init();

	collision_offset_y = -8;

	if (state_machine)
	{
		//Íù×´Ì¬»úÖÐÌí¼Ó¶ÔÓ¦×´Ì¬×´Ì¬
		state_machine->register_state("idle", new SunflowerIdleState(state_machine));
		state_machine->register_state("run", new SunflowerRunState(state_machine));
		state_machine->register_state("att_ex", new SunflowerAttackExState(state_machine));
		state_machine->register_state("die", new SunflowerDieState(state_machine));
		state_machine->set_entry("idle");
		current_movement_state = MovementState::Idle;
	}

	Atlas* atlas_sun_text = ResourcesManger::GetInstance().find_atlas("atlas_sun_text");
	animation_sun_text.add_animation(atlas_sun_text);
	animation_sun_text.set_interval(100);
	animation_sun_text.set_loop(false);
	animation_sun_text.set_on_finished_callback([&]() {
		BulletPool::GetInstance().spawn_sun_ex_bullet(this);
		if (ui_sun_text)
			ui_sun_text->setCanRender(false);
		animation_sun_text.pause_animation();
		can_attack_ex = true;
		can_jump = true;
		this->current_movement_state = MovementState::Idle;
		});

	ui_sun_text = RenderManager::getInstance().createRenderItemUIIamge(nullptr, { 0,0 }, 10, false);
	ui_sun_text->setCanRender(false);
	ui_sun_text->setImageSize(animation_sun_text.get_current_frame_image()->getwidth(), animation_sun_text.get_current_frame_image()->getheight());
	ui_sun_text->setRectSrc(animation_sun_text.get_current_frame_rect_src());


}

void SunflowerCharacter::on_update(float delta)
{
	Super::on_update(delta);

	if (ui_sun_text && update_animation && ui_sun_text->getCanRender())
	{
		ui_sun_text->setPosition({ position.x - size.x + 12, position.y - size.y * 2 - 10 });
		animation_sun_text.on_update(delta);
		ui_sun_text->setImage(animation_sun_text.get_current_frame_image());
	}

}


void SunflowerCharacter::On_Attack()
{
	if (!can_attack)
		return;
	can_attack = false;
	timer_attack_cd.restart();
	BulletPool::GetInstance().spawn_sun_bullet(this);
	//AudioManger::GetInstance().PlaySoundAudio("res/sound/collectSunshine.mp3", 200);
}


void SunflowerCharacter::On_Attack_Ex()
{
	if (!on_ground || !can_attack_ex || mp < 100)
		return;
	can_attack_ex = false;
	can_jump = false;
	mp = 0;

	if (ui_sun_text)
	{
		ui_sun_text->setCanRender(true);
		animation_sun_text.reset();
	}
	AudioManger::GetInstance().PlaySoundAudio("res/sound/sun_text.mp3", 400);
	current_movement_state = MovementState::Attack_ex;
	
	set_velocity_x(0);
}
