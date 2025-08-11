#include "GloomshroomCharacter.h"
#include "StateMachine.h"
#include <iostream>
#include "StateNode.h"
#include <functional>
#include <string>
#include "BulletPool.h"
#include "AudioManger.h"
#include "Bullet.h"
#include "SceneManger.h"
#include "GloomshroomStates.h"

typedef Character Super;
using namespace std;

void GloomshroomCharacter::on_init()
{

	Super::on_init();
	set_collision_size({ 75 , 80 });
	
	collision_offset_y = -1;

	if (state_machine)
	{
		//Íù×´Ì¬»úÖÐ×¢²á¶ÔÓ¦×´Ì¬×´Ì¬
		state_machine->register_state("idle", new GloomshroomIdleState(state_machine));
		state_machine->register_state("run", new GloomshroomRunState(state_machine));
		state_machine->register_state("att_ex", new GloomshroomAttExState(state_machine));
		state_machine->register_state("die", new GloomshroomDieState(state_machine));
		state_machine->set_entry("idle");
		current_movement_state = MovementState::Idle;
	}

	timer_attack_ex.set_wait_time(attack_ex_duration);
	timer_attack_ex.set_one_shot(true);
	timer_attack_ex.set_callback([&] {
		this->can_attack_ex = true;
		this->is_attacking_ex = false;
		this->is_spwan_bubble = false;
		this->can_jump = true;
		this->current_movement_state = Character::MovementState::Idle;
		});


	timer_spwan_bubble_ex.set_wait_time(500);
	timer_spwan_bubble_ex.set_callback([&] {
		Bullet* bullet = BulletPool::GetInstance().spawn_bubble_ex_bullet(this);
		//AudioManger::GetInstance().PlaySoundAudio("res/sound/pea_shoot_1.mp3", false);
		bullet->set_mp(0);
		SceneManger::GetInstance().get_main_camera()->Shake(5, 500, 1);
		});



}



void GloomshroomCharacter::on_update(float delta)
{
	Super::on_update(delta);

	timer_attack_ex.on_update(delta);

	if (is_spwan_bubble)
		timer_spwan_bubble_ex.on_update(delta);
}


void GloomshroomCharacter::On_Attack()
{
	if (!can_attack || is_attacking_ex)
		return;
	can_attack = false;
	timer_attack_cd.set_wait_time(300);
	timer_attack_cd.restart();
	Bullet* bullet = BulletPool::GetInstance().spawn_bubble_bullet(this);
	if (bullet)
	{
		bullet->set_mp(20);
		bullet->set_damage(8);
	}
	AudioManger::GetInstance().PlaySoundAudio("res/sound/bubbles_shot.mp3", false);
}


void GloomshroomCharacter::On_Attack_Ex()
{
	if (!on_ground || !can_attack_ex || mp < 100)
		return;

	can_attack_ex = false;
	is_attacking_ex = true;
	is_spwan_bubble = true;
	can_jump = false;
	mp = 0;

	AudioManger::GetInstance().PlaySoundAudio("res/sound/bubbles_shot_ex.mp3", 200,false);
	timer_attack_ex.restart();
	Bullet* bullet = BulletPool::GetInstance().spawn_bubble_ex_bullet(this);
	bullet->set_mp(0);
	SceneManger::GetInstance().get_main_camera()->Shake(5, 500, 1);

	current_movement_state = MovementState::Attack_ex;
}

