#pragma once

#include "ItemObject.h"
#include "Vector2.h"
#include "../Res/Animation.h"

class Character;

class BuffBox : public ItemObject
{

public:
	enum class BuffType
	{
		Hurry = 0,
		Invisible,
		Recover,
		Silence,
		None
	};

public:
	BuffBox();
	~BuffBox() = default;

	BuffType getBuffType() { return type; }

	IMAGE* get_buff_icon() { return buff_icon; }

private:
	Animation animation_idle;

	bool is_anble = true;

	BuffType type = BuffType::None;

protected:
	Character* hited_character = nullptr;

	Timer timer_buff;

	Timer timer_recover_hp;

	int buff_time = 8000;

	int buff_result = -1;

	IMAGE* buff_icon = nullptr;

private:
	void on_update(float delta) override;
	void check_exceeds_screen();

	void handleCollision(const HitInfo& hit_info) override;

public:
	void event_buff_begin();
	void event_buff_end();

};

