#pragma once
#include "StateNode.h"
#include "GloomshroomCharacter.h"

class StateMachine;
class GloomshroomCharacter;

class GloomshroomIdleState : public StateNode
{
public:
	GloomshroomIdleState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~GloomshroomIdleState() {
		if (gloomshroom_idle_animtaion_right)
			delete gloomshroom_idle_animtaion_right;
		if (gloomshroom_idle_animtaion_left)
			delete gloomshroom_idle_animtaion_left;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation* gloomshroom_idle_animtaion_right = nullptr;
	Animation* gloomshroom_idle_animtaion_left = nullptr;
	GloomshroomCharacter* character = nullptr;

};


class GloomshroomRunState : public StateNode
{
public:
	GloomshroomRunState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~GloomshroomRunState() {
		if (gloomshroom_run_animtaion_right)
			delete gloomshroom_run_animtaion_right;
		if (gloomshroom_run_animtaion_left)
			delete gloomshroom_run_animtaion_left;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation* gloomshroom_run_animtaion_right = nullptr;
	Animation* gloomshroom_run_animtaion_left = nullptr;
	GloomshroomCharacter* character = nullptr;

};


class GloomshroomAttExState : public StateNode
{
public:
	GloomshroomAttExState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~GloomshroomAttExState() {
		if (gloomshroom_attack_ex_animtaion_right)
			delete gloomshroom_attack_ex_animtaion_right;
		if (gloomshroom_attack_ex_animtaion_left)
			delete gloomshroom_attack_ex_animtaion_left;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;


private:
	Animation* gloomshroom_attack_ex_animtaion_right = nullptr;
	Animation* gloomshroom_attack_ex_animtaion_left = nullptr;
	GloomshroomCharacter* character = nullptr;

};



class GloomshroomDieState : public StateNode
{
public:
	GloomshroomDieState(StateMachine* state_machine) { own_state_machine = state_machine; };
	~GloomshroomDieState()
	{
		if (gloomshroom_die_animtaion_right)
			delete gloomshroom_die_animtaion_right;
		if (gloomshroom_die_animtaion_left)
			delete gloomshroom_die_animtaion_left;
	};

	//状态进入函数
	void on_enter() override;

	//状态更新函数
	void on_update(float delta)  override;

	//状态退出时函数
	void on_exit() override;

private:
	GloomshroomCharacter* character = nullptr;
	Animation* gloomshroom_die_animtaion_right = nullptr;
	Animation* gloomshroom_die_animtaion_left = nullptr;
};



