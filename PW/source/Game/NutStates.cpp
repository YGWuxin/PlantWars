#include "NutStates.h"
#include "ResourcesManger.h"
#include "../Res/Animation.h"
#include "StateMachine.h"
#include "Character.h"


/* ¼á¸ç´ı»ú×´Ì¬  */
void NutIdleState::on_enter()
{
	if (!own_state_machine)
		return;

	character = dynamic_cast<NutCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;


	if (!loadedAnimation)
	{
		loadedAnimation = true;

		nut_idle_animtaion_right = new Animation();
		nut_idle_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_nut_idle_right"));
		nut_idle_animtaion_right->set_interval(100);
		nut_idle_animtaion_right->set_loop(true);

		nut_idle_animtaion_left = new Animation();
		nut_idle_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_nut_idle_left"));
		nut_idle_animtaion_left->set_interval(100);
		nut_idle_animtaion_left->set_loop(true);
	}
	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? nut_idle_animtaion_right : nut_idle_animtaion_left);
}


void NutIdleState::on_update(float delta)
{
	if (!character)
		return;
	character->set_current_animation(character->get_is_face_rigth() ? nut_idle_animtaion_right : nut_idle_animtaion_left);

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

void NutIdleState::on_exit()
{
	nut_idle_animtaion_right->reset();
	nut_idle_animtaion_left->reset();
}


/* ¼á¸ç±¼ÅÜ×´Ì¬  */
void NutRunState::on_enter()
{
	if (!own_state_machine)
		return;

	character = dynamic_cast<NutCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;

	if (!loadedAnimation)
	{
		loadedAnimation = true;

		nut_run_animtaion_right = new Animation();
		nut_run_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_nut_run_right"));
		nut_run_animtaion_right->set_interval(100);
		nut_run_animtaion_right->set_loop(true);

		nut_run_animtaion_left = new Animation();
		nut_run_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_nut_run_left"));
		nut_run_animtaion_left->set_interval(100);
		nut_run_animtaion_left->set_loop(true);

	}
	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? nut_run_animtaion_right : nut_run_animtaion_left);
}


void NutRunState::on_update(float delta)
{
	if (!character)
		return;
	character->set_current_animation(character->get_is_face_rigth() ? nut_run_animtaion_right : nut_run_animtaion_left);

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

void NutRunState::on_exit()
{
	nut_run_animtaion_right->reset();
	nut_run_animtaion_left->reset();
}


/* ¼á¸çÌØÊâ¹¥»÷×´Ì¬  */
void NutAttExState::on_enter()
{
	if (!own_state_machine)
		return;

	character = dynamic_cast<NutCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;

	if (!loadedAnimation)
	{

		nut_attack_ex_animtaion_right = new Animation();
		nut_attack_ex_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_nut_attack_ex_left"));
		nut_attack_ex_animtaion_right->set_interval(100);
		nut_attack_ex_animtaion_right->set_loop(false);
		nut_attack_ex_animtaion_right->set_on_finished_callback([&]() {
			this->character->current_movement_state = Character::MovementState::Idle;
			this->character->explode();
			});

		nut_attack_ex_animtaion_left = new Animation();
		nut_attack_ex_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_nut_attack_ex_right"));
		nut_attack_ex_animtaion_left->set_interval(100);
		nut_attack_ex_animtaion_left->set_loop(false);
		nut_attack_ex_animtaion_left->set_on_finished_callback([&](){
			this->character->current_movement_state = Character::MovementState::Idle;
			this->character->explode();
			});
	}

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? nut_attack_ex_animtaion_left : nut_attack_ex_animtaion_right);

}


void NutAttExState::on_update(float delta)
{
	//character->set_current_animation(character->get_is_face_rigth() ? nut_attack_ex_animtaion_left : nut_attack_ex_animtaion_right);

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

void NutAttExState::on_exit()
{
	nut_attack_ex_animtaion_left->reset();
	nut_attack_ex_animtaion_right->reset();
}




/* ¼á¸çËÀÍö×´Ì¬  */
void NutDieState::on_enter()
{
	if (!own_state_machine)
		return;

	character = dynamic_cast<NutCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;

	if (!loadedAnimation)
	{

		nut_die_animtaion_right = new Animation();
		nut_die_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_nut_die_left"));
		nut_die_animtaion_right->set_interval(80);
		nut_die_animtaion_right->set_loop(false);

		nut_die_animtaion_left = new Animation();
		nut_die_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_nut_die_right"));
		nut_die_animtaion_left->set_interval(80);
		nut_die_animtaion_left->set_loop(false);

	}

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? nut_die_animtaion_right : nut_die_animtaion_left);

}


void NutDieState::on_update(float delta)
{
	character->set_current_animation(character->get_is_face_rigth() ? nut_die_animtaion_right : nut_die_animtaion_left);
}

void NutDieState::on_exit()
{
	nut_die_animtaion_right->reset();
	nut_die_animtaion_left->reset();
}
