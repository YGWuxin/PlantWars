#pragma once
#include "Bullet.h"
#include "../Res/Animation.h"

class BulletPool;
class IMAGE;

class PeaBullet : public Bullet
{
	friend class BulletPool;


private:
	Animation animation_break;
	IMAGE* img_pea;
	
	float speed = 0;

	void begin(Character* character) override;

	void play_sound() override;

protected:
	

private:
	PeaBullet();
	~PeaBullet() = default;

	void on_update(float delta) override;


};

