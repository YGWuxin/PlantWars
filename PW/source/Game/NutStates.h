#pragma once
#include "StateNode.h"
#include "NutCharacter.h"

class StateMachine;
class NutCharacter;

class NutIdleState : public StateNode
{
public:
	NutIdleState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~NutIdleState() {
		if (nut_idle_animtaion_right)
			delete nut_idle_animtaion_right;
		if (nut_idle_animtaion_left)
			delete nut_idle_animtaion_left;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation* nut_idle_animtaion_right = nullptr;
	Animation* nut_idle_animtaion_left = nullptr;
	NutCharacter* character = nullptr;

};


class NutRunState : public StateNode
{
public:
	NutRunState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~NutRunState() {
		if (nut_run_animtaion_right)
			delete nut_run_animtaion_right;
		if (nut_run_animtaion_left)
			delete nut_run_animtaion_left;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation* nut_run_animtaion_right = nullptr;
	Animation* nut_run_animtaion_left = nullptr;
	NutCharacter* character = nullptr;

};


class NutAttExState : public StateNode
{
public:
	NutAttExState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~NutAttExState() {
		if (nut_attack_ex_animtaion_right)
			delete nut_attack_ex_animtaion_right;
		if (nut_attack_ex_animtaion_left)
			delete nut_attack_ex_animtaion_left;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation* nut_attack_ex_animtaion_right = nullptr;
	Animation* nut_attack_ex_animtaion_left = nullptr;
	NutCharacter* character = nullptr;

};



class NutDieState : public StateNode
{
public:
	NutDieState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~NutDieState()
	{
		if (nut_die_animtaion_right)
			delete nut_die_animtaion_right;
		if (nut_die_animtaion_left)
			delete nut_die_animtaion_left;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;

private:
	NutCharacter* character = nullptr;
	Animation* nut_die_animtaion_right = nullptr;
	Animation* nut_die_animtaion_left = nullptr;
};

