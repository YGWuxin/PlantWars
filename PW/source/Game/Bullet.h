#pragma once
#include "ItemObject.h"

class BulletPool;
class Character;

class Bullet : public ItemObject
{
	friend class BulletPool;

public:
	void set_damage(int damage)
	{
		this->damage = damage;
	}

	void set_mp(int mp)
	{
		this->mp_value = mp;
	}

	int get_damage() { return damage; }


	void enable();

	void disable();

	void set_owned_character(Character* character)
	{
		owned_character = character;
	}



protected:
	void on_update(float delta) override;

	virtual void check_exceeds_screen();

	void handleCollision(const HitInfo& hit_info) override;

	virtual void play_sound(){};

	virtual void begin(Character* character)
	{
		enable();
		owned_character = character;
	};

protected:
	int damage = 10;						//子弹伤害
	int mp_value = 0;						//所能积攒的能量
	bool valid = true;						//子弹是否有效
	bool is_anble = false;					//子弹是否可以启用
	Character* owned_character = nullptr;		//发射的玩家

	bool is_enable_shake = false;	//是否开启摄像机抖动
	float strenth = 0;				//抖动强度
	int duration = 0;				//抖动间隔

private:



};

