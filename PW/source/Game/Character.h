#pragma once


#include "ItemObject.h"


using namespace std;

class CharacterManger;
class Controller;
class RenderItem;
class RenderUI;
class BuffBox;



class Character : public ItemObject
{
	friend class CharacterManger;
	friend class Controller;

public:

	enum class KeyState
	{
		KEY_UP,
		KEY_DOWN,
	};

	enum class MovementState
	{
		None,
		Idle,
		Run,
		Attack_ex,
		Die
	};

	//角色数据更新
	void on_update(float delta) override;

	//角色创建时的初始化
	virtual void on_init() {};

	void set_own_controller(Controller* controller)
	{
		this->controller = controller;
	}

	void set_owned_controller(Controller* controller);

	Controller* get_owned_controller() { return controller; };

	StateMachine* get_state_machine() { return state_machine; }

	//添加输入事件
	void addInputEvent(string vk_code, function<void()> event, KeyState key_state);

	// 执行输入事件任务
	void executeInputEvent(string vk_code, KeyState key_state);

	virtual void init_input_enven(Character* charater) {};

	virtual void subtract_hp(int value) { hp -= value; printf("hp:%d\r\n", hp); }

	void add_mp(int value) 
	{ 
		mp += value; 
		if (mp > 100)
			mp = 100;
		printf("mp:%d\r\n", mp);
	}

	bool get_on_ground() { return on_ground; }

	void set_hp(int hp) { this->hp = hp; }
	
	void add_hp(int value) {
		hp += value;
		if (hp > 100)
			hp = 100;
	}

	int get_hp() { return hp; }

	int get_mp() { return mp; }

	void set_can_attack(bool canAttack) { this->can_attack_ex = canAttack; }

	void set_can_jump(bool jump) { this->can_jump = jump; printf("2121212\r\n"); }

	void set_to_invulnerable(bool enable_sketch = false, int invulnerable_time = 500);

	void set_to_invulnerable_no_timer(bool is_invulnerable) { this->is_invulnerable = is_invulnerable; };

	bool get_is_invulnerable() { return is_invulnerable; }

	void set_character_run_speed(float speed) { run_velocity = speed; }

	void set_hit_direction_right(bool right) { hit_direction_right = right; }

	virtual void on_die();

	void set_run_velocity(float run_velocity) { this->run_velocity = run_velocity; /*printf("当前速度:%.2f,\r\n", this->run_velocity);*/ };

	float get_run_velocity() { return run_velocity; };

	void set_attack(bool flag) {
		can_attack_ex = flag;
		can_attack = flag;
	}

protected:
	StateMachine* state_machine = nullptr;		//需要要手动销毁

	float jump_velocity = -0.75f;
	float run_velocity = 0.45f;					//跑动速度
	bool on_jump = false;

	bool is_right_key_down = false;				//向右按键按下
	bool is_left_key_down = false;				//向左按键按下

	int  attck_cd = 500;						//普通攻击冷却时间
	bool can_attack = true;						//是否可以普通攻击
	Timer timer_attack_cd;						//普通攻击冷却时间

	IMAGE sketch_image;
	bool is_invulnerable = false;				//角色是否处于无敌状态
	bool is_showing_sketch_frame = false;		//当前帧是否应该显示剪影
	bool is_enable_sketch = false;				//是否开启剪影

	Timer timer_run_effect_generation;			//奔跑特效生成
	Timer timer_die_effect_generation;			//死亡特效生成

	bool can_attack_ex = true;					//是否可以进行特殊攻击

	int hp = 100;								//角色生命值
	int mp = 0;									//角色能量值

	//外部赋值，不需要销毁
	Controller* controller = nullptr;

	bool can_jump = true;

	bool hit_direction_right = false;			//击中方向是否为右边

	bool is_die = false;

private:
	Timer timer_invulnerable;					//无敌状态定时器
	Timer timer_invulnerable_blink;				//无敌状态闪烁定时器


public:
	MovementState current_movement_state = MovementState::None;

	

protected:
	Character(Vector2 position, bool is_render_on_ui = false);

	 ~Character();

	 void handleCollision(const HitInfo& hit_info) override;

	 void set_timer_attack_cd(int cd_time);

	 virtual void on_land() {};

	 virtual void Move_right_down();
	 virtual void Move_right_up();
	 virtual void Move_left_down();
	 virtual void Move_left_up();
	 virtual void On_Jump();
	 virtual void On_Attack() {};
	 virtual void On_Attack_Ex() {};


private:
	unordered_map<string, function<void()>> input_event_map_key_down;
	unordered_map<string, function<void()>> input_event_map_key_up;



};


