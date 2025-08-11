#pragma once

class StateMachine;

class StateNode
{
public:
	StateNode() = default;
	~StateNode() = default;

	//状态进入函数
	virtual void on_enter() {};

	//状态更新函数
	virtual void on_update(float delta) {};

	//状态退出时函数
	virtual void on_exit() {};


protected:
	StateMachine* own_state_machine = nullptr;
	bool loadedAnimation = false;

private:
	


};

