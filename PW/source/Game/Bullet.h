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
	int damage = 10;						//�ӵ��˺�
	int mp_value = 0;						//���ܻ��ܵ�����
	bool valid = true;						//�ӵ��Ƿ���Ч
	bool is_anble = false;					//�ӵ��Ƿ��������
	Character* owned_character = nullptr;		//��������

	bool is_enable_shake = false;	//�Ƿ������������
	float strenth = 0;				//����ǿ��
	int duration = 0;				//�������

private:



};

