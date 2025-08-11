#include "Controller.h"
#include "Character.h"
#include "CharacterManger.h"
#include "PeashooterCharacter.h"
#include <cstdio>
#include <functional>

using namespace std;


void Controller::Possess(Character* character)
{
	if (!character)
		return;
	if (controlled_character)
		controlled_character->set_own_controller(nullptr);
	enable_input();
	character->set_own_controller(this);
	controlled_character = character;

}

void Controller::UnPossess(bool isDestroy)
{
	if (!controlled_character)
		return;
	controlled_character->set_owned_controller(nullptr);
	if (isDestroy)
		CharacterManger::GetInstance().destory_character(controlled_character);
	controlled_character = nullptr;
}

void Controller::check_input(const ExMessage& msg)
{
	if (!can_input)
		return;
	if (msg.message == WM_KEYUP)
	{
		for (std::vector<InputEventMap>::const_iterator it = InputEventMap_List.cbegin(); it != InputEventMap_List.cend(); ++it) {
			if (msg.vkcode != it->vk_code || it->key_state != Character::KeyState::KEY_UP) {
				continue;
			}
			if (it->event)
			{
				it->event();
			}
			if (controlled_character)
			{
				controlled_character->executeInputEvent(it->event_name, Character::KeyState::KEY_UP);
			}
		}
	}
	else if (msg.message == WM_KEYDOWN)
	{
		for (std::vector<InputEventMap>::const_iterator it = InputEventMap_List.cbegin(); it != InputEventMap_List.cend(); ++it) {
			if (msg.vkcode != it->vk_code || it->key_state != Character::KeyState::KEY_DOWN) {
				continue;
			}
			if (it->event)
			{
				it->event();
			}
			if (controlled_character)
			{
				controlled_character->executeInputEvent(it->event_name, Character::KeyState::KEY_DOWN);
			}
		}
	}
}


void Controller::add_input_event_map(unsigned char vk_code, Character::KeyState key_state, function<void()> event)
{
	InputEventMap_List.emplace_back(vk_code, "NULL", key_state, event);
}


void Controller::add_input_event_map(unsigned char vk_code, string event_name, Character::KeyState key_state)
{
	InputEventMap_List.emplace_back(vk_code, event_name, key_state, nullptr);
}
