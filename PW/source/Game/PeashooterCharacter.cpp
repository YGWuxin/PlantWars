#include "PeashooterCharacter.h"
#include "StateMachine.h"
#include <iostream>
#include "StateNode.h"
#include "PeashooterStates.h"
#include <functional>
#include <string>
#include "BulletPool.h"
#include "AudioManger.h"
#include "Bullet.h"
#include "SceneManger.h"


typedef Character Super;

using namespace std;

void PeashooterCharacter::on_init()
{
	Super::on_init();
	set_collision_size({ 60 , 72 });

	collision_offset_y = -8;

	if (state_machine)
	{
		//Íù×´Ì¬»úÖÐ×¢²á¶ÔÓ¦×´Ì¬×´Ì¬
		state_machine->register_state("idle", new PeashooterIdleState(state_machine));
		state_machine->register_state("run",new PeashooterRunState(state_machine));
		state_machine->register_state("att_ex",new PeashooterAttExState(state_machine));
		state_machine->register_state("die", new PeashooterDieState(state_machine));
		state_machine->set_entry("idle");
		current_movement_state = MovementState::Idle;
	}

	timer_attack_ex.set_wait_time(attack_ex_duration);
	timer_attack_ex.set_one_shot(true);
	timer_attack_ex.set_callback([&] {
		this->can_attack_ex = true;
		this->is_attacking_ex = false;
		this->is_spwan_pea = false;
		this->current_movement_state = Character::MovementState::Idle;
		});

	timer_spwan_pea_ex.set_wait_time(100);
	timer_spwan_pea_ex.set_callback([&] {
		Bullet* bullet = BulletPool::GetInstance().spawn_pea_bullet(this, speed_pea_ex);
		//AudioManger::GetInstance().PlaySoundAudio("res/sound/pea_shoot_1.mp3", false);
		bullet->set_mp(0);
		SceneManger::GetInstance().get_main_camera()->Shake(5,80,1);
		});

	timer_spwan_pea_delay.set_wait_time(500);
	timer_spwan_pea_delay.pause();
	timer_spwan_pea_delay.set_one_shot(true);
	timer_spwan_pea_delay.set_callback([&] {
		this->timer_spwan_pea_delay.pause();
		this->timer_attack_ex.restart();
		this->is_spwan_pea = true;
		this->timer_spwan_pea_ex.restart();
		});

}


void PeashooterCharacter::on_update(float delta)
{
	Super::on_update(delta);

	timer_spwan_pea_delay.on_update(delta);
	timer_attack_ex.on_update(delta);

	if (is_spwan_pea)
		timer_spwan_pea_ex.on_update(delta);

}


void PeashooterCharacter::On_Attack()
{
	if (!can_attack || is_attacking_ex)
		return;
	can_attack = false;
	timer_attack_cd.restart();
	Bullet* bullet = BulletPool::GetInstance().spawn_pea_bullet(this,speed_pea);
	bullet->set_mp(20);
	switch (rand() % 2)
	{
	case 0:
		AudioManger::GetInstance().PlaySoundAudio("res/sound/pea_shoot_1.mp3",false);
		break;
	case 1:
		AudioManger::GetInstance().PlaySoundAudio("res/sound/pea_shoot_2.mp3", false);
		break;
	default:
		break;
	}
}


void PeashooterCharacter::On_Attack_Ex()
{
	if (!on_ground || !can_attack_ex || mp < 100)
		return;

	AudioManger::GetInstance().PlaySoundAudio("res/sound/pea_shoot_ex_start.mp3", false);
	AudioManger::GetInstance().PlaySoundAudio("res/sound/pea_shoot_ex.mp3", false);

	can_attack_ex = false;
	is_attacking_ex = true;
	mp = 0;

	current_movement_state = MovementState::Attack_ex;
	timer_spwan_pea_delay.restart();
	timer_spwan_pea_delay.resume();
	set_velocity_x(0);
}
