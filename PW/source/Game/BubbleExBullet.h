#pragma once
#include "Bullet.h"
#include "../Res/Animation.h"

class BulletPool;

class BubbleExBullet :  public Bullet
{
	friend class BulletPool;

private:
	Animation animation_explode;

	const float speed = 0.25f;


private:
	BubbleExBullet();
	~BubbleExBullet() = default;

	void begin(Character* character) override;

	void play_sound() override;

	//void handleCollision(const HitInfo& hit_info) override;

	//void check_exceeds_screen() override;

	void on_update(float delta) override;

};

