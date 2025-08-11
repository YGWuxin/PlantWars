#pragma once
#include "Bullet.h"
#include "../Res/Animation.h"

class BulletPool;

class NutExplode : public Bullet
{
	friend class BulletPool;

private:
	Animation animation_explode;

private:
	NutExplode();
	~NutExplode() = default;

	void begin(Character* character) override;

	void play_sound() override;

	void on_update(float delta) override;

};

