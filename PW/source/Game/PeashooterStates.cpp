#include "PeashooterStates.h"
#include "ResourcesManger.h"
#include "../Res/Animation.h"
#include "StateMachine.h"
#include "Character.h"

/* Íñ¶ºÉäÊÖ´ı»ú×´Ì¬  */
void PeashooterIdleState::on_enter()
{
	if (!own_state_machine)
		return;
	
	character = dynamic_cast<PeashooterCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;
	

	if (!loadedAnimation)
	{
		loadedAnimation = true;
		
		peashooter_idle_animtaion_right = new Animation();
		peashooter_idle_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_peashooter_idle_right"));
		peashooter_idle_animtaion_right->set_interval(70);
		peashooter_idle_animtaion_right->set_loop(true);

		peashooter_idle_animtaion_left = new Animation();
		peashooter_idle_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_peashooter_idle_left"));
		peashooter_idle_animtaion_left->set_interval(70);
		peashooter_idle_animtaion_left->set_loop(true);
	}
	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? peashooter_idle_animtaion_right : peashooter_idle_animtaion_left);
}


void PeashooterIdleState::on_update(float delta)
{
	if (!character)
		return;
	character->set_current_animation(character->get_is_face_rigth() ? peashooter_idle_animtaion_right : peashooter_idle_animtaion_left);

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

void PeashooterIdleState::on_exit()
{
	peashooter_idle_animtaion_right->reset();
	peashooter_idle_animtaion_left->reset();
}



/* Íñ¶ºÉä±¼ÅÜ×´Ì¬  */
void PeashooterRunState::on_enter()
{
	if (!own_state_machine)
		return;

	character = dynamic_cast<PeashooterCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;

	if (!loadedAnimation)
	{
		loadedAnimation = true;

		peashooter_run_animtaion_right = new Animation();
		peashooter_run_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_peashooter_run_right"));
		peashooter_run_animtaion_right->set_interval(80);
		peashooter_run_animtaion_right->set_loop(true);

		peashooter_run_animtaion_left = new Animation();
		peashooter_run_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_peashooter_run_left"));
		peashooter_run_animtaion_left->set_interval(80);
		peashooter_run_animtaion_left->set_loop(true);

	}
	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? peashooter_run_animtaion_right : peashooter_run_animtaion_left);
}


void PeashooterRunState::on_update(float delta)
{
	if (!character)
		return;
	character->set_current_animation(character->get_is_face_rigth() ? peashooter_run_animtaion_right : peashooter_run_animtaion_left);

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

void PeashooterRunState::on_exit()
{
	peashooter_run_animtaion_right->reset();
	peashooter_run_animtaion_left->reset();
}



/* Íñ¶ºÉäÌØÊâ¹¥»÷×´Ì¬  */
void PeashooterAttExState::on_enter()
{
	if (!own_state_machine)
		return;

	character = dynamic_cast<PeashooterCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;

	if (!loadedAnimation)
	{

		peashooter_attack_ex_animtaion_right = new Animation();
		peashooter_attack_ex_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_peashooter_attack_ex_right"));
		peashooter_attack_ex_animtaion_right->set_interval(80);
		peashooter_attack_ex_animtaion_right->set_loop(true);

		peashooter_attack_ex_animtaion_left = new Animation();
		peashooter_attack_ex_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_peashooter_attack_ex_left"));
		peashooter_attack_ex_animtaion_left->set_interval(80);
		peashooter_attack_ex_animtaion_left->set_loop(true);

	}

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? peashooter_attack_ex_animtaion_right : peashooter_attack_ex_animtaion_left);

}


void PeashooterAttExState::on_update(float delta)
{
	character->set_current_animation(character->get_is_face_rigth() ? peashooter_attack_ex_animtaion_right : peashooter_attack_ex_animtaion_left);

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

void PeashooterAttExState::on_exit()
{
	peashooter_attack_ex_animtaion_right->reset();
	peashooter_attack_ex_animtaion_left->reset();
}



/* Íñ¶ºÉäÊÖËÀÍö×´Ì¬  */
void PeashooterDieState::on_enter()
{
	if (!own_state_machine)
		return;

	character = dynamic_cast<PeashooterCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;

	if (!loadedAnimation)
	{

		peashooter_die_animtaion_right = new Animation();
		peashooter_die_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_peashooter_die_right"));
		peashooter_die_animtaion_right->set_interval(80);
		peashooter_die_animtaion_right->set_loop(false);

		peashooter_die_animtaion_left = new Animation();
		peashooter_die_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_peashooter_die_left"));
		peashooter_die_animtaion_left->set_interval(80);
		peashooter_die_animtaion_left->set_loop(false);

	}

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? peashooter_die_animtaion_right : peashooter_die_animtaion_left);

}


void PeashooterDieState::on_update(float delta)
{
	character->set_current_animation(character->get_is_face_rigth() ? peashooter_die_animtaion_right : peashooter_die_animtaion_left);
}

void PeashooterDieState::on_exit()
{
	peashooter_die_animtaion_right->reset();
	peashooter_die_animtaion_left->reset();
}










