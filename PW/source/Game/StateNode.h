#pragma once

class StateMachine;

class StateNode
{
public:
	StateNode() = default;
	~StateNode() = default;

	//״̬���뺯��
	virtual void on_enter() {};

	//״̬���º���
	virtual void on_update(float delta) {};

	//״̬�˳�ʱ����
	virtual void on_exit() {};


protected:
	StateMachine* own_state_machine = nullptr;
	bool loadedAnimation = false;

private:
	


};

