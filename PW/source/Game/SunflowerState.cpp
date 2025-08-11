#include "SunflowerState.h"
#include "ResourcesManger.h"
#include "../Res/Animation.h"
#include "StateMachine.h"
#include "Character.h"

/* 龙日葵待机状态  */
void SunflowerIdleState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<SunflowerCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;

	if (!loadedAnimation)
	{
		loadedAnimation = true;

		sunflower_idle_animtaion_right = new Animation();
		sunflower_idle_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_sunflower_idle_right"));
		sunflower_idle_animtaion_right->set_interval(80);
		sunflower_idle_animtaion_right->set_loop(true);

		sunflower_idle_animtaion_left = new Animation();
		sunflower_idle_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_sunflower_idle_left"));
		sunflower_idle_animtaion_left->set_interval(80);
		sunflower_idle_animtaion_left->set_loop(true);
	}

	//设置当前动画为朝右
	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? sunflower_idle_animtaion_right : sunflower_idle_animtaion_left);
}


void SunflowerIdleState::on_update(float delta)
{
	if (!character)
		return;
	character->set_current_animation(character->get_is_face_rigth() ? sunflower_idle_animtaion_right : sunflower_idle_animtaion_left);

	if (character->current_movement_state == Character::MovementState::Run)
	{
		character->get_state_machine()->switch_to("run");
	}
	else if (character->current_movement_state == Character::MovementState::Attack_ex)
	{
		character->get_state_machine()->switch_to("att_ex");
	}
	else if (character->current_movement_state == Character::MovementState::Die)
	{
		character->get_state_machine()->switch_to("die");
	}
}

void SunflowerIdleState::on_exit()
{
	sunflower_idle_animtaion_right->reset();
	sunflower_idle_animtaion_left->reset();
}


/* 龙日葵移动状态  */
void SunflowerRunState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<SunflowerCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;

	if (!loadedAnimation)
	{
		loadedAnimation = true;

		sunflower_run_animtaion_right = new Animation();
		sunflower_run_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_sunflower_run_right"));
		sunflower_run_animtaion_right->set_interval(80);
		sunflower_run_animtaion_right->set_loop(true);

		sunflower_run_animtaion_left = new Animation();
		sunflower_run_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_sunflower_run_left"));
		sunflower_run_animtaion_left->set_interval(80);
		sunflower_run_animtaion_left->set_loop(true);

	}

	//设置当前动画为朝右
	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? sunflower_run_animtaion_right : sunflower_run_animtaion_left);
}


void SunflowerRunState::on_update(float delta)
{
	if (!character)
		return;
	character->set_current_animation(character->get_is_face_rigth() ? sunflower_run_animtaion_right : sunflower_run_animtaion_left);

	if (character->current_movement_state == Character::MovementState::Idle)
	{
		character->get_state_machine()->switch_to("idle");
	}
	else if (character->current_movement_state == Character::MovementState::Attack_ex)
	{
		character->get_state_machine()->switch_to("att_ex");
	}
	else if (character->current_movement_state == Character::MovementState::Die)
	{
		character->get_state_machine()->switch_to("die");
	}
}

void SunflowerRunState::on_exit()
{
	sunflower_run_animtaion_right->reset();
	sunflower_run_animtaion_left->reset();
}



/* 龙日葵特殊攻击状态  */
void SunflowerAttackExState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<SunflowerCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;

	if (!loadedAnimation)
	{
		loadedAnimation = true;

		sunflower_attack_ex_animtaion_right = new Animation();
		sunflower_attack_ex_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_sunflower_attack_ex_right"));
		sunflower_attack_ex_animtaion_right->set_interval(80);
		sunflower_attack_ex_animtaion_right->set_loop(false);
		sunflower_attack_ex_animtaion_right->set_on_finished_callback([&] {
			character->current_movement_state = Character::MovementState::Idle;
			});

		sunflower_attack_ex_animtaion_left = new Animation();
		sunflower_attack_ex_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_sunflower_attack_ex_left"));
		sunflower_attack_ex_animtaion_left->set_interval(80);
		sunflower_attack_ex_animtaion_left->set_loop(false);
		sunflower_attack_ex_animtaion_left->set_on_finished_callback([&] {
			character->current_movement_state = Character::MovementState::Idle;
			});
	}


	//设置当前动画为朝右
	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? sunflower_attack_ex_animtaion_right : sunflower_attack_ex_animtaion_left);
}


void SunflowerAttackExState::on_update(float delta)
{
	if (!character)
		return;
	if (character->current_movement_state == Character::MovementState::Idle)
	{
		character->get_state_machine()->switch_to("idle");
	}
	else if (character->current_movement_state == Character::MovementState::Run)
	{
		character->get_state_machine()->switch_to("run");
	}
	else if (character->current_movement_state == Character::MovementState::Die)
	{
		character->get_state_machine()->switch_to("die");
	}
}

void SunflowerAttackExState::on_exit()
{
	sunflower_attack_ex_animtaion_right->reset();
	sunflower_attack_ex_animtaion_left->reset();
}



/* 龙日葵死亡状态  */
void SunflowerDieState::on_enter()
{
	if (!own_state_machine)
		return;
	character = dynamic_cast<SunflowerCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;

	if (!loadedAnimation)
	{
		loadedAnimation = true;

		sunflower_die_animtaion_right = new Animation();
		sunflower_die_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_sunflower_die_right"));
		sunflower_die_animtaion_right->set_interval(80);
		sunflower_die_animtaion_right->set_loop(false);

		sunflower_die_animtaion_left = new Animation();
		sunflower_die_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_sunflower_die_left"));
		sunflower_die_animtaion_left->set_interval(80);
		sunflower_die_animtaion_left->set_loop(false);

	}

	//设置当前动画为朝右
	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? sunflower_die_animtaion_right : sunflower_die_animtaion_left);
}


void SunflowerDieState::on_update(float delta)
{
	if (!character)
		return;
	character->set_current_animation(character->get_is_face_rigth() ? sunflower_die_animtaion_right : sunflower_die_animtaion_left);

}

void SunflowerDieState::on_exit()
{
	sunflower_die_animtaion_right->reset();
	sunflower_die_animtaion_left->reset();
}

