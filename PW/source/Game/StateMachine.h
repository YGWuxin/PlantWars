#pragma once
#include <string>
#include "StateNode.h"
#include <unordered_map>


using namespace std;

class Character;

class StateMachine
{
public:
	StateMachine() = default;
	~StateMachine() {
		// 遍历 unordered_map 并删除所有指针
		for (auto& pair : state_pool) {
			delete pair.second; // 删除指针指向的对象
		}
		// 清空 map
		state_pool.clear();
	};

	void on_update(float delta);

	void set_entry(const string& id);

	void switch_to(const string& id);

	void register_state(const string& id, StateNode* state_node);

	void set_own_character(Character* character)
	{
		own_character = character;
	}

	Character* get_own_character() const
	{
		return own_character;
	}

private:
	bool needInit = true;
	StateNode* current_state = nullptr;
	unordered_map<string, StateNode*> state_pool;
	Character* own_character = nullptr;

};




