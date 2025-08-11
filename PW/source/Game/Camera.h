#pragma once

#include "Vector2.h"
#include "../Utils/Timer.h"


class Camera
{
public:
	Camera();
	~Camera() = default;

	const Vector2& get_position() const
	{
		return position;
	}

	void reset();

	void on_update(int delta);

	void Shake(float strenth,int duration,float frq = 0);

private:
	Vector2 position = Vector2(0, 0);		//…„œÒª˙Œª÷√
	Timer timer_shake;
	bool is_shakeing = false;
	float shakeing_strength = 0;
	float frq = 2.0f;
	float frq_temp = 0;
};

