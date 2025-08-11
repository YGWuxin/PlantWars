#include "GloomshroomStates.h"
#include "ResourcesManger.h"
#include "../Res/Animation.h"
#include "StateMachine.h"
#include "Character.h"


/* ´óÅç¹½´ı»ú×´Ì¬  */
void GloomshroomIdleState::on_enter()
{
	if (!own_state_machine)
		return;

	character = dynamic_cast<GloomshroomCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;


	if (!loadedAnimation)
	{
		loadedAnimation = true;

		gloomshroom_idle_animtaion_right = new Animation();
		gloomshroom_idle_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_gloomshroom_idle_right"));
		gloomshroom_idle_animtaion_right->set_interval(100);
		gloomshroom_idle_animtaion_right->set_loop(true);

		gloomshroom_idle_animtaion_left = new Animation();
		gloomshroom_idle_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_gloomshroom_idle_left"));
		gloomshroom_idle_animtaion_left->set_interval(100);
		gloomshroom_idle_animtaion_left->set_loop(true);
	}
	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? gloomshroom_idle_animtaion_right : gloomshroom_idle_animtaion_left);
}


void GloomshroomIdleState::on_update(float delta)
{
	if (!character)
		return;
	character->set_current_animation(character->get_is_face_rigth() ? gloomshroom_idle_animtaion_right : gloomshroom_idle_animtaion_left);

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

void GloomshroomIdleState::on_exit()
{
	gloomshroom_idle_animtaion_right->reset();
	gloomshroom_idle_animtaion_left->reset();
}


/* ´óÅç¹½±¼ÅÜ×´Ì¬  */
void GloomshroomRunState::on_enter()
{
	if (!own_state_machine)
		return;

	character = dynamic_cast<GloomshroomCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;

	if (!loadedAnimation)
	{
		loadedAnimation = true;

		gloomshroom_run_animtaion_right = new Animation();
		gloomshroom_run_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_gloomshroom_run_right"));
		gloomshroom_run_animtaion_right->set_interval(100);
		gloomshroom_run_animtaion_right->set_loop(true);

		gloomshroom_run_animtaion_left = new Animation();
		gloomshroom_run_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_gloomshroom_run_left"));
		gloomshroom_run_animtaion_left->set_interval(100);
		gloomshroom_run_animtaion_left->set_loop(true);

	}
	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? gloomshroom_run_animtaion_right : gloomshroom_run_animtaion_left);
}


void GloomshroomRunState::on_update(float delta)
{
	if (!character)
		return;
	character->set_current_animation(character->get_is_face_rigth() ? gloomshroom_run_animtaion_right : gloomshroom_run_animtaion_left);

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

void GloomshroomRunState::on_exit()
{
	gloomshroom_run_animtaion_right->reset();
	gloomshroom_run_animtaion_left->reset();
}


/* ´óÅç¹½ÌØÊâ¹¥»÷×´Ì¬  */
void GloomshroomAttExState::on_enter()
{
	if (!own_state_machine)
		return;

	character = dynamic_cast<GloomshroomCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;

	if (!loadedAnimation)
	{

		gloomshroom_attack_ex_animtaion_right = new Animation();
		gloomshroom_attack_ex_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_gloomshroom_attack_ex_right"));
		gloomshroom_attack_ex_animtaion_right->set_interval(80);
		gloomshroom_attack_ex_animtaion_right->set_loop(true);

		gloomshroom_attack_ex_animtaion_left = new Animation();
		gloomshroom_attack_ex_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_gloomshroom_attack_ex_left"));
		gloomshroom_attack_ex_animtaion_left->set_interval(80);
		gloomshroom_attack_ex_animtaion_left->set_loop(true);

	}

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? gloomshroom_attack_ex_animtaion_right : gloomshroom_attack_ex_animtaion_left);

}


void GloomshroomAttExState::on_update(float delta)
{
	character->set_current_animation(character->get_is_face_rigth() ? gloomshroom_attack_ex_animtaion_right : gloomshroom_attack_ex_animtaion_left);

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

void GloomshroomAttExState::on_exit()
{
	gloomshroom_attack_ex_animtaion_right->reset();
	gloomshroom_attack_ex_animtaion_left->reset();
}




/* ´óÅç¹½ËÀÍö×´Ì¬  */
void GloomshroomDieState::on_enter()
{
	if (!own_state_machine)
		return;

	character = dynamic_cast<GloomshroomCharacter*>(own_state_machine->get_own_character());;

	if (!character)
		return;

	if (!loadedAnimation)
	{

		gloomshroom_die_animtaion_right = new Animation();
		gloomshroom_die_animtaion_right->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_gloomshroom_die_left"));
		gloomshroom_die_animtaion_right->set_interval(80);
		gloomshroom_die_animtaion_right->set_loop(false);

		gloomshroom_die_animtaion_left = new Animation();
		gloomshroom_die_animtaion_left->add_animation(ResourcesManger::GetInstance().find_atlas("atlas_gloomshroom_die_right"));
		gloomshroom_die_animtaion_left->set_interval(80);
		gloomshroom_die_animtaion_left->set_loop(false);

	}

	if (character)
		character->set_current_animation(character->get_is_face_rigth() ? gloomshroom_die_animtaion_right : gloomshroom_die_animtaion_left);

}


void GloomshroomDieState::on_update(float delta)
{
	character->set_current_animation(character->get_is_face_rigth() ? gloomshroom_die_animtaion_right : gloomshroom_die_animtaion_left);
}

void GloomshroomDieState::on_exit()
{
	gloomshroom_die_animtaion_right->reset();
	gloomshroom_die_animtaion_left->reset();
}
