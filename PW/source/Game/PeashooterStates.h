#pragma once
#include "StateNode.h"
#include "PeashooterCharacter.h"

class StateMachine;
class PeashooterCharacter;

class PeashooterIdleState
	: public StateNode
{
public:
	PeashooterIdleState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~PeashooterIdleState() {
		if (peashooter_idle_animtaion_right)
			delete peashooter_idle_animtaion_right;
		if (peashooter_idle_animtaion_left)
			delete peashooter_idle_animtaion_left;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation* peashooter_idle_animtaion_right = nullptr;
	Animation* peashooter_idle_animtaion_left = nullptr;
	PeashooterCharacter* character = nullptr;

};


class PeashooterRunState
	: public StateNode
{
public:
	PeashooterRunState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~PeashooterRunState()
	{
		if (peashooter_run_animtaion_right)
			delete peashooter_run_animtaion_right;
		if (peashooter_run_animtaion_left)
			delete peashooter_run_animtaion_left;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation* peashooter_run_animtaion_right = nullptr;
	Animation* peashooter_run_animtaion_left = nullptr;
	PeashooterCharacter* character = nullptr;
};


class PeashooterAttExState
	: public StateNode
{
public:
	PeashooterAttExState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~PeashooterAttExState()
	{
		if (peashooter_attack_ex_animtaion_right)
			delete peashooter_attack_ex_animtaion_right;
		if (peashooter_attack_ex_animtaion_left)
			delete peashooter_attack_ex_animtaion_left;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override ;

private:
	PeashooterCharacter* character = nullptr;
	Animation* peashooter_attack_ex_animtaion_right = nullptr;
	Animation* peashooter_attack_ex_animtaion_left = nullptr;
};




class PeashooterDieState
	: public StateNode
{
public:
	PeashooterDieState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~PeashooterDieState()
	{
		if (peashooter_die_animtaion_right)
			delete peashooter_die_animtaion_right;
		if (peashooter_die_animtaion_left)
			delete peashooter_die_animtaion_left;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;

private:
	PeashooterCharacter* character = nullptr;
	Animation* peashooter_die_animtaion_right = nullptr;
	Animation* peashooter_die_animtaion_left = nullptr;
};
