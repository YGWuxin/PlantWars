#pragma once

#include <graphics.h>	
#include <string>
#include <functional>
#include <vector>
#include "Character.h"
#include "CharacterManger.h"
#include "PlayerControllerManger.h"
#include "StatusBar.h"

using namespace std;

class PlayerControllerManger;


class Controller
{
	friend class PlayerControllerManger;

public:
	PlayerControllerManger::PlayerType get_type() { return player_type; }

	//设置被控制的角色
	void Possess(Character* character);

	//获取被控制的角色
	Character* get_owned_character() { return controlled_character; }

	//解除被控制的角色
	void UnPossess(bool isDestroy = false);

	//检查控制器的输入事件
	void check_input(const ExMessage& msg);

	void add_input_event_map(unsigned char vk_code, Character::KeyState key_state, function<void()> event);
	void add_input_event_map(unsigned char vk_code, string event_name, Character::KeyState key_state);

	void clear_input_event_map() { InputEventMap_List.clear(); }

	void disable_input() { can_input = false; }

	void enable_input() { can_input = true; }

	CharacterManger::CharacterType get_character_type() { return character_type; }

	void set_character_type(CharacterManger::CharacterType type) { character_type = type; }

	StatusBar* get_status_bar() { return status_bar; }

	void set_status_bar(StatusBar* bar) { status_bar = bar; }

private:
	Controller(PlayerControllerManger::PlayerType player_type)
	{
		this->player_type = player_type;
	};
	~Controller() = default;

private:
	struct InputEventMap
	{
		unsigned char vk_code;
		string event_name;
		Character::KeyState key_state;
		function<void()> event;
		InputEventMap(unsigned char code, const string name, Character::KeyState state, function<void()> ev)
			: vk_code(code), event_name(name), key_state(state), event(ev) {}
	};
	CharacterManger::CharacterType character_type = CharacterManger::CharacterType::Invalid;

	Character* controlled_character = nullptr;
	std::vector<InputEventMap> InputEventMap_List;

	PlayerControllerManger::PlayerType player_type = PlayerControllerManger::PlayerType::None;

	StatusBar* status_bar = nullptr;

	bool can_input = true;				//是否可以输入

};

