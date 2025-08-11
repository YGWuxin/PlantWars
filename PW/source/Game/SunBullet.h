#pragma once
#include "Bullet.h"
#include "../Res/Animation.h"

class BulletPool;

class SunBullet : public Bullet
{
	friend class BulletPool;

private:
	Animation animation_idle;
	Animation animation_explode;

	void begin(Character* character) override;

	void play_sound() override;

	//void handleCollision(const HitInfo& hit_info) override;

	void check_exceeds_screen() override;

private:
	SunBullet();
	~SunBullet() = default;

	void on_update(float delta) override;

};

