#include "NutCharacter.h"
#include "StateMachine.h"
#include <iostream>
#include "StateNode.h"
#include <functional>
#include <string>
#include "BulletPool.h"
#include "AudioManger.h"
#include "Bullet.h"
#include "SceneManger.h"
#include "NutStates.h"


typedef Character Super;
using namespace std;

void NutCharacter::on_init()
{
	Super::on_init();
	set_collision_size({ 75 , 80 });

	collision_offset_y = -5;

	if (state_machine)
	{
		//Íù×´Ì¬»úÖÐ×¢²á¶ÔÓ¦×´Ì¬×´Ì¬
		state_machine->register_state("idle", new NutIdleState(state_machine));
		state_machine->register_state("run", new  NutRunState(state_machine));
		state_machine->register_state("att_ex", new  NutAttExState(state_machine));
		state_machine->register_state("die", new  NutDieState(state_machine));
		state_machine->set_entry("idle");
		current_movement_state = MovementState::Idle;
	}

	set_run_velocity(0.3f);

	timer_recover_hp.set_wait_time(1200);
	timer_recover_hp.set_callback([&]() {
		if (hp <= 0)
			return;
		hp += 2;
		if (hp > 100)
			hp = 100;
		});

	timer_recover_mp.set_wait_time(1000);
	timer_recover_mp.set_callback([&]() {
		if (hp <= 0)
			return;
		mp += 10;
		if (mp > 100)
			mp = 100;
		});
}

void NutCharacter::explode()
{
	BulletPool::GetInstance().spawn_explode(this);
	SceneManger::GetInstance().get_main_camera()->Shake(8, 200, 1);
	subtract_hp(explode_damge);
	set_to_invulnerable(true);
	can_attack_ex = true;
	can_attack = true;
}

void NutCharacter::on_update(float delta)
{
	Super::on_update(delta);
	timer_recover_hp.on_update(delta);
	timer_recover_mp.on_update(delta);
}


void NutCharacter::on_die()
{
	Character::on_die();
	timer_recover_hp.pause();
	timer_recover_mp.pause();
}


void NutCharacter::subtract_hp(int value)
{
	Character::subtract_hp(value);
	add_mp(10);
}


void NutCharacter::On_Attack()
{
	if (!can_attack)
		return;
	can_attack = false;
	timer_attack_cd.restart();
	Vector2 position = get_current_posistion();
	
	if(is_face_rigth)
		position.x += 150;
	else
		position.x -= 150;

	set_current_posistion(position);
	AudioManger::GetInstance().PlaySoundAudio("res/sound/nut_dash.wav", false);
}


void NutCharacter::On_Attack_Ex()
{
	if (!on_ground || mp < 100 || !can_attack_ex)
		return;
	can_attack_ex = false;
	can_attack = false;
	mp = 0;
	current_movement_state = Character::MovementState::Attack_ex;
	AudioManger::GetInstance().PlaySoundAudio("res/sound/nut_explode1.mp3", false);
	set_velocity_x(0);
}

