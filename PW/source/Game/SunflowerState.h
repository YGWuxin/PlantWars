#pragma once

#include "StateNode.h"
#include "SunflowerCharacter.h"

class StateMachine;
class Animation;

class SunflowerIdleState :
    public StateNode
{
public:
	SunflowerIdleState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~SunflowerIdleState() {
		if (sunflower_idle_animtaion_left)
			delete sunflower_idle_animtaion_left;
		if (sunflower_idle_animtaion_right)
			delete sunflower_idle_animtaion_right;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation* sunflower_idle_animtaion_left = nullptr;
	Animation* sunflower_idle_animtaion_right = nullptr;
	SunflowerCharacter* character = nullptr;

};



class SunflowerRunState :
	public StateNode
{
public:
	SunflowerRunState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~SunflowerRunState() {
		if (sunflower_run_animtaion_left)
			delete sunflower_run_animtaion_left;
		if (sunflower_run_animtaion_right)
			delete sunflower_run_animtaion_right;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation* sunflower_run_animtaion_left = nullptr;
	Animation* sunflower_run_animtaion_right = nullptr;
	SunflowerCharacter* character = nullptr;
};




class SunflowerAttackExState :
	public StateNode
{
public:
	SunflowerAttackExState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~SunflowerAttackExState() {
		if (sunflower_attack_ex_animtaion_left)
			delete sunflower_attack_ex_animtaion_left;
		if (sunflower_attack_ex_animtaion_right)
			delete sunflower_attack_ex_animtaion_right;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation* sunflower_attack_ex_animtaion_left = nullptr;
	Animation* sunflower_attack_ex_animtaion_right = nullptr;
	SunflowerCharacter* character = nullptr;
};



class SunflowerDieState :
	public StateNode
{
public:
	SunflowerDieState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~SunflowerDieState() {
		if (sunflower_die_animtaion_left)
			delete sunflower_die_animtaion_left;
		if (sunflower_die_animtaion_right)
			delete sunflower_die_animtaion_right;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation* sunflower_die_animtaion_left = nullptr;
	Animation* sunflower_die_animtaion_right = nullptr;
	SunflowerCharacter* character = nullptr;
};

